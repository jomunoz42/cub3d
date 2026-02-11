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
	$(PARSE)/parser.c \
	$(PARSE)/header_validation.c \
	$(PARSE)/construct_map.c \
	$(PARSE)/map_validation.c \
	$(PARSE)/rgb_validation.c \
	$(UTILS)/gnl.c \
	$(UTILS)/vini_utils.c \
	$(UTILS)/utils1.c \
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
	@mkdir -p $(EXTRA)
	@sed -i '17i\# include "../extra/AStar/AStar.h"' ./headers/general.h;
	@if [ ! -d "$(EXTRA)/AStar" ]; then \
		git clone https://github.com/BigZaphod/AStar.git $(EXTRA)/AStar; \
	fi
	@$(MAKE) all SRC="$(SRC_BASE) $(SRC_EXTRA)"


# ============== CLEAN ======================

clean:
	@rm -rf $(OBJDIR)

fclean:
	@echo "Removing AStar..."
	@rm -rf ./extra/AStar
	@if grep -q 'AStar/AStar.h' ./headers/general.h; then \
		sed -i '/AStar\/AStar.h/d' ./headers/general.h; \
	fi
	@$(MAKE) clean
	@rm -f $(NAME)


re: fclean all

# ============== TOOLS ======================

deb:
	lldb ./$(NAME) map.cub

val: re
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
