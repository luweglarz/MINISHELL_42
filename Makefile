CC = clang

NAME = minishell.a

FLAGS = -Wall -Wextra -Werror

SRCS  =   main.c srcs/lib/lib_utils.c srcs/parsing.c srcs/builtins/echo.c srcs/builtins/pwd.c srcs/cmd/cmd_utils.c srcs/cmd/cmd_funcs.c

RM	= rm -f

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)
	@$(CC) -g -fsanitize=address -lreadline main.c -o minishell $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)
	$(RM) minishell

re: fclean all