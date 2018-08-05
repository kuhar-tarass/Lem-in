# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/16 16:30:15 by tkuhar            #+#    #+#              #
#    Updated: 2018/07/28 21:47:26 by tkuhar           ###   ########.fr        #
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

CC=		gcc

FLAGS=	-Wall -Wextra -Werror

NAME=	lem-in

SRCNAME=	main.c\
		algoritm_queue.c\
		algoritm.c\
		cache.c\
		out.c\
		parse.c\
		parse2.c\
		tools.c\
		validator_checker.c

INCLD=	./include

SRC=$(addprefix ./src/, $(SRCNAME))

OBJ= $(SRC:%.c=%.o)

LIBFT= ./src/libft/libft.a
LIBFTPRINTF= ./src/libft/libftprintf.a

OK_STRING    =***	$(NAME) created		***

all: $(NAME)
	
$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -I $(INCLD) $(LIBFTPRINTF) $(LIBFT)
	@printf "\n$(GREEN)$(OK_STRING)\n\n"

%.o:%.c $(LIBFT) $(LIBFTPRINTF)
	@$(CC) $(FLAGS) -c $< -I $(INCLD) -o $@
	@printf "$(CYAN)*$(COLOR_OFF)"

$(LIBFT) $(LIBFTPRINTF):
	@$(MAKE) -C ./src/libft
	@printf "\n$(GREEN)libft created $(COLOR_OFF)\n\n"

clean:
	@rm -f $(OBJ)
	@$(MAKE) clean -C ./src/libft
	@printf  "$(YELLOW)remove OBJ\n"

fclean:
	@printf "$(YELLOW)remove OBJ$(COLOR_OFF)\n"
	@$(MAKE) fclean -C ./src/libft
	@rm -f $(OBJ)
	@printf "$(RED)remove $(NAME)$(COLOR_OFF)\n"
	@rm -f $(NAME)
	@printf "$(RED)remove $(NAME2)$(COLOR_OFF)\n"
	@rm -f $(NAME2)

re: fclean all