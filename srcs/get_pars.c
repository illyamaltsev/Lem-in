/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:55:59 by imaltsev          #+#    #+#             */
/*   Updated: 2018/03/18 18:56:00 by imaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char	*get_f_room(char *str)
{
	char	*new;
	int		i;

	i = 0;
	while (str[i] != '-')
		i++;
	new = malloc(sizeof(new) * (i + 1));
	i = 0;
	while (str[i] != '-')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*get_s_room(char *str)
{
	char	*new;
	int		i;

	while (*str != '-')
		str++;
	str++;
	new = malloc(sizeof(new) * (ft_strlen(str) + 1));
	i = 0;
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*get_name(char *str)
{
	char	*new;
	int		i;
	int		count;

	count = 0;
	while (str[count] != ' ')
		count++;
	new = malloc(sizeof(new) * (1 + count));
	i = 0;
	while (str[i] != ' ')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int		get_y(char *str)
{
	while (*str != ' ')
		str++;
	str++;
	while (*str != ' ' && *str != '\0')
		str++;
	str++;
	return (ft_atoi(str));
}

int		get_x(char *str)
{
	while (*str != ' ')
		str++;
	str++;
	return (ft_atoi(str));
}
