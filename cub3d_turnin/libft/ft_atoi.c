/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:28:46 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/30 13:00:04 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	integer;
	int		sign;

	integer = 0;
	sign = 1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == 43 || *str == 45)
		sign = 44 - *(str++);
	while (ft_isdigit(*str))
	{
		if (sign == 1 && ((integer > LONG_MAX / 10)
				|| ((integer == LONG_MAX / 10 && *str - '0' > LONG_MAX % 10))))
			return (-1);
		else if (sign == -1 && ((integer > -1 * (LONG_MIN / 10)
					|| (integer == -1 * (LONG_MIN / 10)
						&& *str - '0' > -1 * (LONG_MIN % 10)))))
			return (0);
		else
			integer = 10 * integer + (*str - '0');
		str++;
	}
	return (sign * (int)integer);
}
