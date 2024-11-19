/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:10:07 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/22 12:01:44 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	set_red(t_cmd *cmd)
{
	t_redirect	*red;

	cmd->in_fd = 0;
	cmd->out_fd = 1;
	red = cmd->list_of_red;
	while (red)
	{
		if (red->my_redirect == 9)
			cmd->out_fd = open(red->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (red->my_redirect == 10)
			cmd->out_fd = open(red->filename, O_CREAT | O_RDWR
					| O_APPEND, 0644);
		if (red->my_redirect == 8)
			cmd->in_fd = open(red->filename, O_RDONLY);
		if (red->my_redirect == 7)
			cmd->in_fd = cmd->here_doc;
		if (cmd->out_fd == -1 || cmd->in_fd == -1)
		{
			perror(red->filename);
			g_data.glob_exit = 1;
			return (0);
		}
		red = red->next;
	}
	return (1);
}

int	set_her_doc(t_cmd *cmds, t_env *env)
{
	t_redirect	*red;

	red = cmds->list_of_red;
	while (red)
	{
		if (red->my_redirect == 7)
		{
			cmds->here_doc = her_doc(red, env);
			if (cmds->here_doc == 1)
			{
				return (0);
			}
		}
		red = red->next;
	}
	return (1);
}

void	free_lexer(t_elm *ptr)
{
	t_elm	*hold;

	while (ptr)
	{
		free(ptr->content);
		hold = ptr->next;
		free(ptr);
		ptr = hold;
	}
}

int	her_sig(int pid)
{
	int	status;

	signal(SIGINT, siiig);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_data.glob_exit = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		g_data.glob_exit = 1;
		return (1);
	}
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	her_doc(t_redirect *red, t_env *env)
{
	int	fd_pipe[2];
	int	pid;

	if (pipe(fd_pipe) == -1)
		perror("");
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		get_herdoc(red, env, fd_pipe);
		close(fd_pipe[1]);
		g_data.glob_exit = 1;
		exit(0);
	}
	if (her_sig(pid))
		return (1);
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}
