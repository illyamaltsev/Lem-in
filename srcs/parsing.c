/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:19:38 by imaltsev          #+#    #+#             */
/*   Updated: 2018/03/18 18:19:39 by imaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		pars_ants(int fd)
{
	char	*line;
	int		ants;

	ants = 0;
	line = NULL;
	while (1)
	{
		get_next_line(fd, &line);
		if (!line)
			error(NULL);
		if (ft_isstrofdigit(line) && (ants = ft_atoi(line)) > 0)
		{
			ft_strdel(&line);
			return (ants);
		}
		if (line[0] != '#')
		{
			ft_strdel(&line);
			error(NULL);
		}
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
	return (ants);
}

t_lem	*pars_room(int fd, t_lem *lem, char *line, int status)
{
	t_lem	*ret;
	char	*str;

	str = NULL;
	if (status == 1 || status == -1)
	{
		ft_printf("%s\n", line);
		while (get_next_line(fd, &line) && line[0] == '#')
		{
			if (ft_strnequ(line, "##start", 7) || ft_strnequ(line, "##end", 5))
			{
				ft_strdel(&line);
				error(lem);
			}
			ft_printf("%s\n", line);
			ft_strdel(&line);
		}
		str = line;
		if (!is_room(line))
			error(lem);
	}
	ret = add_new_room(lem, line, status);
	if (ft_printf("%s\n", line) && str)
		ft_strdel(&str);
	return (ret);
}

t_lem	*join_s_to_f(char *f, char *s, t_lem *lem, int p)
{
	t_lem	*tmp;

	tmp = lem;
	while (!ft_strequ(tmp->name, s))
		tmp = tmp->next;
	while (!ft_strequ(lem->name, f))
		lem = lem->next;
	if (!lem->links)
	{
		lem->links = malloc(sizeof(lem->links) * 2);
		lem->links[0] = tmp;
		lem->links[1] = NULL;
	}
	else
		lem->links = add_link(tmp, lem->links);
	if (p == 0)
		lem = join_s_to_f(s, f, lem->start, 1);
	return (lem->start);
}

t_lem	*pars_rooms(int fd, t_lem *lem)
{
	char	*line;
	int		point;

	point = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_strequ(line, "##start"))
			lem = pars_room(fd, lem, line, 1);
		else if (ft_strequ(line, "##end"))
			lem = pars_room(fd, lem, line, -1);
		else if (line[0] == '#')
			ft_printf("%s\n", line);
		else if (is_room(line))
			lem = pars_room(fd, lem, line, 0);
		else if (is_way(line) && lem && (point++) != -1)
			lem = add_ways(fd, lem, line, NULL);
		else if (ft_printf("Something wrong with this line --> [%s]\n",
			line) != 0)
			error(lem);
		ft_strdel(&line);
		line = NULL;
	}
	if (!point && ft_printf("Have not ways between rooms!!\n") != 0)
		error(lem);
	return (lem->start);
}

t_lem	*parsing(int fd)
{
	t_lem	*lem;
	int		ants;

	lem = NULL;
	ants = pars_ants(fd);
	ft_printf("%d\n", ants);
	g_ants = ants;
	lem = pars_rooms(fd, lem);
	return (lem);
}
