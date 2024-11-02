/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:45:07 by ofilloux          #+#    #+#             */
/*   Updated: 2024/10/25 19:13:42 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_putnbr(int num)
{
	if (num < 0)
	{
		write(STDERR_FILENO, "-", 1);
		num *= -1;
	}
	if (num >= 10)
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	else
	{
		num += 48;
		write(STDERR_FILENO, &num, 1);
	}

}

void	simple_exit(char *msg, int exit_num)
{
	if (exit_num != 0)
	{
		write(STDERR_FILENO, "Err ", 4);
		ft_putnbr(exit_num);
		write(STDERR_FILENO, " : ", 3);
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
	exit(exit_num);
}

void	clean_exit(t_params *params, int exit_num, char *msg)
{
	int	i;

	i = -1;
	while (++i < params->phil_n && params->filo_arr[i].id <= i)
	{
		ft_mutex_lock(&params->filo_arr[i].fil_mtx, params);
		if (params->filo_arr[i].thread != 0)
			if(pthread_detach(params->filo_arr[i].thread) != 0 )
				printf("error for detaching thread of filo %i\n",params->filo_arr[i].id);
		ft_mutex_unlock(&params->filo_arr[i].fil_mtx, params);

		if (params->forks_initialized[i] == true)
			pthread_mutex_destroy(&params->forks2[i]);
		pthread_mutex_destroy(&params->filo_arr[i].fil_mtx);
	}
	pthread_mutex_destroy(&params->start_time_mutex);
	free(params->filo_arr);
	free(params->forks2);
	free(params->forks_initialized);
	if (exit_num != 0)
		simple_exit(msg, exit_num);
	else
		exit(0);
}
