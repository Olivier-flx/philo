/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:45:07 by ofilloux          #+#    #+#             */
/*   Updated: 2024/09/13 19:35:06 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	simple_exit(char *msg, int exit_num)
{
	if (exit_num != 0)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(exit_num);
}

int	get_lst_len(t_filo *filos_lst)
{
	t_filo			*i_n;
	unsigned int	max;

	i_n = filos_lst;
	max = 0;
	while (i_n && i_n->id > max)
	{
		if (i_n->id > max)
			max = i_n->id;
		i_n = i_n->next;
	}
	return ((int) max);
}

void	free_lst_exit(t_filo *filos_lst, int exit_num)
{
	t_filo	*tmp;
	int		i;
	int		lst_size;

	tmp = NULL;
	i = 0;
	if (filos_lst != NULL)
	{
		lst_size = get_lst_len(filos_lst);
		while (filos_lst && i < lst_size)
		{
			tmp = filos_lst->next;
			free (filos_lst);
			filos_lst = tmp;
			i++;
		}
		filos_lst = NULL;
	}
	if (exit_num != 0)
		simple_exit("List error", EXIT_FAILURE);
	else
		exit(0);
}
