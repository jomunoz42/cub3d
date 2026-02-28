#!/bin/bash

NAME="cub3d"
TMP="maps/tmp_test.cub"

VALGRIND_CMD="valgrind --leak-check=full --track-fds=yes \
--show-leak-kinds=all --track-origins=yes ./$NAME"

GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[1;33m"
NC="\033[0m"

run_test()
{
    DESC=$1

    echo ""
    echo "=================================================="
    echo "TEST: $DESC"
    echo "=================================================="
    echo ""

    echo "📄 Current .cub file being tested:"
    echo "--------------------------------------------------"

    # Print with line numbers for readability
    nl -ba $TMP

    echo "--------------------------------------------------"
    echo ""

    # Parser quick check
    PARSER_OUTPUT=$(./$NAME $TMP 2>&1 | head -n 1)

    if [[ "$PARSER_OUTPUT" == Error* ]]; then
        echo "[Parser]: Correctly rejected"
    else
        echo "[Parser]: Did NOT print Error"
    fi

    echo ""
    echo "🧠 Running Valgrind..."
    echo "--------------------------------------------------"
    echo ""

    valgrind --leak-check=full \
             --track-fds=yes \
             --show-leak-kinds=all \
             --track-origins=yes \
             ./$NAME $TMP

    echo ""
    echo "=================================================="
    echo ""
}
########################################
# BUILD VALID FILE PROGRESSIVELY
########################################

VALID="maps/valid_generated.cub"

echo "Building valid file progressively..."

# Start empty valid file
echo "" > $VALID

# Step 1: NO texture
echo "NO ./imgs/north.xpm" >> $VALID
cp $VALID $TMP
run_test "Build step: NO only"

# Step 2: SO texture
echo "SO ./imgs/south.xpm" >> $VALID
cp $VALID $TMP
run_test "Build step: + SO"

# Step 3: WE texture
echo "WE ./imgs/west.xpm" >> $VALID
cp $VALID $TMP
run_test "Build step: + WE"

# Step 4: EA texture
echo "EA ./imgs/east.xpm" >> $VALID
cp $VALID $TMP
run_test "Build step: + EA"

# Step 5: F color
echo "F 220,100,0" >> $VALID
cp $VALID $TMP
run_test "Build step: + F"

# Step 6: C color
echo "C 225,30,0" >> $VALID
cp $VALID $TMP
run_test "Build step: + C"

# Step 7: Map rows
echo "" >> $VALID
echo "11111" >> $VALID
echo "10001" >> $VALID
echo "10N01" >> $VALID
echo "10001" >> $VALID
echo "11111" >> $VALID
cp $VALID $TMP
run_test "Build step: COMPLETE VALID MAP"

########################################
# NOW WE CORRUPT THE VALID FILE
########################################

echo "Now corrupting valid file..."

# 1. Invalid character
cp $VALID $TMP
sed -i 's/10N01/10p01/' $TMP
run_test "Corruption: invalid map character"

# 2. Negative RGB
cp $VALID $TMP
sed -i 's/F 220,100,0/F -1,100,0/' $TMP
run_test "Corruption: negative RGB"

# 3. RGB > 255
cp $VALID $TMP
sed -i 's/F 220,100,0/F 300,0,0/' $TMP
run_test "Corruption: RGB > 255"

# 4. Remove texture
cp $VALID $TMP
sed -i '/^NO /d' $TMP
run_test "Corruption: missing NO texture"

# 5. Non-existent texture path
cp $VALID $TMP
sed -i 's|NO .*|NO ./imgs/none.xpm|' $TMP
run_test "Corruption: non-existent texture"

# 6. Break wall enclosure
cp $VALID $TMP
sed -i 's/11111/11011/' $TMP
run_test "Corruption: open wall"

########################################

rm -f $TMP
rm -f $VALID

echo -e "\nAll tests finished."