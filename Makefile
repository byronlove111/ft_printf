CC = cc 

FLASGS = -Wall -Wextra -Werror

SRC = ./ft_printf.c ./utils.c

NAME = ft_printf.a

AR = ar -rcs

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

all: $(NAME)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean: 
	rm -rf $(OBJ) $(BONUS:.c=.o)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re