# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: home <home@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/15 12:03:05 by ysonmez           #+#    #+#              #
#    Updated: 2022/01/05 12:11:54 by home             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=		libft.a

SRCS	=		ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strchr_pos.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strcmp.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_memfree.c \
				ft_memfreeall.c \

OBJS	=		$(SRCS:.c=.o)

CFLAGS	=		-Wall -Wextra -Werror

.c.o	:
				@gcc $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME)	:		$(OBJS)
				@ar rc $(NAME) $(OBJS)
				@ranlib $(NAME)

clean	:
				@rm -f $(OBJS)

fclean	:		clean
				@rm -f $(NAME)

all		:		$(NAME)

re		:		fclean all

.PHONY	:		clean fclean all re
