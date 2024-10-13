/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:12:02 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/13 13:45:41 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"


void 	start_simulation(t_table *table )
{
	int  	i;
	int 	k;
	table->a = 0;
	int ret;
	table->start_time = get_time();

	i=0;
	k=0;
	while (i <  table->num_philo)
	{
		ret = pthread_create(&table->philos[i].thread, NULL , philo_life_cycle, &table->philos[i]);
		if(ret != 0)
			printf_error("Error creating thread");
		i++;
	}
	change_boolian(&table->table_ready, &table->ready, true);
	while (1)
	{
		i = 0;
		while (i < table->num_philo)
		{
			if(get_time() - table->philos[i].last_meal_time >= table->time_to_die)
			{
				table->simulation_running = 0;
				print_output(&table->philos[i], "died");
				return ;
			}

			i++;
		}
		if(table->meals_required != -1)
		{
			i = 0;
			int counter = 0;
			while(i < table->num_philo)
			{
				if(table->philos[i].meals_eaten >= table->meals_required)
				{
					counter++;
					// increment(&table->incr_count, &counter);
					// printf("------------->>>>>>>>>>   %d \n", counter);

				}

				i++;
			}
			if(counter == table->num_philo)
			{
				printf("-----------> all ate\n");
				setting_variables(&table->stop_simlation, &table->simulation_running, false);
				exit(1);
			}
		}
	}
	
	while ( k < table->num_philo)
	{
		pthread_join(table->philos[k].thread , NULL);
		k++;
	}
}



void eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->fork_id_left]);
	print_output(philo, "has taken a fork");

	pthread_mutex_lock(&philo->table->forks[philo->fork_id_right]);
	print_output(philo, "has taken a fork");

	print_output(philo, "is eating");
	philo->last_meal_time = get_time();
	ft_usleep(philo->table->time_to_eat);

	philo->meals_eaten++;

	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_right]);
	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_left]);
}


void	sleeping( t_philo *philo)
{
	print_output(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_output(philo, "is thinking");
}

void	*philo_life_cycle(void *data)
{

	t_philo *philo = (t_philo *)data;
	while (!read_variables(&philo->table->table_ready, &philo->table->ready))
	;
	if (philo->id % 2 != 0)
		sleeping(philo);
	while (get_long(&philo->table->stop_mutex , &philo->table->simulation_running) != 0 )
	{
		thinking(philo);
		eating(philo);	
		sleeping(philo);
	}
	return (NULL);
}

