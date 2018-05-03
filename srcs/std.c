/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 19:09:04 by imaltsev          #+#    #+#             */
/*   Updated: 2018/03/18 19:09:05 by imaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_rooms(char **f, char **s)
{
	ft_strdel(f);
	ft_strdel(s);
}

void	clear_flags(t_lem *lem)
{
	while (lem)
	{
		lem->flag = 0;
		lem = lem->next;
	}
}

int		helper(int i, int best, t_lem *lem)
{
	return (lem->links[i]->point < lem->links[best]->point
		&& lem->status != -1 && check_way(lem->links[i], NULL)
		&& lem->links[i]->point != -1);
}

int		stop_reading(char *line, int fd)
{
	ft_printf(
	"Reading was stopped, because this line -->[%s] non compliant!!\n", line);
	ft_strdel(&line);
	while (get_next_line(fd, &line))
		ft_strdel(&line);
	return (1);
}

int		check_algo(t_lem *lem)
{
	int i;

	if (lem->status == 1)
		return (1);
	lem->flag = 1;
	i = 0;
	while (lem->links && lem->links[i] != NULL)
	{
		if (lem->links[i]->flag != 1)
			return (check_algo(lem->links[i]));
		i++;
	}
	return (0);
}
