/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tex_valid_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:54:57 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/30 18:48:51 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_img(t_data *dir, t_info *info, char *str, int *flag_dir)
{
	dir->img = mlx_xpm_file_to_image \
	(info->mlx, str, &(dir->width), &(dir->height));
	if (*flag_dir == 1)
		ft_exit("Error: Duplicate declaration error.");
	*flag_dir = 1;
	return (0);
}

int	check_dir_valid(char **splits, t_info *info, char *line, t_parse_flag *flag)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (set_img(&(info->north), info, splits[1], &(flag->north)));
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (set_img(&(info->south), info, splits[1], &(flag->south)));
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (set_img(&(info->west), info, splits[1], &(flag->west)));
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (set_img(&(info->east), info, splits[1], &(flag->east)));
	return (1);
}

int	create_trgb(int red, int green, int blue)
{
	int	color;

	if (red > 255 || green > 255 || blue > 255 || red < 0 || \
	green < 0 || blue < 0)
	{
		printf("invalid color value\n");
		exit (1);
	}
	red = red << 16;
	green = green << 8;
	color = red + green + blue;
	return (color);
}

void	check_comma(char *str)
{
	int	cnt;

	cnt = 0;
	while (*str)
	{
		if (*str == ',')
			cnt++;
		str++;
	}
	if (cnt != 2)
		ft_exit("Error : color format is wrong\n");
}

int	check_c_f_valid(char **splits, t_info *info, char *line, t_parse_flag *flag)
{
	if (line[0] == 'C' && line[1] == ' ' && splits[2] == NULL)
	{
		if (check_ceiling_color_info(splits, info, flag))
		{
			close(info->tmp_fd);
			free(splits);
			free(line);
			ft_exit("Error : ceiling color format is wrong\n");
		}
		return (0);
	}
	else if (line[0] == 'F' && line[1] == ' ' && splits[2] == NULL)
	{
		if (check_floor_color_info(splits, info, flag))
		{
			close(info->tmp_fd);
			free(splits);
			free(line);
			ft_exit("Error : floor color format is wrong\n");
		}
		return (0);
	}
	return (1);
}
