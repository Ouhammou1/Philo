/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:12:18 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/12 21:52:30 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_error(char 	*str)
{
	printf(RED "%s\n" RESET, str);
	exit(1);
}

void 	*save_memory(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if(!ptr)
		printf_error("Malloc failed");
	return (ptr);
}

unsigned int  get_time()
{
	struct timeval av;	
	gettimeofday(&av  ,NULL);
	return ( (av.tv_sec * 1000) + (av.tv_usec / 1000));
}

void ft_usleep(unsigned int time)
{
	unsigned int start = get_time();
	while((get_time() - start) < time)
	{
		usleep(500);
	}
}

void 	print_output( t_philo *philo, char *status)
{
	if(!philo->table->a)
	{
		pthread_mutex_lock(&philo->table->print_lock);
		printf("%u %d %s\n", get_time() - philo->table->start_time, philo->id, status);
		pthread_mutex_unlock(&philo->table->print_lock);
		
	}
}
