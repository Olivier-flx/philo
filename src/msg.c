/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:36:26 by ofilloux          #+#    #+#             */
/*   Updated: 2024/10/30 18:36:37 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	dead_before_print(t_params *params)
{
	ft_mutex_lock(&params->start_time_mutex, params);
	if (params->dinner_is_over)
	{
		ft_mutex_unlock(&params->start_time_mutex, params);
		return (true);
	}
	else
	{
		ft_mutex_unlock(&params->start_time_mutex, params);
		return (false);
	}
}

int	timestamp_msg(t_filo_arr *filo, char *action)
{
	struct timeval	tv;
	double			tvm;

	if (gettimeofday(&tv, NULL) != 0)
		return (-2);
	tvm = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
	tvm -= filo->params->start_time;
	if (ft_strncmp(action, "fork", 4) == 0 && !dead_before_print(filo->params))
		printf("%.0f %i has taken a fork\n", tvm, filo->id);
	if (ft_strncmp(action, "eat", 3) == 0 && !dead_before_print(filo->params))
		printf("\033[1;32m%.0f %i is eating\033[0m\n", tvm, filo->id);
	if (ft_strncmp(action, "sleep", 5) == 0 && !dead_before_print(filo->params))
		printf("%.0f %i is sleeping\n", tvm, filo->id);
	if (ft_strncmp(action, "think", 5) == 0 && !dead_before_print(filo->params))
		printf("%.0f %i is thinking\n", tvm, filo->id);
	if (ft_strncmp(action, "die", 3) == 0)
	{
		printf("\033[0;31m%.0f %i died\033[0m\n", tvm, filo->id);
		return (-1);
	}
	return (0);
}
