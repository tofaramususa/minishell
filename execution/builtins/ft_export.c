/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:48:17 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/15 18:05:16 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ft_env_print_linked: is a function that simply prints the env
 * @proc: is a structure that contains all variables plus 
 * the head to the linked list
*/
void	ft_env_print_linked(t_shell *proc, t_command *av)
{
	t_list	*tmp;

	tmp = *proc->env_list;
	while (tmp)
	{
		if (ft_strchr(tmp->key, '='))
			printf("%s%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	garbage_collector(proc);
	exit(0);
}

int	ft_export_to_linked(t_command *pipe, t_shell *prc)
{
	while (pipe->args[++prc->x])
	{
		if (ft_validate_exprot(pipe->args[prc->x]) == 1)
			print_and_set_flag(pipe, prc);
		else
			chek_exp_a_rplc(*prc->head, pipe->args[prc->x]);
	}
	return (prc->flag);
}
/**
 * ft_export_print_linked: is a function that does export like bash
 * it basically take the linked list and print it in sorted order
 * @sort_list: is a function that sort linked list
 * @proc: is a structure that contains all variables plus the 
 * head to the linked list
*/

int	ft_export_print_linked(t_command *pipe, t_shell *prc)
{
	sort_list(*prc->head);
	re_index(*prc->head);
	prc->flag = 0;
	prc->temp_list = *prc->head;
	prc->x = 0;
	if (pipe->args[1])
		prc->x = ft_export_to_linked(pipe, prc);
	else
	{
		prc->temp_list = *prc->head;
		while (prc->temp_list)
		{
			if (ft_strchr(prc->temp_list->key, '='))
				printf("declare -x %s\"%s\"\n", \
				prc->temp_list->key, prc->temp_list->value);
			else
				printf("declare -x %s\n", prc->temp_list->key);
			prc->temp_list = prc->temp_list->next;
		}
	}
	if (pipe->cmd_len > 1)
		garbage_collector(prc);
	return (prc->x);
}

/**
 * ft_unset_check_and_unset: check if the identifier 
 * is valid and remove it from the linked list
 * @main_head: the head of the linked lsit
 * @args: array of var names to be removed
*/
int	ft_unset_check_and_unset(t_list **main_head, char **args)
{
	t_exp_var	var;

	var.x = -1;
	var.tmp_ex = NULL;
	while (args[++var.x])
	{
		if (ft_strchr(args[var.x], '='))
			return (write(2, args[var.x], ft_strlen(args[var.x])), \
			ft_putstr_fd(" : not a valid identifier\n", 2), 1);
		var.tmp_list = *main_head;
		while (var.tmp_list)
		{
			if (ft_strchr(var.tmp_list->key, '='))
				var.tmp_ex = ft_strjoin(args[var.x], "=");
			else
				var.tmp_ex = ft_strdup(args[var.x]);
			if (ft_strcmp(var.tmp_list->key, var.tmp_ex) == 0)
				return (safefree(var.tmp_ex), \
				remove_element(main_head, var.tmp_list->index));
			safefree(var.tmp_ex);
			var.tmp_list = var.tmp_list->next;
		}
	}
	return (0);
}

/**
 * ft_unset: validate and remove an element from list 
 * @pipe: all the cmd , arg and redirections
 * @proc: the struct containing variables to use
*/
int	ft_unset(t_command *pipe, t_shell *proc)
{
	int	x;
	int	res;

	x = 0;
	res = 0;
	if (pipe->args[1])
		while (pipe->args[++x])
			res = ft_unset_check_and_unset(proc->env_list, &pipe->args[x]);
	if (pipe->cmd_len > 1)
		garbage_collector(prc);
	return (res);
}
