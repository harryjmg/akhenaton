#*****************************************************************************#
#
#	- Akhenaton: Solveur de problème d'échecs -
# 	- L2 Imperatif Bourdin 2014/2015 -
#
#	Harry & Fode
#
#*****************************************************************************#

NAME =		akh

W_FLAGS =	-Wall -Wextra -O3

SRC_DIR =	src/
INC_DIR =	inc/

FILES =		main.c parse.c init.c board.c data.c attack.c \
			valid.c movegen.c io.c makemove.c \
			search.c


SRC = 		$(addprefix $(SRC_DIR), $(FILES))
OBJ = 		$(SRC:.c=.o)

INC =		-I $(INC_DIR)

all:		$(NAME)

$(NAME):	$(OBJ)
			@gcc -o $@ $^ $(INC)
			@printf "[done] ./$(NAME)\n"

%.o:		%.c
			@gcc $(W_FLAGS) -o $@ -c $^ $(INC)

clean:
			@rm -f $(OBJ)

fclean: 	clean
			@rm -f $(NAME)
			@printf "[deleted] ./$(NAME)\n"

re: 		fclean all

.PHONY:		all clean fclean re