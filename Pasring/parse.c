/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:33:24 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/02 00:46:11 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	new_t_cmd_pipe(t_elm **ptr, t_cmd_pipe **full_cmd,
	t_cmd_pipe **cmds, int *i)
{
	int	size;

	size = 0;
	(*full_cmd)->args[*i] = NULL;
	(*full_cmd)->next = cmd_new();
	(*full_cmd) = (*full_cmd)->next;
	*i = 0;
	*ptr = (*ptr)->next;
	size = count_args(*ptr);
	(*full_cmd)->args = malloc(sizeof(char *) * (size + 1));
	(*full_cmd)->reder = red_list(*ptr);
	if ((*full_cmd)->next)
	{
		(*full_cmd) = (*full_cmd)->next;
		(*full_cmd)->args = malloc(sizeof(char *) * (size + 1));
		(*full_cmd)->reder = red_list(*ptr);
		ft_lstadd_back1(cmds, (*full_cmd));
	}
}

void	parce_cmds(t_elm *ptr, t_cmd_pipe *full_cmd, t_cmd_pipe **cmds, int i)
{
	while (ptr)
	{
		if (ptr->type == PIPE_LINE)
			new_t_cmd_pipe(&ptr, &full_cmd, cmds, &i);
		else if (ptr->type == WORD)
			parse_word(&ptr, full_cmd->args, &i);
		else if ((ptr->type == DOUBLE_QUOTE || ptr->type == QOUTE))
		{
			full_cmd->args[i] = parse_quotes(&ptr, ptr->type);
			if (full_cmd->args[i])
				(i)++;
		}
		else
			ptr = ptr->next;
	}
	full_cmd->args[i] = NULL;
}

void	parse_word(t_elm **ptr, char **args, int *i)
{
	args[*i] = ft_strndup((*ptr)->content, (*ptr)->len);
	(*i)++;
	(*ptr) = (*ptr)->next;
}

int	parse_cmd_act(t_elm *ptr, t_cmd_pipe **cmds)
{
	t_cmd_pipe	*full_cmd;
	int			size;
	int			i;

	i = 0;
	between_quot(ptr);
	parse_red(ptr);
	full_cmd = *cmds;
	size = count_args(ptr);
	full_cmd->args = malloc((sizeof(char *)) * (size + 1));
	full_cmd->reder = red_list(ptr);
	parce_cmds(ptr, full_cmd, cmds, i);
	return (EXIT_SUCCESS);
}

void	parse_cmd(t_elm **ptr, t_cmd **fcmd)
{
	int			size;
	t_cmd_pipe	*full_cmd;

	full_cmd = malloc(sizeof(t_cmd_pipe));
	full_cmd->next = NULL;
	size = count_args((*ptr));
	if (parse_cmd_act(*ptr, &full_cmd) == EXIT_FAILURE)
		return ;
	g_data.parcecmd = full_cmd;
	fille_cmd(fcmd, full_cmd);
}
