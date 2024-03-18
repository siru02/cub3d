/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_edge_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:18:52 by hgu               #+#    #+#             */
/*   Updated: 2024/01/29 16:01:15 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_left_line(t_info *info, int *dx, int *dy, int idx)
{
	t_queue	*q;
	int		x;

	q = NULL;
	while (++idx < info->row_cnt)
	{
		x = -1;
		if (info->copy_map[idx][++x] == '0')
		{
			free_dbptr(info->copy_map);
			free_dbptr(info->map);
			ft_exit ("Error: map is not closed\n");
		}
		else if (info->copy_map[idx][x] == ' ')
		{
			push(&q, x, idx);
			space_bfs(&q, info, dx, dy);
		}
		else if (info->copy_map[idx][x] == '*')
		{
			push(&q, x, idx);
			space_bfs(&q, info, dx, dy);
		}
	}
}

void	check_right_line(t_info *info, int *dx, int *dy, int idx)
{
	t_queue	*q;
	int		x;

	q = NULL;
	while (++idx < info->row_cnt)
	{
		x = info->max_col - 1;
		if (info->copy_map[idx][--x] == '0')
		{
			free_dbptr(info->copy_map);
			free_dbptr(info->map);
			ft_exit ("Error: map is not closed\n");
		}
		else if (info->copy_map[idx][x] == ' ')
		{
			push(&q, x, idx);
			space_bfs(&q, info, dx, dy);
		}
		else if (info->copy_map[idx][x] == '*')
		{
			push(&q, x, idx);
			space_bfs(&q, info, dx, dy);
		}
	}
}

void	check_first_line(t_info *info, int *dx, int *dy)
{
	t_queue	*q;
	int		idx;

	idx = 0;
	q = NULL;
	while (++idx < info->max_col - 2)
	{
		if (info->copy_map[0][idx] == '0')
		{
			free_dbptr(info->copy_map);
			free_dbptr(info->map);
			ft_exit ("Error: map is not closed\n");
		}
		else if (info->copy_map[0][idx] == ' ')
		{
			push(&q, idx, 0);
			space_bfs(&q, info, dx, dy);
		}
		else if (info->copy_map[0][idx] == '*')
		{
			push(&q, idx, 0);
			space_bfs(&q, info, dx, dy);
		}
	}
}

void	check_last_line(t_info *info, int *dx, int *dy)
{
	t_queue	*q;
	int		idx;

	idx = 0;
	q = NULL;
	while (++idx < info->max_col - 2)
	{
		if (info->copy_map[info->row_cnt - 1][idx] == '0')
		{
			free_dbptr(info->copy_map);
			free_dbptr(info->map);
			ft_exit ("Error: map is not closed\n");
		}
		else if (info->copy_map[info->row_cnt - 1][idx] == ' ')
		{
			push(&q, idx, info->row_cnt - 1);
			space_bfs(&q, info, dx, dy);
		}
	}
}

void	space_bfs(t_queue **q, t_info *info, int *dx, int *dy)
{
	int	i;
	int	new_x;
	int	new_y;

	while (!is_empty(*q))
	{
		if (info->copy_map[(*q)->first->y][(*q)->first->x] == '0')
			space_bfs_exit (info->copy_map, info->map, \
			"Error: map_condition_error\n");
		info->copy_map[(*q)->first->y][(*q)->first->x] = 'v';
		i = -1;
		while (++i < 8)
		{
			new_x = (*q)->first->x + dx[i];
			new_y = (*q)->first->y + dy[i];
			if (new_x < 0 || new_y < 0 || new_x > info->max_col - 2 \
			|| new_y > info->row_cnt - 1)
				continue ;
			if (!is_in_queue(*q, new_x, new_y) && info->copy_map[new_y][new_x] \
			!= 'v' && info->copy_map[new_y][new_x] != '1')
				push(q, new_x, new_y);
		}
		pop(q);
	}
}
