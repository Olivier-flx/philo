/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:36:16 by ofilloux          #+#    #+#             */
/*   Updated: 2024/10/25 21:32:57 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// s'il n'y a qu'un seul philosophe

// synchroniser de début du repas et donc tous les threads pour que tous
	//les philos commencent leur repas en même temps

// void	*eat_or_not(void *arg) //// NE MARCHE PAS
// {
// 	t_filo	*filo;

// 	filo = (t_filo *) arg;
// 	while (1)
//     {
//         ft_mutex_lock(&(filo->params->start_time_mutex), filo->params);
//         if (filo->params->start_time != -1)
//         {
//             ft_mutex_unlock(&(filo->params->start_time_mutex), filo->params);
//             break; // Quitter la boucle si start_time est initialisé
//         }
//         ft_mutex_unlock(&(filo->params->start_time_mutex), filo->params);
//         usleep(200000); // Délai pour éviter une boucle d'attente serrée
//     }
// 	while (!is_diner_over(filo->params))
// 	{
// 		if (filo->lunchs == filo->params->tot_lunchs)
// 			break ;
// 		eat(filo, filo->params);
// 		sleeping(filo, filo->params);
// 		think(filo, filo->params);
// 	}
// 	//pthread_mutex_destroy(filo->fork); // to  Use or not ? Use the custom one or not
// 	return (NULL);
// }



// void	*eat_or_not(void *arg)
// {
// 	t_filo_arr	*filo;

// 	filo = (t_filo_arr *) arg;
// 	pthread_mutex_lock(&(filo->params->start_time_mutex));
// 	while (filo->params->start_time == -1)
// 	{
// 		pthread_mutex_unlock(&(filo->params->start_time_mutex));
// 		usleep(50);
// 		pthread_mutex_lock(&(filo->params->start_time_mutex));
// 	}
// 	pthread_mutex_unlock(&(filo->params->start_time_mutex));
// 	//  filo->ttd = get_m_time(filo->params);
// 	//filo->ttd = get_m_time(filo->params);
// 	ft_mutex_lock(&filo->fil_mtx, filo->params);
// 	 filo->ttd = get_m_time(filo->params);
// 	  printf("---- in routine filo->ttd  %li\n", filo->ttd);
// 	ft_mutex_unlock(&filo->fil_mtx, filo->params);
// 	while (!is_diner_over(filo->params))
// 	{
// 		pthread_mutex_lock(&(filo->params->start_time_mutex));
// 		if (filo->params->one_died || filo->lunchs == filo->params->tot_lunchs)
// 		{
// 			pthread_mutex_unlock(&(filo->params->start_time_mutex));
// 			break ;
// 		}
// 		pthread_mutex_unlock(&(filo->params->start_time_mutex));
// 		eat(filo, filo->params);
// 		sleeping(filo, filo->params);
// 		think(filo, filo->params);
// 	}
// 	return (NULL);
// }


void	*eat_or_not(void *arg)
{
	t_filo_arr	*filo;

	filo = (t_filo_arr *) arg;
	pthread_mutex_lock(&(filo->params->start_time_mutex));
	while (filo->params->start_time == -1)
	{
		pthread_mutex_unlock(&(filo->params->start_time_mutex));
		usleep(10);
		pthread_mutex_lock(&(filo->params->start_time_mutex));
	}
	pthread_mutex_unlock(&(filo->params->start_time_mutex));

	ft_mutex_lock(&filo->fil_mtx, filo->params); // pas sur que ce siot utile
	filo->ttd = get_m_time(filo->params);
	//printf("---- in routine filo->ttd  %li\n", filo->ttd);
	ft_mutex_unlock(&filo->fil_mtx, filo->params); // pas sur que ce siot utile


	while (true)
	{
		pthread_mutex_lock(&(filo->params->start_time_mutex));
//		printf("bool params->dinner_is_over : %d \n", filo->params->dinner_is_over);
		if (filo->params->dinner_is_over)
		{
			pthread_mutex_unlock(&(filo->params->start_time_mutex));
			break ;
		}
		pthread_mutex_unlock(&(filo->params->start_time_mutex));
		eat(filo, filo->params);
		sleeping(filo, filo->params);
		think(filo, filo->params);
	}
	return (NULL);
}

void	*fake(void *arg)
{
	t_filo_arr	*filo;

	filo = (t_filo_arr *) arg;
	if (filo)
		return (NULL);
	else
		return (NULL);
}

void	one_philo_at_table(t_params *params)
{
	if (pthread_create(&params->filo_arr[0].thread, NULL, &fake, &params->filo_arr[0]) != 0)
			clean_exit(params, EXIT_FAILURE, "1 filo thread create err");
	set_simulation_start_time(params);
	timestamp_msg(&params->filo_arr[0], "fork");
	msleep(params->ttd_max);
	timestamp_msg(&params->filo_arr[0], "die");
	pthread_detach(params->filo_arr[0].thread);

	clean_exit(params, EXIT_SUCCESS, NULL);
}

void	lets_eat(t_params *params)
{
	int		i;

	if (params->phil_n == 1)
		one_philo_at_table(params);
	i = 0;
	while (i < params->phil_n)
	{
		if (pthread_create(&params->filo_arr[i].thread, NULL, &eat_or_not, &params->filo_arr[i]) != 0)
			clean_exit(params, EXIT_FAILURE, "filo thread create err");
		i++;
	}
	set_simulation_start_time(params);
	while (true)
	{
		usleep(10);
		pthread_mutex_lock(&params->start_time_mutex);
		if (params->dinner_is_over && params->start_time >= 0)
		{
			pthread_mutex_unlock(&params->start_time_mutex);
			break ;
		}
		if (params->start_time >= 0)
		{
			pthread_mutex_unlock(&params->start_time_mutex);
			is_diner_over2(params);
		}
		else
			pthread_mutex_unlock(&params->start_time_mutex);

	}
	i = -1;
	while (++i < params->phil_n)
		pthread_join(params->filo_arr[i].thread, NULL);
}

// void	lets_eat(t_params *params)
// {
// 	t_filo	*i_node;
// 	int		i;

// 	if (params->phil_n == 0)
// 		one_philo_at_table(); // TODO
// 	i_node = params->filos_lst;
// 	i = 1;
// 	while (i <= params->phil_n)
// 	{
// 		i++;
// 		ft_mutex_init(&(i_node->fork), NULL, params);
// 		printf("hola philo %i\n", i_node->id);
// 		if (pthread_create(&i_node->thread, NULL, &eat_or_not, i_node) != 0)
// 			free_lst_exit(params->filos_lst, EXIT_FAILURE, "pthread_create err");
// 		i_node = i_node->next;
// 	}
// 	set_simulation_start_time(params); // simulation can start // Protect is with a mutex ??

// }
