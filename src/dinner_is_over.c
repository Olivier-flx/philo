/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_is_over.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:13:03 by ofilloux          #+#    #+#             */
/*   Updated: 2024/10/30 18:41:15 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// fonction pour sortir de la simulation si un philosophe meurt

bool	all_have_ate(t_params *params)
{
	int		i;
	int		meals;

	i = 0;
	meals = 0;
	if (params->tot_lunchs == -1)
		return (false);
	while (i < params->phil_n)
	{
		ft_mutex_lock(&params->filo_arr[i].fil_mtx, params);
		if (params->filo_arr[i].lunchs == params->tot_lunchs)
			meals++;
		ft_mutex_unlock(&params->filo_arr[i].fil_mtx, params);
		if (meals == params->phil_n)
			return (true);
		i++;
	}
	return (false);
}
//			printf("All philosophers have eaten!\n"); // Débogage

bool	is_dead(t_filo_arr *filo)
{
	long	time_without_eating;

	if (filo->ttd == 0)
		return (false);
	time_without_eating = get_m_time(filo->params) - filo->ttd;
	if (time_without_eating > filo->params->ttd_max)
	{
		if (!filo->params->one_died)
		{
			filo->params->one_died = true;
			timestamp_msg(filo, "die");
		}
		return (true);
	}
	return (false);
}

bool	one_died(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->phil_n)
	{
		ft_mutex_lock(&params->filo_arr[i].fil_mtx, params);
		if (is_dead(&params->filo_arr[i]))
		{
			ft_mutex_unlock(&params->filo_arr[i].fil_mtx, params);
			return (true);
		}
		ft_mutex_unlock(&params->filo_arr[i].fil_mtx, params);
		i++;
	}
	return (false);
}

void	is_diner_over2(t_params *params)
{
	ft_mutex_lock(&params->start_time_mutex, params);
	params->one_died = one_died(params);
	params->all_have_ate = all_have_ate(params);
	ft_mutex_unlock(&params->start_time_mutex, params);
	ft_mutex_lock(&params->start_time_mutex, params);
	if (params->one_died || params->all_have_ate)
	{
		params->dinner_is_over = true;
	}
	ft_mutex_unlock(&params->start_time_mutex, params);
}

// bool	is_diner_over(t_params *params)
// {
// 	ft_mutex_lock(&params->start_time_mutex, params);
// 	if (params->one_died)
// 		return (true);
// 	ft_mutex_unlock(&params->start_time_mutex, params);
// 	if (all_have_ate(params) || one_died(params))
// 		return (true);
// 	return (false);
// }

// bool	one_died(t_params *params)
// {
// 	int	i;

// 	i = 0;
// 	while (i < params->phil_n)
// 	{
// 		ft_mutex_lock(&params->filo_arr[i].fil_mtx, params);
// 		if (params->filo_arr[i].is_dead)
// 		{
// 			ft_mutex_unlock(&params->filo_arr[i].fil_mtx, params);
// 			return (true);
// 		}
// 		ft_mutex_unlock(&params->filo_arr[i].fil_mtx, params);
// 		i++;
// 	}
// 	return (false);
// }
