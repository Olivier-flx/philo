/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:17:09 by ofilloux          #+#    #+#             */
/*   Updated: 2024/10/25 19:28:57 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// void	set_table(t_params *params)
// {
// 	t_filo	*last_node;

// 	if (params->filos_lst == NULL)
// 		simple_exit("Err : init filos", EXIT_FAILURE);
// 	last_node = params->filos_lst;
// 	while (last_node->next)
// 		last_node = last_node->next;
// 	last_node->next = params->filos_lst;
// 	params->filos_lst->prev = last_node;
// }

// static t_filo	*create_filo_node(t_params *params, int i)
// {
// 	t_filo	*philo;

// 	philo = malloc(sizeof(t_filo));
// 	if (philo == NULL)
// 		free_lst_exit(params->filos_lst, EXIT_FAILURE, "Malloc err: filo node");
// 	philo->id = i + 1;
// 	philo->ttd = 0;
// 	philo->lunchs = 0;
// 	philo->is_dead = false;
// 	philo->thread = 0;
// 	philo->params = params;
// 	philo->next = NULL;
// 	philo->prev = NULL;
// 	return (philo);
// }

// void	init_filos(t_params *params)
// {
// 	int		i;
// 	t_filo	*new_fil;
// 	t_filo	*i_node;

// 	i = 0;
// 	new_fil = NULL;
// 	i_node = NULL;
// 	while (i < params->phil_n)
// 	{
// 		new_fil = create_filo_node(params, i);
// 		if (params->filos_lst == NULL)
// 		{
// 			params->filos_lst = new_fil;
// 			new_fil->prev = NULL;
// 		}
// 		else
// 		{
// 			i_node = params->filos_lst;
// 			while (i_node->next != NULL)
// 				i_node = i_node->next;
// 			new_fil->prev = i_node;
// 			i_node->next = new_fil;
// 		}
// 		i++;
// 	}
// }

void	init_filos_arr(t_params *params)
{
	int	i;

	i = 0;
	params->filo_arr = malloc (sizeof(t_filo_arr) * params->phil_n);
	if (params->filo_arr == NULL)
		simple_exit(" malloc Err : init filos arr", EXIT_FAILURE);
	while (i < params->phil_n)
	{
		params->filo_arr[i].thread = 0;
		params->filo_arr[i].params = params;
		params->filo_arr[i].id = i + 1;
		params->filo_arr[i].ttd = 0;
		params->filo_arr[i].lunchs = 0;
		ft_mutex_init(&params->filo_arr[i].fil_mtx, NULL, params);
		params->filo_arr[i].is_dead = false;
		params->filo_arr[i].left_fork = &params->forks2[i];
		params->filo_arr[i].right_fork = &params->forks2[(i + 1) % params->phil_n];
		i++;
	}
}

void	init_forks_params_mutexes(t_params *params)
{
	int	i;

	i = 0;
	ft_mutex_init(&(params->start_time_mutex), NULL, params);

	params->forks2 = malloc(sizeof(pthread_mutex_t) * params->phil_n);
	if (!params->forks2)
		clean_exit(params, EXIT_FAILURE, "malloc err forks");

	params->forks_initialized = malloc(sizeof(bool) * params->phil_n);
	if (!params->forks_initialized)
		clean_exit(params, EXIT_FAILURE, "malloc err forks_bool");

	while (i < params->phil_n)
	{
		ft_mutex_init(&(params->forks2[i]), NULL, params);
		params->forks_initialized[i] = true;
		i++;
	}
}


void	init_params(char **av, t_params *params)
{
	params->phil_n = (int) ft_atol(av[1]);
	if (params->phil_n < 1)
		simple_exit("Arg 1 (number of filo) must be int > 0", EXIT_FAILURE);
	params->ttd_max = (int) ft_atol(av[2]);
	if (params->ttd_max < 1)
		simple_exit("Arg 2 (time_to_die) must be int > 0", EXIT_FAILURE);
	params->time_to_eat = (int) ft_atol(av[3]);
	if (params->time_to_eat < 1)
		simple_exit("Arg 2 (time_to_eat) must be int > 0", EXIT_FAILURE);
	params->tts_max = (int) ft_atol(av[4]);
	if (params->tts_max < 1)
		simple_exit("Arg 3 (time_to_sleep) must be int > 0", EXIT_FAILURE);
	if (av[5] && av[5][0])
	{
		params->tot_lunchs = (int) ft_atol(av[5]);
		if (params->tot_lunchs < 0)
			simple_exit("Arg 4 (nbr of lunchs) must be int >= 0", EXIT_FAILURE);
	}
	else
		params->tot_lunchs = -1;
	params->start_time = -1;
	params->one_died = false;
	params->all_have_ate = false;
	params->dinner_is_over = false;
}
