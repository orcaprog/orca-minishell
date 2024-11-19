/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooussaad <ooussaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:26:42 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/18 00:05:12 by ooussaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	ft_puterr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

void	check_error2(char *str)
{
	int	i;

	i = 0;
	ft_puterr(str);
	ft_puterr(" : command not found\n");
	exit(127);
}

void	free_all(char **str, char *str2)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	if (str2 != NULL)
	{
		free(str2);
	}
}

char	*my_path(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	*cmpath;
	char	**mypath;
	char	*join;

	i = 0;
	if (!access(cmd, X_OK))
		return (cmd);
	while (!ft_strnstr(env[i], "PATH=", 5) && env != NULL)
		i++;
	path = env[i];
	mypath = ft_split(path + 5, ':');
	cmpath = ft_strjoin("/", cmd);
	i = 0;
	while (mypath[i])
	{
		join = ft_strjoin(mypath[i], cmpath);
		if (!access(join, F_OK))
			return (free_all(mypath, cmpath), join);
		free(join);
		i++;
	}
	return (free_all(mypath, cmpath), NULL);
}
