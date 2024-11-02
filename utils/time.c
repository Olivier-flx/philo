/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:42:01 by ofilloux          #+#    #+#             */
/*   Updated: 2024/10/30 18:37:31 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static uint64_t	u_time_of_day(void)
{
	struct timeval	tv;
	uint64_t		u_time;

	gettimeofday(&tv, NULL);
	u_time = (uint64_t) tv.tv_sec * 1000000 + (uint64_t) tv.tv_usec;
	return (u_time);
}

// usleep plus précis
int	ft_usleep(unsigned int time)
{
	uint64_t	start;

	start = u_time_of_day();
	while ((u_time_of_day() - start) < time)
		usleep(time / 50);
	return (0);
}

int	msleep(unsigned int msec)
{
	unsigned int	usec;

	usec = msec * 1000;
	if (ft_usleep(usec) != 0)
		return (-1);
	return (0);
}

void	set_simulation_start_time(t_params *params)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		clean_exit(params, EXIT_FAILURE, "set start time err");
	ft_mutex_lock(&(params->start_time_mutex), params);
	params->start_time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
	ft_mutex_unlock(&(params->start_time_mutex), params);
}

long	get_m_time(t_params *params)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		free(params->filo_arr);
		clean_exit(params, EXIT_FAILURE, "get_m_time err");
	}
	return ((tv.tv_sec) * 1000 + (tv.tv_usec / 1000));
}
