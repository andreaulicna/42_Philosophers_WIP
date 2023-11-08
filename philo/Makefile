# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 13:21:58 by aulicna           #+#    #+#              #
#    Updated: 2023/11/08 14:31:29 by aulicna          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = src/main.c \
						src/input.c

OBJ = $(SRC:.c=.o)

HEADER = incl/philosophers.h

CFLAGS = -Wall -Werror -Wextra

GCC = gcc

all: $(NAME)
	@echo "philo executable ready ✅"

.c.o:
	$(GCC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	$(GCC) $(CFLAGS) -o $@ $^

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re