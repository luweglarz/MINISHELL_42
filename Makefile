CC = clang

UNAME = $(shell uname)

NAME = minishell.a

FLAGS = -Wall -Wextra -Werror

SRCS  =  srcs/builtins/cd.c srcs/builtins/echo.c srcs/builtins/env.c srcs/builtins/execpath.c srcs/builtins/exit.c srcs/builtins/export.c srcs/builtins/pwd.c srcs/builtins/unset.c\
		 srcs/cmd/error.c srcs/cmd/parse_cmd_array.c \
		 srcs/env/env_utils1.c srcs/env/env_utils2.c srcs/env/env_utils3.c\
		 srcs/filling/fill_cmd_array_utils.c srcs/filling/fill_cmd_array.c srcs/filling/split_args_utils.c srcs/filling/split_args.c \
		 srcs/lib/ft_split_slash.c srcs/lib/ft_split.c srcs/lib/lib_utils1.c srcs/lib/lib_utils2.c \
		 srcs/parsing/del_quotes.c srcs/parsing/without_quote.c srcs/parsing/get_exit_code.c srcs/parsing/expand_env1.c srcs/parsing/expand_env2.c srcs/parsing/expand_env3.c srcs/parsing/parsing_utils1.c srcs/parsing/parsing_utils2.c srcs/parsing/parsing_utils3.c srcs/parsing/parsing.c \
		 srcs/redirections/brackets.c srcs/redirections/pipe.c srcs/redirections/redirections_utils.c \

RM	= rm -f

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)
ifeq ($(UNAME), Darwin)
	@$(CC) minishell.c -o minishell -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include $(NAME)
endif
ifeq ($(UNAME), Linux)
	@$(CC) -g minishell.c -o minishell -lreadline $(NAME)
endif

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)
	$(RM) minishell

re: fclean all