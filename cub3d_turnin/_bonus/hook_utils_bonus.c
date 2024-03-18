/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:40:35 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/30 19:14:16 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	rotate_right(t_info *info, double angle)
{
	double	new_x;
	double	new_y;
	double	new_plane_x;
	double	new_plane_y;

	new_x = info->user->dir_x * cos(angle) - info->user->dir_y * sin(angle);
	new_y = info->user->dir_x * sin(angle) + info->user->dir_y * cos(angle);
	new_plane_x = info->user->plane_x * cos(angle) \
	- info->user->plane_y * sin(angle);
	new_plane_y = info->user->plane_x * sin(angle) \
	+ info->user->plane_y * cos(angle);
	info->user->dir_x = new_x;
	info->user->dir_y = new_y;
	info->user->plane_x = new_plane_x;
	info->user->plane_y = new_plane_y;
}

void	rotate_left(t_info *info, double angle)
{
	double	new_x;
	double	new_y;
	double	new_plane_x;
	double	new_plane_y;

	new_x = info->user->dir_x * cos(-angle) \
	- info->user->dir_y * sin(-angle);
	new_y = info->user->dir_x * sin(-angle) \
	+ info->user->dir_y * cos(-angle);
	new_plane_x = info->user->plane_x * cos(-angle) \
	- info->user->plane_y * sin(-angle);
	new_plane_y = info->user->plane_x * sin(-angle) \
	+ info->user->plane_y * cos(-angle);
	info->user->dir_x = new_x;
	info->user->dir_y = new_y;
	info->user->plane_x = new_plane_x;
	info->user->plane_y = new_plane_y;
}

int	check_wall(t_info *info, double mov_x, double mov_y)
{
	int	x;
	int	y;

	x = info->user->pos_x + mov_x;
	y = info->user->pos_y + mov_y;
	if (info->map[y][x] == '1' && info->map[(int)(info->user->pos_y)][x] != '1')
		return (2);
	if (info->map[y][x] == '1' && info->map[y][(int)(info->user->pos_x)] != '1')
		return (3);
	if (info->map[y][x] == '1')
		return (1);
	return (0);
}

int	win_close(t_info *info)
{
	mlx_destroy_image(info->mlx, info->img.img);
	mlx_destroy_window(info->mlx, info->mlx_win);
	free_dbptr(info->map);
	exit(0);
}
