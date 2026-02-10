# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/29 22:29:12 by mohamaib          #+#    #+#              #
#    Updated: 2026/01/30 17:50:58 by mohamaib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = philo.c \
       simulate.c \
       simulate_utils.c \
       simulate_utils2.c \
       exit.c \
       philo_utils.c \
       init.c \
       gc.c

OBJS = $(SRCS:.c=.o)

HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re