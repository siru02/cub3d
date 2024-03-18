/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:42:02 by hgu               #+#    #+#             */
/*   Updated: 2024/01/29 17:00:13 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_name(char *argv)
{
	int	len;

	len = ft_strlen(argv);
	if (len < 4)
		return (0);
	if (argv[len - 1] != 'b' && argv[len - 2] != 'u' \
	&& argv[len - 3] != 'c' && argv[len - 4] != '.')
		return (1);
	return (0);
}

void	fill_space(char *map, int max_col)
{
	int	len;

	len = ft_strlen(map) - 1;
	if (map[len] != '\n')
		len++;
	while (len < max_col)
		map[len++] = ' ';
	map[max_col - 1] = '\0';
	return ;
}

void	free_dbptr(char **dbptr)
{
	int	i;

	i = -1;
	while (dbptr[++i])
		free(dbptr[i]);
	free(dbptr);
}

void	validation_error(char *error_msg, char **splits, char *line, int fd)
{
	if (splits != NULL)
		free_dbptr(splits);
	free(line);
	printf("%s\n", error_msg);
	close(fd);
	exit (1);
}

int	check_flag(t_parse_flag *flag)
{
	if (flag->east == 0 || flag->west == 0 || flag->south == 0 \
	|| flag->north == 0 || flag->ceiling == 0 || flag->floor == 0)
		return (0);
	return (1);
}
