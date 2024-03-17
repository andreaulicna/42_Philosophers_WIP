# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 13:21:58 by aulicna           #+#    #+#              #
#    Updated: 2024/03/17 15:01:41 by aulicna          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = src/main.c \
		src/input.c \
		src/init.c \
		src/party_run.c \
		src/party_close.c \
		src/eat_sleep_think.c \
		src/mutex_change.c \
		src/log.c \
		src/time.c \
		src/error.c \
		src/free.c

OBJ = $(SRC:.c=.o)

HEADER = incl/philosophers.h

#CFLAGS = -Wall -Werror -Wextra -fsanitize=thread -g
CFLAGS = -Wall -Werror -Wextra -g

CC = cc

all: $(NAME)
	@echo "philo executable ready ✅"

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re