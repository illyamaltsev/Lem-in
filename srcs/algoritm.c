/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algoritm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:41:25 by imaltsev          #+#    #+#             */
/*   Updated: 2018/03/14 17:41:27 by imaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_way(t_lem *lem, t_lem *prev_lem)
{
	int i;

	if (lem->flag == 1)
		return (0);
	if (lem->status == 1)
		return (1);
	if (is_start(lem->links))
		return (1);
	i = 0;
	while (lem->links[i] != NULL)
	{
		if (lem->links[i]->status != -1 && prev_lem &&
		!ft_strequ(lem->links[i]->name, prev_lem->name) &&
		check_way(lem->links[i], lem) == 1)
			return (1);
		else if (lem->links[i]->status != -1 && !prev_lem &&
			check_way(lem->links[i], lem) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	vacuum_help(t_lem *lem, int best)
{
	lem->links[best]->ant--;
	lem->ant = g_ants - lem->links[best]->ant;
	ft_printf("L%d-%s ", lem->ant, lem->name);
	lem->flag = 1;
}

void	vacuum(t_lem *lem, int best, int i)
{
	while ((i = -1) == -1)
	{
		best = 0;
		while (lem->links[++i] != NULL)
			if (helper(i, best, lem))
				best = i;
		if (lem->links[best]->status == 1)
		{
			if (lem->links[best]->ant > 0)
				vacuum_help(lem, best);
			return ;
		}
		else if (lem->links[best]->status != -1 && lem->links[best]->flag == 0)
		{
			lem->ant = lem->links[best]->ant;
			lem->links[best]->ant = 0;
			if (lem->ant != 0 && ft_printf("L%d-%s ", lem->ant, lem->name))
				lem->flag = 1;
			lem->flag = 1;
			lem = lem->links[best];
		}
		else
			return ;
	}
}

int		vac_end(t_lem *end)
{
	int i;
	int k;

	i = -1;
	while (end->links[++i] != NULL)
	{
		if (end->links[i]->status == 1)
		{
			k = 1;
			while (g_ants > end->ant && ft_printf("L%d-%s ", k, end->name))
			{
				end->ant = k;
				k++;
			}
			ft_printf("\n");
			return (0);
		}
		if (end->links[i]->ant != 0)
		{
			ft_printf("L%d-%s ", end->links[i]->ant, end->name);
			end->ant++;
			end->links[i]->ant = 0;
		}
	}
	return (1);
}

void	algoritm(t_lem *start, t_lem *end)
{
	int		i;
	t_lem	*end1;

	analyse(&start, 0);
	if (!check_algo(end) && ft_printf("Have not true way!!\n"))
		error(start->start);
	clear_flags(end->start);
	end1 = end;
	while (g_ants > end->ant && vac_end(end))
	{
		i = 0;
		paint_flags(end);
		while (end->links[i] != NULL)
		{
			if (end->links[i]->point != -1)
				vacuum(end->links[i], 0, 0);
			end = end1;
			i++;
		}
		clear_flags(end->start);
		ft_printf("\n");
		end = end1;
	}
}
