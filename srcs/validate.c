/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 17:31:49 by imaltsev          #+#    #+#             */
/*   Updated: 2018/03/23 17:31:50 by imaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		validate_room(t_lem *lem, t_lem *tmp)
{
	int count;

	while (lem)
	{
		count = 0;
		tmp = lem->start;
		while (tmp)
		{
			if (ft_strequ(tmp->name, lem->name))
				count++;
			tmp = tmp->next;
		}
		if (count != 1)
			error(lem->start);
		lem = lem->next;
	}
}

void	validate_start(t_lem *lem)
{
	int count;

	count = 0;
	while (lem)
	{
		if (lem->status == 1)
			count++;
		lem = lem->next;
	}
	if (count != 1)
	{
		ft_printf("Quantity of start rooms must be 1, not %d\n", count);
		error(lem);
	}
}

void	validate_end(t_lem *lem)
{
	int count;

	count = 0;
	while (lem)
	{
		if (lem->status == -1)
			count++;
		lem = lem->next;
	}
	if (count != 1)
	{
		ft_printf("Quantity of end rooms must be 1, not %d\n", count);
		error(lem);
	}
}

void	validate_koord(t_lem *lem, t_lem *tmp)
{
	while (lem)
	{
		tmp = lem->start;
		while (tmp)
		{
			if (lem->x == tmp->x && lem->y == tmp->y
				&& !ft_strequ(lem->name, tmp->name))
				error(tmp);
			tmp = tmp->next;
		}
		lem = lem->next;
	}
}

void	validate(t_lem *lem)
{
	int i;

	validate_start(lem->start);
	validate_end(lem->start);
	i = 0;
	while (lem->status != 1)
		lem = lem->next;
	if (!lem->links)
		error(lem);
	validate_koord(lem->start, lem->start);
	validate_room(lem->start, lem->start);
}
