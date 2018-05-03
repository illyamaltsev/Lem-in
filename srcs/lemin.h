/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:35:30 by imaltsev          #+#    #+#             */
/*   Updated: 2018/03/12 15:35:32 by imaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "../libft/mylibft.h"
# include <fcntl.h>

int					g_ants;

typedef struct		s_lem
{
	char			*name;
	int				ant;
	struct s_lem	**links;
	struct s_lem	*next;
	struct s_lem	*start;
	int				status;
	int				x;
	int				y;
	int				point;
	int				flag;
}					t_lem;

void				error(t_lem *lem);
void				del_lem(t_lem *lem);

void				algoritm(t_lem *start, t_lem *end);
int					check_way(t_lem *lem, t_lem *prev_lem);

char				*get_s_room(char *str);
char				*get_f_room(char *str);
char				*get_name(char *str);
int					get_y(char *str);
int					get_x(char *str);

int					is_start(t_lem **links);
int					is_room(char *str);
int					is_way(char *str);

t_lem				*parsing(int fd);
t_lem				*join_s_to_f(char *f, char *s, t_lem *lem, int p);

void				analyse(t_lem **lem, int n);

t_lem				*add_ways(int fd, t_lem *lem, char *line, char *froom);
t_lem				**add_link(t_lem *link, t_lem **links);
t_lem				*add_new_room(t_lem *lem, char *str, int status);

int					stop_reading(char *line, int fd);
void				free_rooms(char **f, char **s);
void				clear_flags(t_lem *lem);
void				printlem(t_lem *lem);
int					check_algo(t_lem *lem);
int					helper(int i, int best, t_lem *lem);

void				validate(t_lem *lem);

void				paint_flags(t_lem *lem);

#endif
