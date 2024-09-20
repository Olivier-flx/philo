/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:43:58 by ofilloux          #+#    #+#             */
/*   Updated: 2024/09/18 17:32:10 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// NOT USED
char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		i;

	if (!s1 && s1[0] == '\0')
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
		i++;
	cpy = malloc ((i + 1) * sizeof (char));
	if (!cpy)
		return (NULL);
	cpy[i--] = '\0';
	while (i >= 0)
	{
		cpy[i] = s1[i];
		i--;
	}
	return (cpy);
}

//USED
size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

//USED
bool	contains_letter(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] >= 21 && s[i] <= 42) || s[i] == 44 || s[i] == 46 \
			|| s[i] == 47 || s[i] >= 58)
			return (true);
		i++;
	}
	return (false);
}

//USED
long	ft_atol(char *s)
{
	int		i;
	int		negative;
	long	number;

	if (contains_letter(s))
		return (-404);
	i = 0;
	negative = 1;
	number = 0;
	while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			negative = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		number = number * 10 + (s[i] - '0');
		if (number > INT_MAX)
			return (-404);
		i++;
	}
	return (number * negative);
}

// NOT USED
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l1;
	int		l2;
	int		t;
	char	*nw;

	l1 = (int)ft_strlen(s1);
	l2 = (int)ft_strlen(s2);
	nw = malloc((l1 + l2 + 1) * sizeof(char));
	if (!nw)
		return (NULL);
	t = 0;
	while (t <= l1 - 1 && s1[t])
	{
		nw[t] = s1[t];
		t++;
	}
	while (t <= (l1 + l2 - 1) && s2[t - l1])
	{
		nw[t] = s2[t - l1];
		t++;
	}
	nw[t] = '\0';
	return (nw);
}

// USED
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((const char) s1[i] != (const char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}
