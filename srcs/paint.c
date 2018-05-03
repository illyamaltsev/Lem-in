/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 16:01:08 by imaltsev          #+#    #+#             */
/*   Updated: 2018/03/29 16:01:10 by imaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	paint(t_lem *lem)
{
	int best;
	int i;

	while (1)
	{
		best = 0;
		i = 0;
		while (lem->links[++i] != NULL)
			if (lem->links[i]->point < lem->links[best]->point &&
			lem->status != -1 && lem->links[i]->point != -1
			&& lem->links[i]->flag == 0)
				best = i;
		if (lem->links[best]->status != -1 && lem->links[best]->flag == 0)
		{
			lem->flag = 1;
			lem = lem->links[best];
		}
		else
			return ;
	}
}

void	rev_flags(t_lem *lem)
{
	while (lem)
	{
		if (lem->status == 0)
		{
			if (lem->flag == 1)
				lem->flag = 0;
			else
				lem->flag = 1;
		}
		lem = lem->next;
	}
}

void	paint_flags(t_lem *lem)
{
	int i;

	i = 0;
	while (lem->links[i] != NULL)
	{
		paint(lem->links[i]);
		i++;
	}
	rev_flags(lem->start);
}
