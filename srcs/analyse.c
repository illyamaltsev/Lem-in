/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:35:35 by imaltsev          #+#    #+#             */
/*   Updated: 2018/03/18 18:35:36 by imaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	analyse(t_lem **lem, int n)
{
	int i;

	if (n != 0 && ((*lem)->status == -1 || (*lem)->status == 1))
	{
		(*lem)->point = n;
		return ;
	}
	if ((*lem)->point > n || (*lem)->point == -1)
		(*lem)->point = n;
	else
		return ;
	i = 0;
	while ((*lem)->links[i])
	{
		if ((*lem)->links[i]->status != 1)
			analyse(&(*lem)->links[i], n + 1);
		i++;
	}
}
