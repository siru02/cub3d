/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_c_f_valid_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:11:33 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/30 19:12:37 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_ceiling_color_info(char **splits, t_info *info, t_parse_flag *flag)
{
	char	**color_splits;

	check_comma(splits[1]);
	color_splits = ft_split(splits[1], ',');
	if (color_splits[0] != NULL && color_splits[1] != NULL \
	&& color_splits[2] != NULL)
		info->c_color = create_trgb(ft_atoi(color_splits[0]), \
		ft_atoi(color_splits[1]), ft_atoi(color_splits[2]));
	else
	{
		free_dbptr(color_splits);
		return (1);
	}
	flag->ceiling = 1;
	free_dbptr(color_splits);
	return (0);
}

int	check_floor_color_info(char **splits, t_info *info, t_parse_flag *flag)
{
	char	**color_splits;

	check_comma(splits[1]);
	color_splits = ft_split(splits[1], ',');
	if (color_splits[0] != NULL && color_splits[1] != NULL \
	&& color_splits[2] != NULL)
		info->f_color = create_trgb(ft_atoi(color_splits[0]), \
		ft_atoi(color_splits[1]), ft_atoi(color_splits[2]));
	else
	{
		free_dbptr(color_splits);
		return (1);
	}
	flag->floor = 1;
	free_dbptr(color_splits);
	return (0);
}
