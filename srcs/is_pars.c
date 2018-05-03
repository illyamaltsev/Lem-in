/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 19:00:47 by imaltsev          #+#    #+#             */
/*   Updated: 2018/03/18 19:00:48 by imaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		is_start(t_lem **links)
{
	int i;

	i = 0;
	while (links[i] != NULL)
	{
		if (links[i]->status == 1)
			return (1);
		i++;
	}
	return (0);
}

int		is_room(char *str)
{
	int i;
	int spaces_counter;
	int numbers_counter;

	i = 0;
	spaces_counter = 0;
	numbers_counter = 0;
	if (str[0] == ' ')
		return (0);
	while (str[i] != '\0')
	{
		if (i != 0 && str[i] == ' ' && i++ != 0)
			spaces_counter++;
		else if (str[i] != 'L' && i == 0 && (numbers_counter++) != -1)
			while (str[i] != ' ' && str[i] != '\0')
				i++;
		else if (i != 0 && ft_isdigit(str[i]) && numbers_counter++ != 0)
			while (ft_isdigit(str[i]))
				i++;
		else if (str[i] != '\0')
			return (0);
	}
	if (spaces_counter == 2 && numbers_counter == 3)
		return (1);
	return (0);
}

int		is_way(char *str)
{
	int i;
	int point;
	int words_counter;

	words_counter = 0;
	point = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '-')
		{
			while (str[i] != '-' && str[i] != '\0')
				i++;
			words_counter++;
		}
		else
		{
			point++;
			i++;
		}
	}
	if (words_counter == 2 && point)
		return (1);
	return (0);
}
