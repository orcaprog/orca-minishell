/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:11:27 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/18 10:42:13 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	if_unset_pwd(t_env **env)
{
	ft_lstadd_back_mini(env, ft_lstnew_mini("PWD"));
	cheak_key(*env, "OLDPWD", 1);
}

char	*cheak_key(t_env *env, char *key, int k)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strcmp(key, ptr->key))
		{
			if (k)
				ptr->value = NULL;
			return (ptr->key);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

char	*cmd_pwd(int fd, int k)
{
	char	*cwd;
	int		i;

	cwd = malloc(10000);
	i = 0;
	if (!getcwd(cwd, 10000))
		perror("");
	if (k)
	{
		ft_putendl_fd(cwd, fd);
		free(cwd);
		g_data.glob_exit = 0;
	}
	else
		return (cwd);
	return (NULL);
}
