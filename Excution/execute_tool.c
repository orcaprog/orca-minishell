/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooussaad <ooussaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:40:08 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/19 18:26:30 by ooussaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	siiig(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	ft_dup_io1(t_cmd *cmds, int *fd)
{
	if (cmds->errr)
	{
		errno = 2;
		perror(cmds->cmd);
		exit(127);
	}
	if (!cmds->cheak)
		exit(1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmds->cmd)
		exit(0);
	if (cmds->out_fd == 1 && cmds->next)
		check_error("ERR_DUP ", dup2(fd[1], 1));
	else
		check_error("ERR_DUP ", dup2(cmds->out_fd, 1));
	close(fd[1]);
	close(fd[0]);
	check_error("ERR_DUP ", dup2(cmds->in_fd, STDIN_FILENO));
}

void	ft_dup_io2(t_cmd *cmds, int *fd, int last_fd)
{
	if (cmds->in_fd == 0)
		check_error("ERR_DUP ", dup2(last_fd, 0));
	else
		check_error("ERR_DUP ", dup2(cmds->in_fd, 0));
	close(last_fd);
	if (cmds->out_fd == 1 && cmds->next)
		check_error("ERR_DUP ", dup2(fd[1], 1));
	else
		check_error("ERR_DUP ", dup2(cmds->out_fd, 1));
	close(fd[1]);
	close(fd[0]);
}

void	wait_signal(int pid)
{
	int	status;

	signal(SIGINT, siiig);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_data.glob_exit = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
		{
			write(1, "Quit: 3\n", 8);
			g_data.glob_exit = 131;
		}
		if (WTERMSIG(status) == 2)
			g_data.glob_exit = 130;
	}
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	while (wait(NULL) != -1)
		;
}
