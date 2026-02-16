NAME = cub3d

SRCDIR = .
OBJDIR = objs
MLXDIR = ../.minilibx-linux
GNL_DIR = ./gnl
MAP_DIR = maps
PARSE = ./parsing
UTILS = ./utils
MINIMAP = ./minimap
EXTRA = ./extra

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Wno-incompatible-pointer-types
MLX_FLAGS = -L . -lmlx -lXext -lX11
INCLUDES = -I$(MLXDIR) -I$(GNL_DIR) -I. -I$(MAP_DIR)

# ================= SOURCES =================

SRC_BASE = \
	$(SRCDIR)/main.c \
	struct_new.c \
	window_management.c \
	freedom.c \
	player_movement.c \
	picasso.c \
	raycast.c \
	mouse_movement.c \
	songs.c \
	basic_enemy.c \
	winning_exit.c \
	$(PARSE)/parser.c \
	$(PARSE)/header_validation.c \
	$(PARSE)/construct_map.c \
	$(PARSE)/map_validation.c \
	$(PARSE)/rgb_validation.c \
	$(UTILS)/gnl.c \
	$(UTILS)/dda_utils1.c \
	$(UTILS)/enemy_utils1.c \
	$(UTILS)/enemy_utils2.c \
	$(UTILS)/freedom_helper.c \
	$(UTILS)/game_loop_helper.c \
	$(UTILS)/keyboard_utils2.c \
	$(UTILS)/keyboard_utils.c \
	$(UTILS)/picasso_helper.c \
	$(UTILS)/print_stuff.c \
	$(UTILS)/songs_helper.c \
	$(UTILS)/struct_new_utils1.c \
	$(UTILS)/struct_new_utils2.c \
	$(UTILS)/struct_new_utils3.c \
	$(UTILS)/struct_new_utils4.c \
	$(UTILS)/struct_new_utils5.c \
	$(UTILS)/texture_utils1.c \
	$(UTILS)/utils1.c \
	$(UTILS)/vignette_utils.c \
	$(UTILS)/vini_utils10.c \
	$(UTILS)/vini_utils13.c \
	$(UTILS)/vini_utils16.c \
	$(UTILS)/vini_utils17.c \
	$(UTILS)/vini_utils19.c \
	$(UTILS)/vini_utils1.c \
	$(UTILS)/vini_utils2.c \
	$(UTILS)/vini_utils3.c \
	$(UTILS)/vini_utils4.c \
	$(UTILS)/vini_utils5.c \
	$(UTILS)/vini_utils6.c \
	$(UTILS)/vini_utils7.c \
	$(UTILS)/vini_utils8.c \
	$(UTILS)/vini_utils9.c \
	$(UTILS)/vini_utils.c \
	$(MINIMAP)/minimap.c \
	$(MINIMAP)/minimap_utils.c

SRC_EXTRA = \
	$(EXTRA)/AStar/AStar.c \
	$(EXTRA)/enemy.c

SRC = $(SRC_BASE)

# ================ OBJECTS ==================

OBJS = $(SRC:../%.c=$(OBJDIR)/%.o)
# OBJS = $(OBJS:./%.c=$(OBJDIR)/%.o)

# ================= RULES ===================

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -lm -lXfixes -o $(NAME)

$(OBJDIR)/%.o: ../%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: ./%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# =============== EXTRA =====================


extra: SRC += $(SRC_EXTRA)
extra:
	@mkdir -p extra
	@echo "[Creating extra directory]"
	@if [ -f enemy.txt ]; then \
		cp enemy.txt $(EXTRA)/enemy.c; \
	fi
	@echo "[Injecting enemy logic into game_loop_helper.c]"
	@if ! grep -q "update_enemy(gen, i);" ./utils/game_loop_helper.c; then \
		sed -i '25i\		if (gen->enemy[i].type != ENEMY_SKELETON && gen->flags->terror_mode)' ./utils/game_loop_helper.c; \
		sed -i '26i\			update_enemy(gen, i);' ./utils/game_loop_helper.c; \
	fi
	@echo "[Injecting mlx include into general.h]"
	@sed -i '17i\# include "../extra/AStar/AStar.h"' ./headers/general.h;
	@if [ ! -d "$(EXTRA)/AStar" ]; then \
		git clone https://github.com/BigZaphod/AStar.git $(EXTRA)/AStar; \
	fi
	@$(MAKE) all SRC="$(SRC_BASE) $(SRC_EXTRA)" CFLAGS=""


lib:
	git clone git@github.com:42paris/minilibx-linux.git
	cd minilibx-linux && make && cp libmlx.a ../ && cp mlx.h ../headers && cd .. && rm -rf minilibx-linux
	@if ! grep -q '# include "mlx.h"' ./headers/general.h; then \
		sed -i '15i\# include "mlx.h"' ./headers/general.h; \
	fi
# ============== CLEAN ======================

clean:
	@rm -rf $(OBJDIR)

fclean:
	@echo "Removing AStar and extra logic..."
	@rm -rf ./extra/AStar
	@rm -rf ./extra/enemy.c
	@sed -i '/ENEMY_SKELETON/d' ./utils/game_loop_helper.c
	@sed -i '/update_enemy(gen, i);/d' ./utils/game_loop_helper.c
	@if grep -q 'AStar/AStar.h' ./headers/general.h; then \
		sed -i '/AStar\/AStar.h/d' ./headers/general.h; \
	fi
	@if grep -q '# include "mlx.h"' ./headers/general.h; then \
		sed -i '/# include "mlx.h"/d' ./headers/general.h; \
	fi
	@rm -rf extra
	@echo "Deleting extra directory"
	@rm -rf headers/mlx.h
	@echo "Removing mlx.h from headers"
	@$(MAKE) clean
	@rm -f $(NAME)



re: fclean lib all

# ============== TOOLS ======================

deb:
	lldb ./$(NAME) maps/testing.cub

val:
	valgrind --leak-check=full --track-fds=yes \
	--show-leak-kinds=all --track-origins=yes \
	./$(NAME) map.cub

run: re
	@./$(NAME) maps/testing.cub

norm:
	@norminette $(shell find . -type f \( -name "*.c" -o -name "*.h" \)) \
	| awk '/c: Error/ { c++; if (c % 2 == 1) printf "\033[1;35m%s\033[0m\n", $$0; else printf "\033[1;36m%s\033[0m\n", $$0 }'
	@echo "Amount of errors: " && norminette $(shell find . -type f \( -name "*.c" -o -name "*.h" \)) | grep "Error" | wc -l

.PHONY: all clean fclean re extra run norm
