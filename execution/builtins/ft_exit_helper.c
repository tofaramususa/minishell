/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:42:07 by yonamog2          #+#    #+#             */
/*   Updated: 2023/08/30 14:14:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void atoi_utl_with_exit(char *str, int x, t_shell *proc)
{
	unsigned long long res;

	res = 0;
	proc->copy = 0;
	while (str[x] >= '0' && str[x] <= '9')
	{
		proc->copy = res;
		// copy += 0; // Perform a no-op operation with copy
		res = (res * 10) + (str[x++] - '0');
		if (proc->copy > res)
		{
			ft_putstr_fd(": numeric argument required\n", 2);
			garbage_collector(&proc);
			exit(255);
		}
	}
}

int	ft_exit_helper(const char *str, t_shell *proc)
{
	int					x;
	int					sign;
	unsigned long long	res;

	x = 0;
	res = 0;
	sign = 1;
	x++;
	while (array_strchr("\t \v\f\r\n", str[x]))
		x++;
	if (str[x] == '-' || str[x] == '+')
	{
		if (str[x] == '-')
			sign = -1;
		x++;
	}
	atoi_utl_with_exit((char *)str, x, proc);
	return (res * sign);
}
