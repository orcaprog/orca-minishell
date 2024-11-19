/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooussaad <ooussaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:54:12 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/18 00:18:05 by ooussaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	check_key2(char *env)
{
	int	i;

	i = 0;
	if ((env[i] >= 'a' && env[i] <= 'z') || (env[i] >= 'A' && env[i] <= 'Z')
		|| env[i] == '_')
	{
		while (env[i])
		{
			if ((env[i] >= 'a' && env[i] <= 'z') || (env[i] >= 'A'
					&& env[i] <= 'Z') || (env[i] >= '0' && env[i] <= '9')
				|| env[i] == '_')
			{
				i++;
			}
			else
				return (1);
		}
		return (0);
	}
	return (1);
}

int	cmd_unset(char **arg, t_env **env)
{
	int	i;
	int	err;

	err = 0;
	i = 0;
	while (arg[i])
	{
		if (check_key2(arg[i]))
		{
			p_error("unset: '");
			p_error(arg[i]);
			p_error("': not a valid identifier\n");
			err = 1;
		}
		else
			del_node(env, arg[i]);
		i++;
	}
	g_data.glob_exit = err;
	return (g_data.glob_exit);
}
