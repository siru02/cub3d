/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:24:39 by hgu               #+#    #+#             */
/*   Updated: 2024/01/30 19:54:12 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	key_handler(int key_code, t_info *info)
{
	if (key_code == 53)
		win_close(info);
	mlx_destroy_image(info->mlx, info->img.img);
	info->img.img = mlx_new_image(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	info->img.addr = mlx_get_data_addr(info->img.img, \
	&(info->img.bits_per_pixel), &(info->img.line_length), &(info->img.endian));
	if (key_code == KEY_W)
		move_up_down(info, key_code);
	else if (key_code == KEY_S)
		move_up_down(info, key_code);
	else if (key_code == KEY_A)
		move_side(info, key_code, 0, 0);
	else if (key_code == KEY_D)
		move_side(info, key_code, 0, 0);
	else if (key_code == KEY_LEFT)
		camera_rotate(info, key_code);
	else if (key_code == KEY_RIGHT)
		camera_rotate(info, key_code);
	if (raycasting(info, info->user, info->ray) == 1)
		return (1);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img.img, 0, 0);
	return (0);
}

void	move_up_down(t_info *info, int key_code)
{
	int		flag;
	double	dir_x;
	double	dir_y;

	dir_x = info->user->dir_x;
	dir_y = info->user->dir_y;
	if (key_code == KEY_S)
	{
		dir_x = info->user->dir_x * -1;
		dir_y = info->user->dir_y * -1;
	}
	flag = check_wall(info, dir_x * 0.3, dir_y * 0.3);
	if (flag == 2)
		info->user->pos_x = info->user->pos_x + dir_x * 0.15;
	else if (flag == 3)
		info->user->pos_y = info->user->pos_y + dir_y * 0.15;
	else if (flag == 1)
		return ;
	else
	{
		info->user->pos_x = info->user->pos_x + dir_x * 0.15;
		info->user->pos_y = info->user->pos_y + dir_y * 0.15;
	}
	return ;
}

void	move_side(t_info *info, int key_code, double mov_x, double mov_y)
{
	int		flag;

	mov_x = info->user->dir_x * cos(M_PI / 2) \
	+ info->user->dir_y * sin(M_PI / 2);
	mov_y = -info->user->dir_x * sin(M_PI / 2) \
	+ info->user->dir_y * cos(M_PI / 2);
	if (key_code == KEY_D)
	{
		mov_x = info->user->dir_x * cos(M_PI / 2) \
		- info->user->dir_y * sin(M_PI / 2);
		mov_y = info->user->dir_x * sin(M_PI / 2) \
		+ info->user->dir_y * cos(M_PI / 2);
	}
	flag = check_wall(info, mov_x * 0.3, mov_y * 0.3);
	if (flag == 1)
		return ;
	if (flag == 2)
		info->user->pos_x += mov_x * 0.15;
	else if (flag == 3)
		info->user->pos_y += mov_y * 0.15;
	else
	{
		info->user->pos_x += mov_x * 0.15;
		info->user->pos_y += mov_y * 0.15;
	}
}

void	camera_rotate(t_info *info, int key_code)
{
	double	angle;

	angle = M_PI / 60;
	if (key_code == KEY_RIGHT)
		rotate_right(info, angle);
	else if (key_code == KEY_LEFT)
		rotate_left(info, angle);
}

int	mouse_handler(int x, int y, t_info *info)
{
	double		new_x;
	double		new_plane_x;
	double		angle;

	if (x >= info->cam.x && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		angle = M_PI / 60;
	else if (x >= 0 && x < info->cam.x && y >= 0 && y < SCREEN_HEIGHT)
		angle = -M_PI / 60;
	else
		return (1);
	new_x = info->user->dir_x * cos(angle) - info->user->dir_y * sin(angle);
	info->user->dir_y = \
	info->user->dir_x * sin(angle) + info->user->dir_y * cos(angle);
	new_plane_x = info->user->plane_x * cos(angle) \
	- info->user->plane_y * sin(angle);
	info->user->plane_y = \
	info->user->plane_x * sin(angle) + info->user->plane_y * cos(angle);
	info->cam.x = x;
	info->user->dir_x = new_x;
	info->user->plane_x = new_plane_x;
	if (raycasting(info, info->user, info->ray) == 1)
		return (1);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img.img, 0, 0);
	return (0);
}
