# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 16:19:39 by ofilloux          #+#    #+#              #
#    Updated: 2024/10/30 18:46:15 by ofilloux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
COMP = cc -Wall -Wextra -Werror -pthread -g -O0 -fsanitize=thread
INC = ./inc/philo.h

UTILS = ./utils/strings.c \
		./utils/time.c \
		./utils/mutex.c \
		./utils/clean_exit.c

SRC = main.c \
	./src/init.c \
	./src/algo.c \
	./src/actions.c \
	./src/dinner_is_over.c \
	./src/msg.c \
	$(UTILS)

OBJ = $(SRC:.c=.o)

###################

all : $(NAME)

$(NAME) : $(OBJ)
	$(COMP) $(OBJ) -pthread -o $(NAME)

%.o : %.c $(INC) Makefile
	$(COMP) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
