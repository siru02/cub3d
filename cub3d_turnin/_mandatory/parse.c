/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:57:10 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/30 13:43:54 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing(char *argv, t_info *info)
{
	int				fd;
	t_parse_flag	flag;
	char			*line;

	if (check_name(argv))
		ft_exit("Error : not a .cub file\n");
	init_flag(&flag);
	info->row_cnt = 0;
	info->max_col = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_exit("Error : no such file\n");
	info->tmp_fd = fd;
	check_tex_valid(fd, info, &flag, &line);
	check_map(fd, info, &line, &flag);
	close (fd);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		free(info->map);
		ft_exit("Error : no such file\n");
	}
	make_map(fd, info, &line, &flag);
	close(fd);
	is_map_closed(info);
}

void	check_map(int fd, t_info *info, char **line, t_parse_flag *flag)
{
	while ((*line)[0] == '\n')
	{
		free (*line);
		*line = get_next_line(fd);
		flag->map_start_line++;
	}
	while (*line)
	{
		if (check_map_line_valid(*line, flag))
			validation_error("Error: map error\n", NULL, *line, fd);
		if ((size_t)(info->max_col) < ft_strlen(*line))
			info->max_col = (int)ft_strlen(*line);
		free (*line);
		*line = get_next_line(fd);
		(info->row_cnt)++;
	}
	info->map = (char **)malloc(sizeof(char *) * (info->row_cnt + 1));
	if (info->map == NULL)
		ft_exit("Error: malloc\n");
	info->map[info->row_cnt] = NULL;
	free(*line);
}

void	make_map(int fd, t_info *info, char **line, t_parse_flag *flag)
{
	int	i;

	i = -1;
	while (++i < flag->map_start_line)
	{
		*line = get_next_line(fd);
		free(*line);
	}
	*line = get_next_line(fd);
	i = 0;
	while (*line)
	{
		info->map[i] = (char *)malloc(sizeof(char) * (info->max_col));
		if (info->map[i] == NULL)
			validation_error("Error: map_malloc\n", info->map, *line, fd);
		ft_strlcpy(info->map[i], *line, info->max_col);
		if (ft_strlen(*line) < (size_t)(info->max_col - 1))
			fill_space(info->map[i], info->max_col);
		free(*line);
		*line = get_next_line(fd);
		i++;
	}
}

void	check_tex_valid(int fd, t_info *info, t_parse_flag *flag, char **line)
{
	char			**splits;

	*line = get_next_line(fd);
	while (*line && check_flag(flag) == 0)
	{
		flag->map_start_line++;
		(*line)[ft_strlen(*line) - 1] = '\0';
			splits = ft_split(*line, ' ');
		if (*line[0] != '\0' && splits[1] != NULL && splits[2] == NULL)
		{
			printf("%s\n", *line);
			if (check_dir_valid(splits, info, *line, flag) \
			&& check_c_f_valid(splits, info, *line, flag))
				validation_error \
				("Error: unexpected file value", splits, *line, fd);
		}
		if (splits[0] != NULL && splits[1] == NULL)
			validation_error \
			("Error: Error: unexpecte line\n", splits, *line, fd);
		free_dbptr(splits);
		free (*line);
		*line = get_next_line(fd);
	}
	if (*line == NULL)
		validation_error("Error: no map info\n", NULL, NULL, fd);
}

void	is_map_closed(t_info *info)
{
	t_queue	*q;
	int		idx;
	int		dx[8];
	int		dy[8];

	init_dx_dy(dx, dy);
	idx = -1;
	locate_user(info->map, info);
	check_edge(info, dx, dy);
	q = NULL;
	push(&q, (int)(info->user->pos_x), (int)(info->user->pos_y));
	ft_bfs(q, info, dx, dy);
}
