/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:42:01 by ofilloux          #+#    #+#             */
/*   Updated: 2024/09/18 19:16:02 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	msleep(unsigned int msec)
{
	unsigned int	usec;

	usec = msec * 1000;
	if (usleep(usec) != 0)
		return (-1);
	return (0);
}

void	set_simulation_start_time(t_params *params)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		free_lst_exit(params->filos_lst, EXIT_FAILURE);
	params->start_time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
}

int	timestamp_msg(t_filo *filo, char *action)
{
	struct timeval	tv;
	double			tvm;

	if (gettimeofday(&tv, NULL) != 0)
		return (-2);
	tvm = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
	tvm -= filo->params->start_time;
	if (ft_strncmp(action, "fork", 4) == 0)
		printf("%f %i has taken a fork", tvm, filo->id);
	if (ft_strncmp(action, "eat", 3) == 0)
		printf("%f %i is eating", tvm, filo->id);
	if (ft_strncmp(action, "sleep", 5) == 0)
		printf("%f %i is sleeping", tvm, filo->id);
	if (ft_strncmp(action, "think", 5) == 0)
		printf("%f %i is thinking", tvm, filo->id);
	if (ft_strncmp(action, "die", 3) == 0)
	{
		printf("%f %i died", tvm, filo->id);
		return (-1);
	}
	return (0);
}
