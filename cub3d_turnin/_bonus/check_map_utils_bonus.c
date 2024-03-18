/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:22:34 by hgu               #+#    #+#             */
/*   Updated: 2024/01/30 19:13:03 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_map_line_valid(char *line, t_parse_flag *flag)
{
	int	i;

	i = -1;
	if (line[0] == '\n')
		return (1);
	while (line[++i])
	{
		if (line[i] == 'N' || line[i] == 'S' \
		|| line[i] == 'E' || line[i] == 'W')
		{
			if (flag->user_char != 0)
				ft_exit("Error : There are 2 or more users!!\n");
			flag->user_char = line[i];
		}
		if (line[i] == ' ' || line[i] == '1' || \
		line[i] == '0' || line[i] == 'N' || \
		line[i] == 'S' || line[i] == 'E' || line[i] == 'W' || line[i] == '\n')
			continue ;
		else
			return (1);
	}
	return (0);
}
