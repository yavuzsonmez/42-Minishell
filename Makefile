# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 14:20:37 by ysonmez           #+#    #+#              #
#    Updated: 2022/02/15 10:09:16 by ysonmez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color
Set_Color		=		\033[0m						# Text Reset
Red				=		\033[0;31m					# Red
Green			=		\033[0;32m					# Green

NAME			=		minishell

SRCS			=		srcs/main.c \
						srcs/parser.c \
						srcs/syntax.c \
						srcs/cmd.c \
						srcs/cmd_path.c \
						srcs/file_hd_spaces.c \
						srcs/quotes_cmd.c \
						srcs/quotes_fix.c \
						srcs/quotes_utils.c \
						srcs/utils.c \
						srcs/env_lst.c \
						srcs/lst_utils.c \
						srcs/exec_main.c \
						srcs/exec_main_utils.c \
						srcs/exec_route.c \
						srcs/exec_route2.c \
						srcs/exec_task.c \
						srcs/exec_utils.c \
						srcs/exec_lst_utils.c \
						srcs/exec_command.c \
						srcs/exec_heredoc.c \
						srcs/signals.c \
						srcs/env_get.c \
						srcs/dollar_sign.c \
						srcs/ft_replace.c \
						srcs/free.c \
						srcs/cd.c \
						srcs/echo.c \
						srcs/env.c \
						srcs/exit.c \
						srcs/export.c \
						srcs/pwd.c \
						srcs/unset.c \

OBJS			=		$(SRCS:.c=.o)

LIB				=		@make -C ./libft

ifeq ($(USER), home)
	LDFLAGS="-L/usr/local/opt/readline/lib"
	CPPFLAGS="-I/usr/local/opt/readline/include"
else #42
	LDFLAGS="-L/Users/$(USER)/.brew/opt/readline/lib"
	CPPFLAGS="-I/Users/$(USER)/.brew/opt/readline/include"
endif

CFLAGS			=		-Wall -Werror -Wextra #-g -fsanitize=address

.c.o			:
						@gcc $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME)			:		$(OBJS)
						$(LIB)
						@echo "$(Green)Libft has been created$(Set_Color)"
						@gcc -lreadline $(LDFLAGS) $(CPPFLAGS) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)
						@echo "$(Green)Minishell has been created$(Set_Color)"

lib				:
						$(LIB)
						@echo "$(Green)Libft has been created$(Set_Color)"

clean			:
						@rm -f $(OBJS)
						@echo "$(Red)Objects have been removed$(Set_Color)"

fclean			:		clean
						@rm -f $(NAME)
						@echo "$(Red)Minishell has been removed$(Set_Color)"
						@cd ./libft && make fclean
						@echo "$(Red)Libft has been removed$(Set_Color)"

all				:		$(NAME)

re				:		fclean all

.PHONY			:		clean fclean all re
