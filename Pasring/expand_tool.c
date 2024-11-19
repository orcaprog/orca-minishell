/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooussaad <ooussaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 00:04:33 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/22 18:26:37 by ooussaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	set_type(t_elm *ptr, enum e_token type, enum e_token type2)
{
	ptr = ptr->next;
	while (ptr && ptr->type != type)
		ptr = ptr->next;
	while (ptr && ptr->next && ptr->type == type
		&& ptr->next->type != WHITE_SPACE && ptr->next->type != PIPE_LINE)
	{
		ptr->type = type2;
		ptr = ptr->next;
	}
}

int	set_doublquot(t_elm **data, enum e_token type, enum e_token type2,
	enum e_token type3)
{
	int		i;
	t_elm	*ptr;

	i = 0;
	while ((*data)->next && (*data)->type == type
		&& (*data)->next->type != WHITE_SPACE && (*data)->next->type != WORD
		&& (*data)->next->type != ENV && (*data)->next->type != type3)
	{
		i++;
		(*data)->type = type2;
		(*data) = (*data)->next;
	}
	ptr = (*data);
	if (ptr->next && (i % 2 == 0 || ptr->next->type == WORD))
	{
		set_type(ptr, type, type2);
		return (0);
	}
	else
		return (1);
}

void	expand_quot(t_elm **data)
{
	t_elm	*elem;

	elem = *data;
	while (elem)
	{
		if (elem->next && elem->type == DOUBLE_QUOTE
			&& elem->next->type == DOUBLE_QUOTE)
		{
			lotof_quot(&elem, DOUBLE_QUOTE, IGNOR, QOUTE);
		}
		if (elem->next && elem->type == QOUTE && elem->next->type == QOUTE)
		{
			lotof_quot(&elem, QOUTE, IGNO, DOUBLE_QUOTE);
		}
		elem = elem->next;
	}
}

void	convert_to_word(t_elm **data)
{
	t_elm	*elem;

	elem = *data;
	while (elem)
	{
		if (elem && elem->type == DOUBLE_QUOTE
			&& elem->next && elem->next->state == IN_DQUOTE)
			to_word(&elem);
		if (elem && elem->type == QOUTE && elem->next
			&& elem->next->state == IN_QUOTE)
		{
			elem = elem->next;
			while (elem && elem->type != QOUTE)
			{
				if (elem->type != IGNO)
					elem->type = WORD;
				elem = elem->next;
			}
			if (elem && elem->type == QOUTE)
				elem = elem->next;
		}
		if (!elem)
			break ;
		elem = elem->next;
	}
}

void	expand_env(t_elm **data, t_env *env)
{
	t_elm	*ptr;

	ptr = *data;
	while (ptr)
	{
		if (ptr->type == ENV)
			expand_env_var(ptr, env);
		if (ptr->type == LESS_RED)
		{
			ptr = ptr->next->next;
			while (ptr->type == WHITE_SPACE || ptr->type == DOUBLE_QUOTE
				|| ptr->type == QOUTE)
				ptr = ptr->next;
			while (ptr && ptr->type != WHITE_SPACE && ptr->type != DOUBLE_QUOTE
				&& ptr->type != QOUTE && ptr->type != PIPE_LINE)
			{
				if (ptr->type == ENV)
					ptr->type = WORD;
				ptr = ptr->next;
			}
		}
		if (!ptr)
			break ;
		ptr = ptr->next;
	}
}
