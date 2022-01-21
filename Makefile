NAME		=	minishell

SRCS_FILES	= 	${shell find ./source -name "*.c"}

SRCS_FOLDER	=	source/

SRCS		= 	$(SRCS_FILES)
OBJS		=	$(patsubst %.c,%.o,$(SRCS))

READLINE = -L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib/ -lreadline

INCLUDE		=	-I./include -I./libs/libft/

CC			=	gcc -g
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address
RM			=	rm -f

LIB = ./libft/libft.a

.PHONY:		all clean fclean re bonus

all:		$(NAME)

%.o:		%.c
			$(CC) $(INCLUDE) -c -g $< -o $@ 
$(NAME):	$(OBJS)
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(INCLUDE) ${READLINE} $(LIB) -o $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)
			@make -C $(dir $(LIB)) clean

fclean:		clean
			@make -C $(dir $(LIB)) fclean
			$(RM) $(NAME)

re:			fclean all

norm:
	norminette