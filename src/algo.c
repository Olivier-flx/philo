/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:36:16 by ofilloux          #+#    #+#             */
/*   Updated: 2024/09/18 19:12:56 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// fonction pour sortir de la simulation si un philosophe meurt

bool	all_have_ate(t_params *params)
{
	t_filo	*i_node;
	int		meals;

	meals = 0;
	if (params->tot_lunchs = NULL)
		return (false);
	i_node = params->filos_lst;
	while (i_node->id != params->phil_n)
	{
		if (i_node->lunchs == params->tot_lunchs)
			meals++;
		if (meals == params->phil_n)
			return (true);
		i_node = i_node->next;
	}
	return (false);
}

bool	one_died(t_params *params)
{
	t_filo	*i_node;

	i_node = params->filos_lst;
	while (i_node->id != params->phil_n)
	{
		if (i_node->is_dead)
			return (true);
		i_node = i_node->next;
	}
	return (false);
}


bool	diner_is_over(t_params *params)
{
	if (all_have_ate(params) || one_died(params))
		return(true);
	return(false)
}


// synchroniser de début du repas et donc tous les threads pour que tous
	//les philos commencent leur repas en même temps

// s'il n'y a qu'un seul philosophe


void	*eat_or_not(t_filo	*filo)
{
	if(filo->id == filo->params->phil_n)
		// start_dinner
		return ;
	// if next and prev is_eating == false , then the filo can eat
	// tte - est décompté jusqu'à 0 et pendant ce temps is_eating == true
}

lets_eat(t_params *params)
{
	t_filo	*i_node;

	i_node = params->filos_lst;
	while (i_node->id < params->phil_n)
	{
		if (pthread_create(i_node->thread, NULL, eat_or_not, i_node) != 0)
			free_lst_exit(params->filos_lst, EXIT_FAILURE);
		i_node = i_node->next;
	}
	set_simulation_start_time(params)

	//simulation can start
	// get dinner start time

}
