/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_1_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:35:15 by hgu               #+#    #+#             */
/*   Updated: 2024/01/30 19:14:07 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_queue	*init_queue(void)
{
	t_queue	*queue;

	queue = malloc(sizeof(t_queue));
	if (!queue)
	{
		printf("Error: Q malloc failed\n");
		exit(1);
	}
	queue->first = NULL;
	queue->last = NULL;
	return (queue);
}

t_node	*make_new_node(int x, int y)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
	{
		printf("Error: Node malloc failed\n");
		exit(1);
	}
	new_node->x = x;
	new_node->y = y;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	push(t_queue **queue, int x, int y)
{
	t_node	*node_to_push;

	if (*queue == NULL)
		*queue = init_queue();
	node_to_push = make_new_node(x, y);
	if ((*queue)->first == NULL)
	{
		(*queue)->first = node_to_push;
		(*queue)->last = node_to_push;
	}
	else
	{
		(*queue)->last->next = node_to_push;
		node_to_push->prev = (*queue)->last;
		(*queue)->last = node_to_push;
	}
}

void	pop(t_queue **queue)
{
	t_node	*node;

	if (*queue == NULL || (*queue)->first == NULL)
		return ;
	node = (*queue)->first;
	if ((*queue)->first == (*queue)->last)
	{
		(*queue)->first = NULL;
		(*queue)->last = NULL;
		free(*queue);
		*queue = NULL;
	}
	else
	{
		(*queue)->first = (*queue)->first->next;
		(*queue)->first->prev = NULL;
	}
	free(node);
	return ;
}

void	print_queue(t_queue *queue)
{
	t_node	*node;
	int		cnt;

	printf("print_queue started\n");
	cnt = 0;
	if (queue == NULL)
	{
		printf("que is NULL\n");
		printf("print_queue end\n");
		return ;
	}
	node = queue->first;
	while (node != NULL)
	{
		printf("idx: %d: x == %d, y == %d\n", cnt, node->x, node->y);
		node = node->next;
		cnt++;
	}
	printf("print_queue end\n");
}
