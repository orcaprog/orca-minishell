/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooussaad <ooussaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:18:48 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/20 12:04:02 by ooussaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	cheak_her_doc(t_cmd *cmds)
{
	int			her;
	t_redirect	*red;

	her = 0;
	while (cmds)
	{
		red = cmds->list_of_red;
		while (red)
		{
			if (red->my_redirect == 7)
				her++;
			red = red->next;
		}
		cmds = cmds->next;
	}
	return (her);
}

void	one_cmd(t_cmd *cmds, t_global *all, char **env, int k)
{
	if (!get_env(all->env_list, "PATH", NULL, 0) && access(cmds->cmd,
			X_OK) != 0)
		cmds->errr = 1;
	k = set_her_doc(cmds, all->env_list);
	cmds->cheak = set_red(cmds);
	if (k && cmds->cheak)
	{
		if (cheackis_buil(all->all_cmd->cmd))
			exucute_builtine(all, all->all_cmd);
		if (cmds->cmd && cheackis_buil(all->all_cmd->cmd) != 1)
			cmd_excution(all, env);
	}
}

void	more_cmds(t_cmd *cmds, t_global *all, char **env, int k)
{
	while (cmds)
	{
		if (!set_her_doc(cmds, all->env_list))
		{
			k = 0;
			break ;
		}
		cmds = cmds->next;
	}
	cmds = all->all_cmd;
	if (k)
	{
		while (cmds)
		{
			cmds->cheak = set_red(cmds);
			if (!get_env(all->env_list, "PATH", NULL, 0) && access(cmds->cmd,
					X_OK) != 0)
				cmds->errr = 1;
			cmds = cmds->next;
		}
		cmd_excution(all, env);
	}
}

void	execution_mini(t_global *all, char **env)
{
	t_cmd	*cmds;
	int		k;

	cmds = all->all_cmd;
	k = 1;
	if (cheak_her_doc(cmds) > 16)
	{
		p_error("maximum here-document count exceeded\n");
		exit(2);
	}
	while (cmds)
	{
		cmds->errr = 0;
		cmds = cmds->next;
	}
	cmds = all->all_cmd;
	if (cmds && !cmds->next)
		one_cmd(cmds, all, env, k);
	else
		more_cmds(cmds, all, env, k);
}
