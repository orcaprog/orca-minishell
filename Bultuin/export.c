/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:38:13 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/18 11:34:17 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	export_join(t_env *ptr, char	**va, char *str)
{
	char	*hold;

	if (!ft_strcmp(ptr->key, va[0]))
	{
		if (ch_join(str))
		{
			ptr->value = ft_strjoin2(ptr->value, va[1]);
			free(va[1]);
		}
		else if (va[1])
		{
			hold = ptr->value;
			ptr->value = va[1];
			free(hold);
		}
		ptr->content = str;
		free(va[0]);
		free(va);
		return (1);
	}
	return (0);
}

int	cheak_add(t_env **env, char *str)
{
	t_env	*ptr;
	char	**va;

	va = var_val(str);
	ptr = *env;
	while (ptr)
	{
		if (export_join(ptr, va, str))
			return (0);
		ptr = ptr->next;
	}
	if (!ptr)
		free_all(va, NULL);
	return (1);
}

int	check_key(char *env)
{
	int	i;

	i = 0;
	if ((env[i] >= 'a' && env[i] <= 'z') || (env[i] >= 'A' && env[i] <= 'Z')
		|| env[i] == '_')
	{
		while (env[i] != '+' && env[i] != '=' && env[i])
		{
			if ((env[i] >= 'a' && env[i] <= 'z') || (env[i] >= 'A'
					&& env[i] <= 'Z') || (env[i] >= '0' && env[i] <= '9')
				|| env[i] == '_')
			{
				i++;
				if (env[i] == '+' && env[i + 1] != '=')
					return (1);
			}
			else
				return (1);
		}
		return (0);
	}
	return (1);
}

void	print_export(t_env *env, int fd)
{
	t_val	val;
	t_env	*ptr1;
	t_env	*ptr2;
	t_env	*ptr3;

	ptr1 = env;
	ptr2 = env;
	ptr3 = env;
	val.fd = fd;
	while (ptr1)
	{
		print_order(env, &val, ptr2, ptr3);
		ptr1 = ptr1->next;
	}
	ptr1 = env;
	while (ptr1)
	{
		ptr1->cheak = 1;
		ptr1 = ptr1->next;
	}
}

void	cmd_export(t_env **env, char **arg, int fd)
{
	int	i;
	int	k;
	int	err;

	err = 0;
	k = 1;
	i = 0;
	if (!arg[i])
		print_export(*env, fd);
	while (arg[i])
	{
		if (check_key(arg[i]))
		{
			p_error("export: '");
			p_error(arg[i]);
			p_error("': not a valid identifier\n");
			err = 1;
			k = 0;
		}
		if (cheak_add(env, arg[i]) && k)
			ft_lstadd_back_mini(env, ft_lstnew_mini(arg[i]));
		k = 1;
		i++;
	}
	g_data.glob_exit = err;
}
