/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:04:07 by hgu               #+#    #+#             */
/*   Updated: 2024/01/30 19:51:14 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_line line, t_user *user, t_ray *ray, t_info *info)
{
	t_data	tex;

	if (ray->side == WALL_X)
	{
		if ((double)ray->map_x < user->pos_x)
			set_tex_info(&tex, &(info->west));
		else
			set_tex_info(&tex, &(info->east));
	}
	else
	{
		if ((double)ray->map_y < user->pos_y)
			set_tex_info(&tex, &(info->north));
		else
			set_tex_info(&tex, &(info->south));
	}
	tex.addr = mlx_get_data_addr(tex.img, &(tex.bits_per_pixel), \
	&(tex.line_length), &(tex.endian));
	select_tex_pixel(&line, ray, user, &tex);
	draw_vertical(line, ray, info, &tex);
}

void	select_tex_pixel(t_line *line, t_ray *ray, t_user *user, t_data *tex)
{
	double	wallx;

	if (ray->side == WALL_X)
		wallx = user->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wallx = (double)user->pos_x + \
		(double)ray->perp_wall_dist * (double)ray->ray_dir_x;
	wallx = wallx - floor(wallx);
		line->tex_x_point = (int)(wallx * tex->width);
	if (ray->side == WALL_X && ray->ray_dir_x > 0)
		line->tex_x_point = tex->width - line->tex_x_point - 1;
	if (ray->side == WALL_Y && ray->ray_dir_y < 0)
		line->tex_x_point = tex->width - line->tex_x_point - 1;
}

void	draw_vertical(t_line line, t_ray *ray, t_info *info, t_data *tex)
{
	char	*target_ptr;
	int		y;
	double	step;
	double	tex_pos;

	y = -1;
	while (++y < line.draw_start)
		my_mlx_pixel_put(&(info->img), (int)ray->x, y, info->c_color);
	step = 1.0 * (double)tex->height / (double)line.height;
	tex_pos = (line.draw_start - SCREEN_HEIGHT / 2 + line.height / 2) * step;
	while (y <= line.draw_end)
	{
		if (tex_pos >= tex->height)
			tex_pos = tex->height - 1;
		if (tex_pos < 0)
			tex_pos = 0;
		target_ptr = tex->addr + tex->line_length * (int)tex_pos + (tex->\
		width - line.tex_x_point) * (tex->bits_per_pixel / 8);
		my_mlx_pixel_put(&(info->img), (int)ray->x, y, \
		*(unsigned int *)target_ptr);
		tex_pos += step;
		y++;
	}
	while (y < SCREEN_HEIGHT)
		my_mlx_pixel_put(&(info->img), (int)ray->x, y++, info->f_color);
}
