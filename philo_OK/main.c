/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:12:23 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/15 19:35:54 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	toto(void)
{
	system("leaks -q philo");
}

void	ft_free(t_table *table)
{
	free(table->philos);
	table->philos = NULL;
	free(table->forks);
	table->forks = NULL;
	return ;
}

void	ft_print(char *ptr)
{
	printf("%s", ptr);
	return ;
}

void	ft_destroy_mutex(t_table *table)
{
	int	i;

	if (pthread_mutex_destroy(&table->stop_mutex) != 0)
		return (ft_print("Failed to destroy mutex\n"));
	if (pthread_mutex_destroy(&table->table_ready) != 0)
		return (ft_print("Failed to destroy mutex\n"));
	if (pthread_mutex_destroy(&table->print_lock) != 0)
		return (ft_print("Failed to destroy mutex\n"));
	if (pthread_mutex_destroy(&table->stop_simlation) != 0)
		return (ft_print("Failed to destroy mutex\n"));
	if (pthread_mutex_destroy(&table->stop_simlation_two) != 0)
		return (ft_print("Failed to destroy mutex\n"));
	if (pthread_mutex_destroy(&table->incr_count) != 0)
		return (ft_print("Failed to destroy mutex\n"));
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_mutex_destroy(&table->forks[i]) != 0)
			return (ft_print("Failed to destroy mutex\n"));
		i++;
	}
	return ;
}

void	handle_one_philo(t_table *table)
{
	table->a = 0;
	table->start_time = get_time();
	pthread_mutex_lock(&table->forks[0]);
	print_output(table->philos, "is thinking");
	print_output(table->philos, "has taken a fork");
	print_output(table->philos, "is died");
	pthread_mutex_unlock(&table->forks[0]);
	return ;
}

int	main(int ac, char **av)
{
	t_table	table;

	// atexit(toto);
	if (ac == 6 || ac == 5)
	{
		if (parsing_data(&table, ac, av) == 1)
			return (0);
		data_init(&table);
		if (ft_atoi(av[1]) == 1)
			handle_one_philo(&table);
		else
			start_simulation(&table);
	}
	else
	{
		printf_error("Error: Wrong number of arguments !");
		return (0);
	}
	ft_destroy_mutex(&table);
	ft_free(&table);
	return (0);
}
