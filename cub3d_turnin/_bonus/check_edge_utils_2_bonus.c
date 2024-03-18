/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_edge_utils_2_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:56:01 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/30 19:12:53 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	space_bfs_exit(char **dbptr_1, char **dbptr_2, char *err_msg)
{
	free_dbptr(dbptr_1);
	free_dbptr(dbptr_2);
	ft_exit(err_msg);
}
