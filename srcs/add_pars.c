/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:42:32 by imaltsev          #+#    #+#             */
/*   Updated: 2018/03/18 18:42:35 by imaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_lem	*create_new(char *str, int status)
{
	t_lem	*new;

	new = malloc(sizeof(*new));
	new->name = get_name(str);
	new->ant = 0;
	new->next = NULL;
	new->x = get_x(str);
	new->y = get_y(str);
	new->status = status;
	new->links = NULL;
	new->point = -1;
	new->flag = 0;
	return (new);
}

void	check_way_room(char *f, char *s, t_lem *lem)
{
	int count_f;
	int count_s;

	count_f = 0;
	count_s = 0;
	while (lem)
	{
		if (ft_strequ(lem->name, f))
			count_f++;
		if (ft_strequ(lem->name, s))
			count_s++;
		lem = lem->next;
	}
	if (count_s != 1 || count_f != 1)
	{
		ft_printf("Not found way ""%s""-""%s""!!\n", f, s);
		error(lem);
	}
}

t_lem	*add_ways(int fd, t_lem *lem, char *line, char *froom)
{
	char	*sroom;

	ft_printf("%s\n", line);
	froom = get_f_room(line);
	sroom = get_s_room(line);
	check_way_room(froom, sroom, lem->start);
	lem = join_s_to_f(froom, sroom, lem->start, 0);
	free_rooms(&froom, &sroom);
	while (get_next_line(fd, &line))
	{
		if (line[0] == '#' && ft_printf("%s\n", line))
			ft_strdel(&line);
		else if (is_way(line) && ft_printf("%s\n", line)
			&& (froom = get_f_room(line)) != NULL)
		{
			sroom = get_s_room(line);
			check_way_room(froom, sroom, lem->start);
			ft_strdel(&line);
			lem = join_s_to_f(froom, sroom, lem->start, 0);
			free_rooms(&froom, &sroom);
		}
		else if (stop_reading(line, fd))
			return (lem->start);
	}
	return (lem->start);
}

t_lem	**add_link(t_lem *link, t_lem **links)
{
	t_lem	**new_links;
	int		i;

	i = 0;
	while (links[i] != NULL)
		i++;
	new_links = malloc(sizeof(new_links) * (i + 2));
	i = 0;
	while (links[i] != NULL)
	{
		new_links[i] = links[i];
		i++;
	}
	new_links[i] = link;
	new_links[i + 1] = NULL;
	free(links);
	return (new_links);
}

t_lem	*add_new_room(t_lem *lem, char *str, int status)
{
	t_lem	*new;

	if (lem == NULL)
	{
		lem = create_new(str, status);
		lem->start = lem;
	}
	else
	{
		while (lem->next)
			lem = lem->next;
		new = create_new(str, status);
		lem->next = new;
		new->start = lem->start;
		lem = new;
	}
	return (lem);
}
