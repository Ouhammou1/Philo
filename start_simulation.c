/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:12:02 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/11 20:22:41 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"

bool 	read_variables(pthread_mutex_t *mutex, bool *value)
{
	bool 	type;

	pthread_mutex_lock(mutex);
	type = *value;
	pthread_mutex_unlock(mutex);
	return (type);
}

long get_long(pthread_mutex_t *mutex, long *value)
{
	long res;
	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

void increment(pthread_mutex_t *mutex, int *val)
{
	pthread_mutex_lock(mutex);
	(*val)++;
	pthread_mutex_lock(mutex);

}

void	setting_variables(pthread_mutex_t *mutex,long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}
void set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}
void 	start_simulation(t_table *table )
{
	int  i =0;
	table->a = 0;
	int ret;
	table->simulation_running = 1;
	table->start_time = get_time();


	while (i <  table->num_philo)
	{
		// ft_usleep(100);
		ret = pthread_create(&table->philos[i].thread, NULL , philo_life_cycle, &table->philos[i]);
		if(ret != 0)
			printf_error("Error creating thread");
		i++;
	}
	set_bool(&table->table_ready, &table->ready, true);
	while (1)
	{
		i = 0;
		while (i < table->num_philo)
		{
			// if (get_time() - get_long(&table->philos[i].time_mutex ,&table->philos[i].last_meal_time) >= table->time_to_die)
			if(get_time() - table->philos[i].last_meal_time >= table->time_to_die)
			{
				//setting_variables(&table->stop_mutex , &table->simulation_running, 0);
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
					counter++;
				i++;
			}
			if(counter == table->num_philo)
			{
				printf("-----------> all ate\n");
				// set_bool(&table->stop_mutex, &table->simulation_running, false);
				exit(1);
			}
		}
	}
	
	int l = 0;
	while ( l < table->num_philo)
	{
		pthread_join(table->philos[l].thread , NULL);
		l++;
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
	ft_usleep(philo->table->time_to_sleep);
}

void	*philo_life_cycle(void *data)
{

	t_philo *philo = (t_philo *)data;
	while (!read_variables(&philo->table->table_ready, &philo->table->ready))
	;
	if (philo->id % 2 != 0)
		sleeping(philo);
	while (get_long(&philo->table->stop_mutex , &philo->table->simulation_running) != 0 )//&& philo->table->philo_is_die == false )
	{
		thinking(philo);
		eating(philo);	
		sleeping(philo);
	}
	return (NULL);
}

