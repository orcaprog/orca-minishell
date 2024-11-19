/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:12:50 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/18 10:41:44 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*get_env(t_env *env, char *s, char *s2, int cheack)
{
	t_env	*ptr;
	char	*hold;

	ptr = env;
	while (ptr)
	{
		if (!ft_strcmp(ptr->key, s))
		{
			if (s2)
			{
				hold = ptr->value;
				ptr->value = s2;
				if (cheack)
					free(hold);
				break ;
			}
			return (ptr->value);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

void	go_to_home(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strcmp(ptr->key, "HOME"))
			break ;
		ptr = ptr->next;
	}
	if (!ptr)
		p_error("cd: HOME not set\n");
	else
	{
		get_env(ptr, "OLDPWD", cmd_pwd(1, 0), 1);
		if (chdir(ptr->value))
		{
			g_data.glob_exit = 1;
			perror(ptr->value);
		}
		get_env(ptr, "PWD", cmd_pwd(1, 0), 1);
	}
}

void	back_old(t_env **env, int fd)
{
	char	*temp;

	if (!get_env(*env, "OLDPWD", NULL, 0))
		return (p_error("cd: OLDPWD not set\n"));
	else
	{
		temp = get_env(*env, "PWD", NULL, 0);
		if (!get_env(*env, "OLDPWD", NULL, 0))
			return (p_error("OLDPWD not set\n"));
		if (chdir(get_env(*env, "OLDPWD", NULL, 0)) == -1)
		{
			g_data.glob_exit = 1;
			return (perror(get_env(*env, "OLDPWD", NULL, 0)));
		}
		ft_putendl_fd(get_env(*env, "OLDPWD", NULL, 0), fd);
		get_env(*env, "PWD", get_env(*env, "OLDPWD", NULL, 0), 0);
		get_env(*env, "OLDPWD", temp, 0);
		return ;
	}
}

void	change_dir(t_env **env, char *join, char *go, int k)
{
	if (!cheak_key(*env, "OLDPWD", 0))
		ft_lstadd_back_mini(env, ft_lstnew_mini("OLDPWD"));
	get_env(*env, "OLDPWD", cmd_pwd(1, 0), 1);
	if (chdir(join) != 0)
	{
		g_data.glob_exit = 1;
		perror(go);
	}
	if (k)
		free(join);
	get_env(*env, "PWD", cmd_pwd(1, 0), 1);
}

void	cmd_cd(char **path, t_env **env, int fd)
{
	char	*join;
	int		k;

	k = 1;
	if (!path[0])
		return (go_to_home(*env));
	if (path[0][0] == '-' && path[0][1] == '\0')
	{
		back_old(env, fd);
		if (!cheak_key(*env, "PWD", 0))
			if_unset_pwd(env);
		return ;
	}
	if (path[0][0] != '/')
	{
		join = ft_strjoin2(cmd_pwd(1, 0), "/");
		join = ft_strjoin2(join, path[0]);
	}
	else
	{
		join = path[0];
		k = 0;
	}
	change_dir(env, join, path[0], k);
}
