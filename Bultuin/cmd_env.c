/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooussaad <ooussaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:51:18 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/18 00:11:18 by ooussaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	print_ex(t_env *ptr3, int fd)
{
	if (ptr3->value)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(ptr3->key, fd);
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(ptr3->value, fd);
		ft_putendl_fd("\"", fd);
	}
	else
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putendl_fd(ptr3->key, fd);
	}
}

void	print_order(t_env *env, t_val *val, t_env *ptr2, t_env *ptr3)
{
	ptr2 = env;
	while (ptr2->cheak != 1)
		ptr2 = ptr2->next;
	val->small = ptr2->key;
	ptr2 = env;
	while (ptr2)
	{
		if (ft_strcmp(val->small, ptr2->key) != -1 && ptr2->cheak)
		{
			val->small = ptr2->key;
			ptr3 = ptr2;
		}
		ptr2 = ptr2->next;
	}
	print_ex(ptr3, val->fd);
	ptr3->cheak = 0;
}

void	cmd_env(t_env *env, int fd)
{
	t_env	*ptr;

	ptr = env;
	if (!get_env(env, "PATH", NULL, 0))
	{
		p_error("env: No such file or directory\n");
		g_data.glob_exit = 127;
		return ;
	}
	while (ptr)
	{
		if (ptr->value)
		{
			ft_putstr_fd(ptr->key, fd);
			ft_putstr_fd("=", fd);
			ft_putendl_fd(ptr->value, fd);
		}
		ptr = ptr->next;
	}
	g_data.glob_exit = 0;
}
