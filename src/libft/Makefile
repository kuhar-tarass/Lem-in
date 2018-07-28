# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/22 20:42:59 by tkuhar            #+#    #+#              #
#    Updated: 2018/07/28 14:55:43 by tkuhar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_OFF=\033[0m#			# Text Reset
BLACK	=\033[0;30m#		# Black
RED		=\033[0;31m#		# Red
GREEN	=\033[0;32m#		# Green
YELLOW	=\033[0;33m#		# Yellow
BLUE	=\033[0;34m#		# Blue
PURPLE	=\033[0;35m#		# Purple
CYAN	=\033[0;36m#		# Cyan
WHITE	=\033[0;37m#		# White

CC= gcc
FLAGS= -Wall -Wextra -Werror
NAME= libft.a
SRC= ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c \
ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c \
ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c \
ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c \
ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c \
ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c \
ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c\
ft_lstpush_back.c ft_lstpush_front.c ft_strsplit_lst.c ft_exp.c ft_lstfind.c \

PRINTF = get_next_line.c \
flags_processing.c \
ft_getcharw.c \
ft_getstrw.c \
ft_itoa_base.c \
ft_printf.c \
ft_strinsert.c \
func_call.c \
func_print.c

OBJ= $(SRC:%.c=%.o)
PRINTFOBJ= $(PRINTF:%.c=%.o)

OK_STRING	=***	$(NAME) created		***

all: $(NAME) libftprintf.a

$(NAME) libftprintf.a : $(OBJ) $(PRINTFOBJ)
	@ar rcs $(NAME) $(OBJ) get_next_line.o
	@ar rcs libftprintf.a $(PRINTFOBJ)

%.o:%.c
	@$(CC) $(FLAGS) -c $< -o $@ -I ../../include
	@printf "$(CYAN)*$(COLOR_OFF)"

clean:
	@rm -f $(OBJ) $(PRINTFOBJ)

fclean: clean
	@rm -f $(NAME) libftprintf.a

re: fclean all
