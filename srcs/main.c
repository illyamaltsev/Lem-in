/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:33:51 by imaltsev          #+#    #+#             */
/*   Updated: 2018/03/12 15:33:54 by imaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	error(t_lem *lem)
{
	ft_printf("ERROR\n");
	if (lem)
		lem = lem->start;
	del_lem(lem);
	exit(1);
}

void	del_lem(t_lem *lem)
{
	t_lem *tmp;

	while (lem)
	{
		ft_strdel(&lem->name);
		if (lem->links != NULL)
			free(lem->links);
		lem->links = NULL;
		tmp = lem;
		free(lem);
		lem = NULL;
		lem = tmp->next;
	}
	lem = NULL;
}

int		main(int argc, char **argv)
{
	int		fd;
	t_lem	*lem;
	t_lem	*start;
	t_lem	*end;

	fd = 0;
	lem = NULL;
	argc = 1;
	argv = NULL;
	lem = parsing(fd);
	ft_printf("\n");
	validate(lem->start);
	lem = lem->start;
	while (lem && lem->status != 1)
		lem = lem->next;
	lem->ant = g_ants;
	start = lem;
	lem = lem->start;
	while (lem && lem->status != -1)
		lem = lem->next;
	end = lem;
	algoritm(start, end);
	del_lem(lem);
}
