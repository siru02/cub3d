# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 16:31:55 by donglee2          #+#    #+#              #
#    Updated: 2024/01/30 19:24:03 by donglee2         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
BONUS_NAME = cub3d_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./libft -lft
MLXFLAG = -lmlx -framework OpenGL -framework AppKit -g3 -fsanitize=address

MANDATORY_DIR = ./_mandatory

MANDATORY_SRCS = $(MANDATORY_DIR)/main.c\
$(MANDATORY_DIR)/hook.c\
$(MANDATORY_DIR)/parse.c\
$(MANDATORY_DIR)/check_map_utils.c\
$(MANDATORY_DIR)//parse_utils.c\
$(MANDATORY_DIR)/raycasting.c\
$(MANDATORY_DIR)/is_map_closed.c\
$(MANDATORY_DIR)/draw_pixel.c\
$(MANDATORY_DIR)/ft_init.c\
$(MANDATORY_DIR)/ft_queue_1.c\
$(MANDATORY_DIR)/ft_queue_2.c\
$(MANDATORY_DIR)/hook_utils.c\
$(MANDATORY_DIR)/check_edge_utils_1.c\
$(MANDATORY_DIR)/check_tex_valid_utils.c\
$(MANDATORY_DIR)/check_edge_utils_2.c\
$(MANDATORY_DIR)/ft_bfs_utils.c\
$(MANDATORY_DIR)/check_c_f_valid_utils.c

BONUS_DIR = ./_bonus

BONUS_SRCS = $(BONUS_DIR)/main_bonus.c\
$(BONUS_DIR)/hook_bonus.c\
$(BONUS_DIR)/parse_bonus.c\
$(BONUS_DIR)/check_map_utils_bonus.c\
$(BONUS_DIR)/parse_utils_bonus.c\
$(BONUS_DIR)/raycasting_bonus.c\
$(BONUS_DIR)/is_map_closed_bonus.c\
$(BONUS_DIR)/draw_pixel_bonus.c\
$(BONUS_DIR)/ft_init_bonus.c\
$(BONUS_DIR)/ft_queue_1_bonus.c\
$(BONUS_DIR)/ft_queue_2_bonus.c\
$(BONUS_DIR)/hook_utils_bonus.c\
$(BONUS_DIR)/check_edge_utils_1_bonus.c\
$(BONUS_DIR)/check_tex_valid_utils_bonus.c\
$(BONUS_DIR)/check_edge_utils_2_bonus.c\
$(BONUS_DIR)/ft_bfs_utils_bonus.c\
$(BONUS_DIR)/check_c_f_valid_utils_bonus.c

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

RM = rm -rf

MAKE = make

LIBFT = libft/libft.a

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< -g3

$(LIBFT):
	$(MAKE) -C ./libft bonus



$(NAME): $(MANDATORY_OBJS) $(LIBFT) 
	$(CC) $(CFLAGS) -o $(NAME) $(MANDATORY_OBJS) $(LDFLAGS) $(MLXFLAG)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LDFLAGS) $(MLXFLAG)
	touch $@

clean:	
	$(RM) $(MANDATORY_OBJS) $(BONUS_OBJS) bonus
	$(MAKE) -C ./libft clean

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	$(RM) $(LIBFT)
	
re: fclean all
