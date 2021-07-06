CC = clang

UNAME = $(shell uname)

NAME = minishell.a

FLAGS = -Wall -Wextra -Werror

SRCS  =  srcs/lib/lib_utils1.c srcs/lib/lib_utils2.c srcs/lib/ft_split.c srcs/parsing/parsing.c srcs/cmd/cmd_utils.c \
 	srcs/cmd/fill_cmd_array.c  srcs/cmd/parse_cmd_array.c  srcs/cmd/cmd_utils.c srcs/cmd/pipe.c \
	srcs/builtins/echo.c srcs/builtins/pwd.c srcs/builtins/execpath.c srcs/builtins/cd.c srcs/builtins/env.c \
	srcs/builtins/exit.c srcs/builtins/unset.c srcs/builtins/export.c srcs/builtins/error.c \
	srcs/parsing/expand_env.c srcs/parsing/parsing_utils.c srcs/parsing/parsing.c \
	srcs/env/env_utils1.c srcs/env/env_utils2.c

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
	@$(CC) minishell.c -o minishell -lreadline $(NAME)
endif

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)
	$(RM) minishell

re: fclean all