/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:39:21 by ofilloux          #+#    #+#             */
/*   Updated: 2024/10/21 15:55:52 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr, \
			t_params *params) // attr peut être remplacá par NULL car non utilisé
{
	int	errnum;

	errnum = 0;
	// mutex = malloc(sizeof(pthread_mutex_t));
	// if (mutex == NULL)
	// 	clean_exit(params, EXIT_FAILURE, "Malloc error for mutex");
	errnum = pthread_mutex_init(mutex, attr);
	if (errnum != 0)
		clean_exit(params, errnum, "mutex init error");
}

void	ft_mutex_destroy(pthread_mutex_t *mutex, t_params *params)
{
	int	errnum;

	errnum = 0;
	if (mutex != NULL)
	{
		errnum = pthread_mutex_destroy(mutex);
		if (errnum != 0)
			clean_exit(params, errnum, "mutex destroy error");
	}
}

void	ft_mutex_lock(pthread_mutex_t *mutex, t_params *params)
{
	int	errnum;

	errnum = 0;
	if (mutex != NULL)
	{
		errnum = pthread_mutex_lock(mutex);
		if (errnum != 0)
			clean_exit(params, errnum, "mutex lock error");
	}
}

void	ft_mutex_unlock(pthread_mutex_t *mutex, t_params *params)
{
	int	errnum;

	errnum = 0;
	if (mutex != NULL)
	{
		errnum = pthread_mutex_unlock(mutex);
		if (errnum != 0)
			clean_exit(params, errnum, "mutex unlock error");
	}
}
