# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/07 12:14:16 by jemagnie     #+#   ##    ##    #+#        #
#    Updated: 2018/11/01 17:40:07 by jemagnie    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #
NAME = fdf
FLAG = -Wall -Wextra -Werror
SRC = src/fdf.c src/event.c src/parse.c src/draw.c src/line.c \
	  src/rotate.c src/more.c src/mouse.c src/size.c
SEG = -fsanitize=address
OBJ = $(SRC:.c=.o)

.SILENT:

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	@make -C libft/
	@make -C minilibx_macos/
	@gcc $(FLAG) -L libft/ -lft -g -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit $(OBJ) -o $(NAME)
	@echo "fdf created"

%.o: %.c ./include/fdf.h
	@gcc $(FLAG) -I./ -c -o $@ $<

clean:
	@/bin/rm -f $(OBJ)
	@make -C libft/ clean
	@make -C minilibx_macos/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean
	@make -C minilibx_macos/ clean

re: fclean all

.PHONY : all clean fclean re
