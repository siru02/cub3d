/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:12:22 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/30 19:15:40 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

# define SCREEN_WIDTH		1280
# define SCREEN_HEIGHT		720
# define KEY_ESC			53
# define KEY_W				13
# define KEY_S				1
# define KEY_A				0
# define KEY_D				2
# define KEY_LEFT			123
# define KEY_RIGHT			124
# define PRESS_RED_BUTTON	17
# define WALL_X				0
# define WALL_Y				1

typedef struct s_user
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	plane_len;
}t_user;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perp_wall_dist;
	double	x;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		side;
}t_ray;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}t_data;

typedef struct s_camera
{
	double	x;
	double	y;
}t_camera;

typedef struct s_info
{
	char		**map;
	char		**copy_map;
	int			max_col;
	t_data		img;
	t_data		west;
	t_data		east;
	t_data		south;
	t_data		north;
	void		*mlx;
	void		*mlx_win;
	int			f_color;
	int			c_color;
	t_user		*user;
	t_ray		*ray;
	t_camera	cam;
	int			width;
	int			height;
	int			row_cnt;
	int			tmp_fd;
}t_info;

typedef struct s_parse_flag
{
	int		east;
	int		west;
	int		south;
	int		north;
	int		ceiling;
	int		floor;
	int		map_start_line;
	char	user_char;
}t_parse_flag;

typedef struct s_line
{
	int		height;
	int		draw_start;
	int		draw_end;
	int		tex_x_point;
	double	y_ratio;
	double	x_ratio;
}t_line;

typedef struct s_node
{
	int				x;
	int				y;
	struct s_node	*prev;
	struct s_node	*next;
}t_node;

typedef struct s_queue
{
	t_node	*first;
	t_node	*last;
}t_queue;

//parse.c
void	make_map(int fd, t_info *info, char **line, t_parse_flag *flag);
void	parsing(char *argv, t_info *info);
void	check_tex_valid(int fd, t_info *info, t_parse_flag *flag, char **line);
void	check_map(int fd, t_info *info, char **line, t_parse_flag *flag);
void	is_map_closed(t_info *info);

//draw_pixel
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	select_tex_pixel(t_line *line, t_ray *ray, t_user *user, t_data *tex);
void	draw_vertical(t_line line, t_ray *ray, t_info *info, t_data *tex);
void	draw_line(t_line line, t_user *user, t_ray *ray, t_info *info);

//is_map_closed
void	init_dx_dy(int *dx, int *dy);
void	locate_user(char **map, t_info *info);
void	check_edge(t_info *info, int *dx, int *dy);
void	ft_bfs(t_queue *q, t_info *info, int *dx, int *dy);

//ft_bfs_utils
char	**map_copy(char **src, t_info *info, int i, int j);
int		check_zero(char **copy_map, int new_x, int new_y);
int		check_visited(char **copy_map, int new_x, int new_y, t_info *info);
void	exit_case_check(t_info *info, int new_x, int new_y);

//ft_init
void	init_info(t_info *info, t_ray *ray, t_user *user);
void	init_user(t_user *user_ptr, t_info *info);
void	init_flag(t_parse_flag *flag);
void	check_xpm_files(t_info *info);

//ft_queue_1
t_queue	*init_queue(void);
t_node	*make_new_node(int x, int y);
void	push(t_queue **queue, int x, int y);
void	pop(t_queue **queue);
void	print_queue(t_queue *queue);

//ft_queue_2
int		is_empty(t_queue *q);
int		is_in_queue(t_queue *q, int new_x, int new_y);

//hook_utils
void	rotate_right(t_info *info, double angle);
void	rotate_left(t_info *info, double angle);
int		check_wall(t_info *info, double mov_x, double mov_y);
int		win_close(t_info *info);

//hook
int		key_handler(int key_code, t_info *info);
void	move_up_down(t_info *info, int key_code);
void	move_side(t_info *info, int key_code, double mov_x, double mov_y);
void	camera_rotate(t_info *info, int key_code);
int		mouse_handler(int x, int y, t_info *info);

//check_map_utils
int		check_map_line_valid(char *line, t_parse_flag *flag);

//parse_utils
int		check_name(char *argv);
void	fill_space(char *map, int max);
void	free_dbptr(char **splits);
void	validation_error(char *error_msg, char **splits, char *line, int fd);
int		check_flag(t_parse_flag *flag);

//ratcasting
int		raycasting(t_info *info, t_user *user, t_ray *ray);
void	init_dist(t_user *user, t_ray *ray);
void	perform_dda(t_info *info, t_ray *ray, int hit);
t_line	init_line_height(t_ray *ray);
void	set_tex_info(t_data *tex, t_data *dir);

//main
void	ft_exit(char *str);

//check_edge_utils_1
void	check_left_line(t_info *info, int *dx, int *dy, int idx);
void	check_right_line(t_info *info, int *dx, int *dy, int idx);
void	check_first_line(t_info *info, int *dx, int *dy);
void	check_last_line(t_info *info, int *dx, int *dy);
void	space_bfs(t_queue **q, t_info *info, int *dx, int *dy);

//check_edge_utils_2
void	space_bfs_exit(char **dbptr_1, char **dbptr_2, char *err_msg);

//check_tex_valid_utils
int		create_trgb(int red, int green, int blue);
void	check_comma(char *str);
int		check_dir_valid(char **splits, t_info *info, char *line, \
		t_parse_flag *flag);
int		check_c_f_valid(char **splits, t_info *info, char *line, \
		t_parse_flag *flag);

//check_c_f_valid_utils
int		check_ceiling_color_info(char **splits, t_info *info, \
		t_parse_flag *flag);
int		check_floor_color_info(char **splits, t_info *info, t_parse_flag *flag);

#endif 