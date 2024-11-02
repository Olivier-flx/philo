/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:39:55 by ofilloux          #+#    #+#             */
/*   Updated: 2024/10/30 18:18:51 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// void	eat(t_filo *filo, t_params *params)
// {
// 	if (!is_diner_over(params))
// 	{
// 		ft_mutex_lock(&(filo->fork), params);
// 		timestamp_msg(filo, "fork");
// 		ft_mutex_lock(&(filo->prev->fork), params);
// 		timestamp_msg(filo, "fork");
// 		filo->ttd = get_m_time(params); // à mutexer ?
// 		filo->lunchs++; /// à mutexer ?
// 		timestamp_msg(filo, "eat");
// 		msleep(params->time_to_eat);
// 		ft_mutex_unlock(&(filo->fork), params);
// 		ft_mutex_unlock(&(filo->prev->fork), params);
// 	}
// }

// void	eat(t_filo_arr *filo, t_params *params)
// {
// 	ft_mutex_lock(&params->start_time_mutex, params);
// 	if (!params->dinner_is_over)
// 	{
// 		ft_mutex_unlock(&params->start_time_mutex, params);
// 		if (filo->id % 2 == 0)
// 		{
// 			ft_mutex_lock(filo->left_fork, params);
// 			timestamp_msg(filo, "fork");
// 			ft_mutex_lock(filo->right_fork, params);
// 			timestamp_msg(filo, "fork");
// 		}
// 		else
// 		{
// 			ft_mutex_lock(filo->right_fork, params);
// 			timestamp_msg(filo, "fork");
// 			ft_mutex_lock(filo->left_fork, params);
// 			timestamp_msg(filo, "fork");
// 		}
// 		ft_mutex_lock(&filo->fil_mtx, params);
// 		filo->ttd = get_m_time(params);
// 		filo->lunchs++;
// 		ft_mutex_unlock(&filo->fil_mtx, params);
// 		timestamp_msg(filo, "eat");
// 		msleep(params->time_to_eat);
// 		ft_mutex_unlock(filo->left_fork, params);
// 		ft_mutex_unlock(filo->right_fork, params);
// 	}
// 	else
// 		ft_mutex_unlock(&params->start_time_mutex, params);
// }

void	pick_forks(t_filo_arr *filo, t_params *params)
{
	if (filo->id % 2 == 0)
	{
		ft_mutex_lock(filo->left_fork, params);
		timestamp_msg(filo, "fork");
		ft_mutex_lock(filo->right_fork, params);
		timestamp_msg(filo, "fork");
	}
	else
	{
		ft_mutex_lock(filo->right_fork, params);
		timestamp_msg(filo, "fork");
		ft_mutex_lock(filo->left_fork, params);
		timestamp_msg(filo, "fork");
	}
}

void	eat(t_filo_arr *filo, t_params *params)
{
	ft_mutex_lock(&params->start_time_mutex, params);
	if (!params->dinner_is_over)
	{
		ft_mutex_unlock(&params->start_time_mutex, params);
		pick_forks(filo, params);
		ft_mutex_lock(&filo->fil_mtx, params);
		filo->ttd = get_m_time(params);
		ft_mutex_unlock(&filo->fil_mtx, params);
		timestamp_msg(filo, "eat");
		msleep(params->time_to_eat);
		ft_mutex_lock(&filo->fil_mtx, params);
		filo->ttd = get_m_time(params);
		filo->lunchs++;
		ft_mutex_unlock(&filo->fil_mtx, params);
		ft_mutex_unlock(filo->left_fork, params);
		ft_mutex_unlock(filo->right_fork, params);
	}
	else
		ft_mutex_unlock(&params->start_time_mutex, params);
}

void	sleeping(t_filo_arr *filo, t_params *params)
{
	ft_mutex_lock(&params->start_time_mutex, params);
	if (!params->dinner_is_over)
	{
		ft_mutex_unlock(&params->start_time_mutex, params);
		timestamp_msg(filo, "sleep");
		msleep(params->tts_max);
	}
	else
		ft_mutex_unlock(&params->start_time_mutex, params);
}

void	think(t_filo_arr *filo, t_params *params)
{
	long	time_before_dying;

	ft_mutex_lock(&params->start_time_mutex, params);
	if (!params->dinner_is_over)
	{
		ft_mutex_unlock(&params->start_time_mutex, params);
		timestamp_msg(filo, "think");
		time_before_dying = get_m_time(params) - filo->ttd;
		msleep(time_before_dying / 10);
	}
	else
		ft_mutex_unlock(&params->start_time_mutex, params);
}

// void	think(t_filo_arr *filo, t_params *params)
// {
// 	ft_mutex_lock(&params->start_time_mutex, params);
// 	if (!params->dinner_is_over)
// 	{
// 		ft_mutex_unlock(&params->start_time_mutex, params);
// 		timestamp_msg(filo, "think");
// 		msleep((params->ttd_max - params->tts_max) / 2);
// 	}
// 	else
// 		ft_mutex_unlock(&params->start_time_mutex, params);
// }
