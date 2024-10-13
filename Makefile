# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/11 20:12:28 by bouhammo          #+#    #+#              #
#    Updated: 2024/10/12 22:43:00 by bouhammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =cc 
CFLAGS= -Wall -Wextra -Werror
CFILES= parsing.c main.c  ft_atoi.c functions.c start_simulation.c change_in_var.c 
 
OBJS= $(CFILES:.c=.o)
NAME = philo


all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re: fclean all 
