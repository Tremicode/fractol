SRCS = events_mouse_key.c init.c main.c math_utils.c render.c string_utils.c julia.c
OBJS = ${SRCS:%.c=%.o}
FLAGS = -Wall -Wextra -Werror -g
CC = gcc -g
RM = rm -f
NAME = fractol
MLX = ./minilibx-linux/libmlx.a

%.o:		%.c
			$(CC) $(FLAGS) -c $< -o $@

all:		$(NAME)

$(MLX):
			$(MAKE) -C ./minilibx-linux

$(NAME):	$(OBJS) $(MLX)
			$(CC) $(FLAGS) $(OBJS) $(MLX)  -o $(NAME) -lXext -lX11 -lm

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all
