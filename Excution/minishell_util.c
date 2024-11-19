/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:02:55 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/18 09:08:15 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	cheackis_buil(char *cmd)
{
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	return (0);
}

int	exucute_builtine(t_global *all, t_cmd *cmds)
{
	if (!ft_strcmp(cmds->cmd, "env"))
		cmd_env(all->env_list, cmds->out_fd);
	if (!ft_strcmp(cmds->cmd, "unset"))
		cmd_unset(cmds->args, &all->env_list);
	if (!ft_strcmp(cmds->cmd, "export"))
		cmd_export(&all->env_list, cmds->args, cmds->out_fd);
	if (!ft_strcmp(cmds->cmd, "cd"))
		cmd_cd(cmds->args, &all->env_list, cmds->out_fd);
	if (!ft_strcmp(cmds->cmd, "pwd"))
		cmd_pwd(cmds->out_fd, 1);
	if (!ft_strcmp(cmds->cmd, "exit"))
		cmd_exit(cmds->args);
	if (!ft_strcmp(cmds->cmd, "echo"))
		cmd_echo(cmds->args, cmds->out_fd);
	return (g_data.glob_exit);
}
