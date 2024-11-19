/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 09:13:22 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/18 10:49:43 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	cheak_n(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '-' && cmd[i + 1] == 'n')
	{
		i++;
		while (cmd[i] == 'n' && cmd[i])
			i++;
		if (!cmd[i])
			return (1);
	}
	return (0);
}

void	no_newline(char **cmd, int fd)
{
	int	i;

	i = 0;
	while (cmd[i] && cheak_n(cmd[i]))
		i++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		i++;
		if (cmd[i])
			ft_putchar_fd(' ', fd);
	}
}

void	cmd_echo(char **cmd, int fd)
{
	int	i;

	i = 0;
	if (!cmd[i])
		ft_putchar_fd('\n', fd);
	if (cmd[i] && !cheak_n(cmd[i]))
	{
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], fd);
			i++;
			if (cmd[i])
				ft_putchar_fd(' ', fd);
		}
		ft_putchar_fd('\n', fd);
	}
	else
		no_newline(cmd, fd);
	g_data.glob_exit = 0;
}
