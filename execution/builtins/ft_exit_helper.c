/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_modified.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:42:07 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/13 22:35:14 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	atoi_utl_with_exit(char *str, int x, t_shell *proc)
{
	unsigned long long		res;
	unsigned long long		copy;

	copy = 0;
	res = 0;

	while (str[x] >= '0' && str[x] <= '9')
	{
		copy = res;
		res = (res * 10) + (str[x++] - '0');
		if (copy > res)
		{
			ft_putstr_fd(": numeric argument required\n", 2);
			garbage_collector(proc)
			exit(255);
		}
	}
}

int	ft_exit_helper(const char *str, t_pipe *pipe, t_shell *proc)
{
	int						x;
	int						sign;
	unsigned long long		res;
	unsigned long long		copy;

	x = 0;
	res = 0;
	sign = 1;
	copy = 0;
		x++;
	while(array_strchr("\t \v\f\r\n", str[x]))
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
