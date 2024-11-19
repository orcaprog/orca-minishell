/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 08:48:57 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/20 23:51:57 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	redir_error_2(t_elm *ptr)
{
	t_elm	*next;

	printf("%s", ptr->content);
	next = skip_spaces(ptr->next);
	if (!next || (next->type != WORD && !is_redir(next->type)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_redir(t_elm *elem)
{
	if (elem->type == LESS_RED || elem->type == MORE_RED)
	{
		elem = elem->next->next;
		if (!elem)
			return (1);
	}
	else
		elem = elem->next;
	if (elem)
	{
		while (elem && elem->type == WHITE_SPACE)
			elem = elem->next;
		if (!elem)
			return (1);
		if (is_redir(elem->type) || elem->type == PIPE_LINE)
			return (1);
	}
	else
		return (1);
	return (0);
}

void	parse1(t_elm *ptr, t_global *all)
{
	all->all_cmd = NULL;
	parse_cmd(&ptr, &all->all_cmd);
}

int	syntax_errors(t_list *list)
{
	t_elm	*ptr;

	ptr = list->head;
	while (ptr)
	{
		if (is_redir(ptr->type))
		{
			if (check_redir(ptr))
				return (write(2, "minishell: syntax error\n", 25));
		}
		if (ptr->type == PIPE_LINE)
		{
			if (pipe_error(ptr))
				return (write(2, "minishell: syntax error\n", 25));
		}
		if (ptr->type == DOUBLE_QUOTE || ptr->type == QOUTE)
		{
			if (!check_unclosed_quotes(&ptr, ptr->type))
				return (EXIT_FAILURE);
		}
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}

int	lunch_shell(char *line, t_global *all)
{
	g_data.lex = lexer(line);
	if (syntax_errors(g_data.lex))
	{
		free_lexer(g_data.lex->head);
		free(g_data.listt);
		g_data.glob_exit = 258;
		return (1);
	}
	expan_var(&g_data.lex->head, all->env_list);
	parse1(g_data.lex->head, all);
	free_lexr_n2(g_data.lex->head);
	free(g_data.listt);
	free_arg2(g_data.parcecmd);
	return (0);
}
