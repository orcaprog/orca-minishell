/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_excution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooussaad <ooussaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:52:34 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/18 00:04:02 by ooussaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	**join_op(char *cmd, char **op)
{
	int		i;
	int		j;
	char	**cmdop;

	j = 1;
	i = 0;
	while (op[i])
		i++;
	cmdop = malloc(sizeof(char *) * (i + 2));
	i = 0;
	cmdop[0] = ft_strdup(cmd);
	while (op[i])
	{
		cmdop[j] = ft_strdup(op[i]);
		i++;
		j++;
	}
	cmdop[j] = NULL;
	return (cmdop);
}

int	first_child(t_global *all, t_cmd *cmds, char **env, int *fd)
{
	char	*path;
	char	**cmdop;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		ft_dup_io1(cmds, fd);
		if (cheackis_buil(cmds->cmd))
			exit(exucute_builtine(all, cmds));
		cmdop = join_op(cmds->cmd, cmds->args);
		path = my_path(cmds->cmd, env);
		if (!path)
			check_error2(cmds->cmd);
		if (execve(path, cmdop, env) == -1)
		{
			check_error2(cmds->cmd);
			exit(1);
		}
	}
	return (pid);
}

void	call_childs(t_global *all, t_cmd *cmds, char **env, t_val *val)
{
	char	*path;
	char	**cmdop;

	ft_dup_io2(cmds, val->fd_p, val->last_fd);
	if (cheackis_buil(cmds->cmd))
		exit(exucute_builtine(all, cmds));
	if (cmds->errr)
	{
		errno = 2;
		perror(cmds->cmd);
		exit(127);
	}
	cmdop = join_op(cmds->cmd, cmds->args);
	path = my_path(cmdop[0], env);
	if (!path)
		check_error2(cmds->cmd);
	if (execve(path, cmdop, env) == -1)
	{
		check_error2(cmds->cmd);
		exit(1);
	}
}

int	multp_cmd(t_global *all, t_cmd *cmds, char **env, t_val *val)
{
	int	pid;

	while (cmds)
	{
		pipe(val->fd_p);
		pid = fork();
		if (pid == 0)
		{
			if (!cmds->cheak)
				exit(1);
			if (!cmds->cmd)
				exit(0);
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			call_childs(all, cmds, env, val);
		}
		close(val->last_fd);
		val->last_fd = val->fd_p[0];
		close(val->fd_p[1]);
		cmds = cmds->next;
	}
	return (pid);
}

void	cmd_excution(t_global *all, char **env)
{
	int		pid;
	t_val	val;
	t_cmd	*cmds;

	val.last_fd = 0;
	pipe(val.fd_p);
	val.last_fd = val.fd_p[0];
	pid = first_child(all, all->all_cmd, env, val.fd_p);
	cmds = all->all_cmd->next;
	close(val.fd_p[1]);
	if (cmds)
		pid = multp_cmd(all, cmds, env, &val);
	wait_signal(pid);
}
