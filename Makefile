NAME = cube3d
BONUS = cube3d_bonus
LIBFT = libft/libft.a

INC = ./minilibx-linux
LIBFT_DIR = libft

UNAME := $(shell uname)

CC = cc
CFLAGS = -I$(INC) -I$(LIBFT_DIR)/include -O3 -g

SRC = ./src/main.c \
	./src/mlx.c \
	./src/hook.c \
	./src/parsing/parsing.c \
	./src/parsing/parsing_img.c \
	./src/parsing/parsing_rgb.c \
	./src/parsing/parsing_map.c \
	./src/error.c \
	./src/struct.c \
	./src/parsing/check_map.c \
	./src/print_recast.c \
	./src/print_wall.c

BONUS_SRC = ./bonus/main.c \
	./bonus/mlx.c \
	./bonus/hook.c \
	./bonus/parsing/parsing.c \
	./bonus/parsing/parsing_img.c \
	./bonus/parsing/parsing_rgb.c \
	./bonus/parsing/parsing_map.c \
	./bonus/error.c \
	./bonus/struct.c \
	./bonus/parsing/check_map.c \
	./bonus/print_recast.c \
	./bonus/print_wall.c \
	./bonus/print_map.c \
	./bonus/print_weapon.c \
	./bonus/hook_utils.c \
	./bonus/hook_mv.c \
	./bonus/mouse_utils.c

OBJ = $(SRC:%.c=%.o)
BONUS_OBJ = $(BONUS_SRC:%.c=%.o)

LFLAGS = -Wall -Wextra -Werror -g -L$(INC) -lmlx -lXext -lX11 -lm -L$(LIBFT_DIR) -lft

ifeq ($(UNAME), Linux)
	LFLAGS += -lbsd
endif

# Règles de compilation
all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(BONUS)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

$(BONUS): $(BONUS_OBJ) $(LIBFT)
	@$(CC) -o $(BONUS) $(BONUS_OBJ) $(LFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(BONUS_OBJ) *~ core *.core
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME) $(BONUS)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus
