/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:12:32 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/15 19:35:57 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)

{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	return (0);
}

int	parsing_data(t_table *table, int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (ft_isdigit(av[i][j]) == 0)
			{
				printf_error("Enter Numbers Please  !");
				return (1);
			}
			j++;
		}
		i++;
	}
	table->num_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->meals_required = ft_atoi(av[5]);
	else
		table->meals_required = -1;
	return (0);
}

void	init_table(t_table *table)
{
	table->philos = save_memory(sizeof(t_philo) * table->num_philo);
	table->forks = save_memory(sizeof(pthread_mutex_t) * table->num_philo);
	table->simulation_running = 1;
	table->philo_is_die = false;
	table->ready = false;
	if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
		printf_error("Mutex init of print_lock is failed");
	if (pthread_mutex_init(&table->table_ready, NULL) != 0)
		printf_error("Mutex init of print_lock is failed");
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		printf_error("Mutex init of print_lock is failed");
	if (pthread_mutex_init(&table->stop_simlation, NULL) != 0)
		printf_error("Mutex init of print_lock is failed");
	if (pthread_mutex_init(&table->stop_simlation_two, NULL) != 0)
		printf_error("Mutex init of print_lock is failed");
	if (pthread_mutex_init(&table->incr_count, NULL) != 0)
		printf_error("Mutex init of print_lock is failed");
}

void	data_init(t_table *table)
{
	int	i;

	init_table(table);
	i = 0;
	while (i < table->num_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = get_time();
		table->philos[i].table = table;
		table->philos[i].fork_id_left = i;
		table->philos[i].fork_id_right = (i + 1) % table->num_philo;
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			printf_error("Mutex init  of forks[i] is failed");
		i++;
	}
}
