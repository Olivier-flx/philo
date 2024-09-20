/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:17:09 by ofilloux          #+#    #+#             */
/*   Updated: 2024/09/18 18:25:21 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_table(t_params *params)
{
	t_filo	*last_node;

	last_node = params->filos_lst;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = params->filos_lst;
	params->filos_lst->prev = last_node;
}

t_filo	*create_filo_node(t_params *params, int i)
{
	t_filo	*philo;

	philo = malloc(sizeof(t_filo));
	if (philo == NULL)
		free_lst_exit(params->filos_lst, EXIT_FAILURE);
	philo->id = i + 1;
	philo->ttd = 0;
	philo->sleep_time = 0;
	philo->lunchs = 0;
	philo->is_eating = false;
	philo->is_sleeping = false;
	philo->is_dead = false;
	philo->thread = NULL;
	philo->params = params;
	philo->next = NULL;
	philo->prev = NULL;
	return (philo);
}

void	init_filos(t_params *params)
{
	int		i;
	t_filo	*new_fil;
	t_filo	*i_node;

	i = 0;
	new_fil = NULL;
	i_node = NULL;
	while (i < params->phil_n)
	{
		new_fil = create_filo_node(params, i);
		if (params->filos_lst == NULL)
		{
			params->filos_lst = new_fil;
			new_fil->prev = NULL;
		}
		else
		{
			i_node = params->filos_lst;
			while (i_node->next != NULL)
				i_node = i_node->next;
			new_fil->prev = i_node;
			i_node->next = new_fil;
		}
		i++;
	}
}

void	init_params(char **av, t_params *params)
{
	params->phil_n = (int) ft_atol(av[1]);
	if (params->phil_n < 1)
		simple_exit("Arg 1 (number of filo) must be int > 0", EXIT_FAILURE);
	params->ttd_max = ft_atol(av[2]);
	if (params->ttd_max < 1)
		simple_exit("Arg 2 (time_to_die) must be int > 0", EXIT_FAILURE);
	params->tte_max = ft_atol(av[3]);
	if (params->tte_max < 1)
		simple_exit("Arg 2 (time_to_eat) must be int > 0", EXIT_FAILURE);
	params->tts_max = ft_atol(av[4]);
	if (params->tts_max < 1)
		simple_exit("Arg 3 (time_to_sleep) must be int > 0", EXIT_FAILURE);
	if (av[4] && av[4][0])
	{
		params->tot_lunchs = ft_atol(av[5]);
		if (params->tot_lunchs < 1)
			simple_exit("Arg 4 (nbr of lunchs) must be int > 0", EXIT_FAILURE);
	}
	else
		params->tot_lunchs = -404;
	params->filos_lst = NULL;
	init_filos(params);
	if (params->filos_lst == NULL)
		simple_exit("Err : init filos", EXIT_FAILURE);
	set_table(params);
}
