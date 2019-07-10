##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME =	my_hunter

OBJ	=	$(SRC:.c=.o)

SRC	=	my_hunter_without_coding_style.c	\
		my_put_nbr.c						\
		my_putstr.c							\
		int_to_string.c						\

all:
		gcc -o $(NAME) $(SRC) -lm -l csfml-graphics -l csfml-system
		ar rc libmy.a $(SRC)

clean:
		rm -f *.o

fclean:	clean
		rm -rf $(NAME)

re:		fclean all