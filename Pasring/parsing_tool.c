/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 00:30:41 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/17 19:57:50 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	count_args(t_elm *elem)
{
	t_elm	*tmp;
	int		i;

	i = 0;
	tmp = elem;
	while (tmp && tmp->type != PIPE_LINE)
	{
		if (tmp->type == WORD || tmp->type == ENV)
			i++;
		if (tmp)
			tmp = tmp->next;
	}
	return (i);
}

int	is_redir(enum e_token type)
{
	return (type == IN_RED || type == OUT_RED || type == MORE_RED
		|| type == LESS_RED);
}

t_elm	*skip_spaces(t_elm *ptr)
{
	while (ptr && ptr->type == WHITE_SPACE)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

int	pipe_error(t_elm *ptr)
{
	t_elm	*next;

	next = skip_spaces(ptr->next);
	if (ptr->type == PIPE_LINE && !ptr->prev)
	{
		return (EXIT_FAILURE);
	}
	if (!next || (next->type != WORD && next->type != DOUBLE_QUOTE
			&& next->type != QOUTE && next->type != ENV
			&& !is_redir(next->type)))
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	redir_error(t_elm *ptr)
{
	t_elm	*next;

	next = ptr;
	if (next->type == MORE_RED || next->type == LESS_RED)
	{
		next = next->next;
	}
	next = skip_spaces(ptr->next);
	if (!next || (next->type != WORD && !is_redir(next->type)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
