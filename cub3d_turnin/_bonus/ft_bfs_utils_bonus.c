/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:30:45 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/30 19:14:03 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	**map_copy(char **src, t_info *info, int i, int j)
{
	char	**dst;

	dst = (char **)malloc(sizeof(char *) * info->row_cnt + 1);
	if (dst == NULL)
		exit(1);
	dst[info->row_cnt] = NULL;
	while (src[++i])
	{
		j = -1;
		dst[i] = malloc(info->max_col);
		if (dst[i] == NULL)
			exit(1);
		while (src[i][++j])
			dst[i][j] = src[i][j];
		j = -1;
		while (dst[i][++j] == ' ')
			dst[i][j] = '*';
		j = info->max_col - 2;
		while (dst[i][j] == ' ' || dst[i][j] == '\n')
			dst[i][j--] = '*';
		dst[i][info->max_col - 1] = '\0';
	}
	return (dst);
}

int	check_zero(char **copy_map, int new_x, int new_y)
{
	if (copy_map[new_y][new_x] == '0')
		return (1);
	return (0);
}

int	check_space(char **copy_map, int new_x, int new_y)
{
	if (copy_map[new_y][new_x] == ' ')
		return (1);
	return (0);
}

int	check_visited(char **copy_map, int new_x, int new_y, t_info *info)
{
	if (new_y < 0 || new_x < 0)
		ft_exit("out\n");
	if (new_y > info->row_cnt - 1 || new_x > info->max_col - 1)
		ft_exit("out\n");
	if (copy_map[new_y][new_x] == 'v')
		return (1);
	return (0);
}

void	exit_case_check(t_info *info, int new_x, int new_y)
{
	if (new_x < 0 || new_y < 0 || new_x > info->max_col - 2 \
	|| new_y > info->row_cnt - 1 || info->copy_map[new_y][new_x] == ' ' \
	|| info->copy_map[new_y][new_x] == '*')
	{
		free_dbptr(info->copy_map);
		free_dbptr(info->map);
		ft_exit("Error: map error\n");
	}
}
