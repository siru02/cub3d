/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:29:45 by hgu               #+#    #+#             */
/*   Updated: 2024/01/30 19:14:18 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_bfs(t_queue *q, t_info *info, int *dx, int *dy)
{
	int		i;
	int		new_x;
	int		new_y;

	info->copy_map = map_copy(info->map, info, -1, -1);
	while (!is_empty(q))
	{
		i = -1;
		while (++i < 8)
		{
			new_x = q->first->x + dx[i];
			new_y = q->first->y + dy[i];
			exit_case_check(info, new_x, new_y);
			if (!check_visited(info->copy_map, new_x, new_y, info) \
			&& check_zero(info->copy_map, new_x, new_y))
			{
				push(&q, q->first->x + dx[i], q->first->y + dy[i]);
				info->copy_map[new_y][new_x] = 'v';
			}
		}
		pop(&q);
	}
	free_dbptr(info->copy_map);
}

void	check_edge(t_info *info, int *dx, int *dy)
{
	info->copy_map = map_copy(info->map, info, -1, -1);
	check_first_line(info, dx, dy);
	check_last_line(info, dx, dy);
	check_left_line(info, dx, dy, -1);
	check_right_line(info, dx, dy, -1);
	free_dbptr(info->copy_map);
}

void	init_dx_dy(int *dx, int *dy)
{
	dx[0] = 1;
	dx[1] = 0;
	dx[2] = -1;
	dx[3] = 0;
	dx[4] = 1;
	dx[5] = 1;
	dx[6] = -1;
	dx[7] = -1;
	dy[0] = 0;
	dy[1] = 1;
	dy[2] = 0;
	dy[3] = -1;
	dy[4] = 1;
	dy[5] = -1;
	dy[6] = -1;
	dy[7] = 1;
}

void	locate_user(char **map, t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i] != NULL)
	{
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' \
			|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				info->user->pos_y = (double)i + 0.51;
				info->user->pos_x = (double)j + 0.51;
				return ;
			}
		}
	}
	free_dbptr(map);
	ft_exit("No user in the map\n");
}
