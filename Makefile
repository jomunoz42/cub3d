
NAME = cub3d
SRCDIR = .
OBJDIR = objs
MLXDIR = ../.minilibx-linux
GNL_DIR = ./gnl
MAP_DIR = maps
TEXTURE_DIR = ../textures
PARSE = ./parsing
UTILS = ./utils

SRC = \
	$(SRCDIR)/main.c struct_new.c window_management.c freedom.c megamente.c player_movement.c picasso.c davinci.c\
	$(PARSE)/parser.c \
	$(PARSE)/header_validation.c \
	$(PARSE)/construct_map.c \
	$(PARSE)/map_validation.c \
	$(PARSE)/rgb_validation.c \
	$(UTILS)/gnl.c \
	$(UTILS)/vini_utils.c \
	$(UTILS)/utils1.c \
	$(PARSE)/villan_arc.c \


OBJS = $(SRC:../%.c=$(OBJDIR)/%.o)
OBJS := $(OBJS:./%.c=$(OBJDIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Wno-incompatible-pointer-types #TIRAR ESSA ULTIMA FLAG DEPOIS ANIMAL CABACO DO KRL


MLX_FLAGS = -L . -lmlx -lXext -lX11
INCLUDES = -I$(MLXDIR) -I$(GNL_DIR) -I. -I$(MAP_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(OBJDIR)/%.o: ../%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: ./%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

val: re
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --track-origins=yes ./$(NAME) map.cub
	
lib:
	tar -xf minilibx-linux.tgz
	cd minilibx-linux && make CFLAGS="-O3 -std=gnu11"
	test -f libmlx.a
	mv mlx.h ../
	rm -rf minilibx-linux

norm:
	@norminette $(shell find . -type f \( -name "*.c" -o -name "*.h" \)) \
	| awk '/c: Error/ { c++; if (c % 2 == 1) printf "\033[1;35m%s\033[0m\n", $$0; else printf "\033[1;36m%s\033[0m\n", $$0 }'
	@echo "Amount of errors: " && norminette $(shell find . -type f \( -name "*.c" -o -name "*.h" \)) | grep "Error" | wc -l

run: re
	@./$(NAME) map.cub


.PHONY: all clean fclean re