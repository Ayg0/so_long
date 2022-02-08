CC = cc

NAME = so_long


CFLAGS = -Wall -Werror -Wextra -Imlx
LFLAGS = -lmlx -framework OpenGl -framework Appkit

SRCS = enemy_movements.c so_long.c so_long_utils1.c so_long_utils2.c so_long_utils3.c\
		so_long_utils4.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJS = ${SRCS:.c=.o}


.c.o:
		$(CC) $(CFLAGS) -c -o $@ $<

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(LFLAGS) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
