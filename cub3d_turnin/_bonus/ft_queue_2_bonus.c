/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:42:20 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/30 19:14:11 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_empty(t_queue *q)
{
	if (q == NULL)
		return (1);
	if (q->first == NULL)
		return (1);
	return (0);
}

int	is_in_queue(t_queue *q, int new_x, int new_y)
{
	t_node	*tmp;

	if (q == NULL)
		return (0);
	if (q->first == NULL)
		return (0);
	tmp = q->first;
	if (tmp->x == new_x && tmp->y == new_y)
		return (1);
	tmp = tmp->next;
	while (tmp != NULL && tmp->next != q->first)
	{
		if (tmp->x == new_x && tmp->y == new_y)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
