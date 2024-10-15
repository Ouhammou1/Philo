/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:12:02 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/14 21:24:16 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation_threads(t_table *table)
{
	int	i;

	table->a = 0;
	table->start_time = get_time();
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_life_cycle,
				&table->philos[i]) != 0)
			printf_error("Error creating thread");
		i++;
	}
	change_boolian(&table->table_ready, &table->ready, true);
}

void	check_meals_required(t_table *table)
{
	int	counter;
	int	i;

	if (table->meals_required != -1)
	{
		counter = 0;
		i = 0;
		while (i < table->num_philo)
		{
			if (table->philos[i].meals_eaten >= table->meals_required)
				counter++;
			i++;
		}
		if (counter == table->num_philo)
		{
			printf("-----------> all ate\n");
			setting_variables(&table->stop_simlation,
				&table->simulation_running, 0);
		}
	}
}

void	monitor_simulation(t_table *table)
{
	int	i;

	while (table->simulation_running)
	{
		i = 0;
		while (i < table->num_philo)
		{
			if (get_time()
				- table->philos[i].last_meal_time >= table->time_to_die)
			{
				setting_variables(&table->stop_simlation_two,
					&table->simulation_running, 0);
				print_output(&table->philos[i], "died");
				exit(1);
			}
			i++;
		}
		if (!table->simulation_running)
			break ;
		check_meals_required(table);
	}
}

void	start_simulation(t_table *table)
{
	int	i;

	start_simulation_threads(table);
	monitor_simulation(table);
	i = 0;
	while (i < table->num_philo)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

void	*philo_life_cycle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!read_variables(&philo->table->table_ready, &philo->table->ready))
		;
	if (philo->id % 2 != 0)
		sleeping(philo);
	while (get_long(&philo->table->stop_mutex,
			&philo->table->simulation_running) != 0)
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}
