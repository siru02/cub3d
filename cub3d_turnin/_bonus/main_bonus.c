/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:10:39 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/30 19:14:20 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_exit(char *str)
{
	printf("%s", str);
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_user	user;
	t_info	info;
	t_ray	ray;

	if (argc != 2)
	{
		printf("Error : argc error!!\n");
		return (1);
	}
	init_info(&info, &ray, &user);
	parsing(argv[1], &info);
	init_user(&user, &info);
	check_xpm_files(&info);
	mlx_hook(info.mlx_win, 17, 0, &win_close, &info);
	mlx_hook(info.mlx_win, 2, 0, &key_handler, &info);
	mlx_hook(info.mlx_win, 6, 0, &mouse_handler, &info);
	if (raycasting(&info, &user, &ray) == 1)
		return (1);
	mlx_put_image_to_window(info.mlx, info.mlx_win, info.img.img, 0, 0);
	mlx_loop(info.mlx);
}
