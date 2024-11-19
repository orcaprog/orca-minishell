/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tool_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:03:09 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/20 23:24:47 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	between_quot(t_elm *ptr1)
{
	while (ptr1)
	{
		if (ptr1 && (ptr1->type == DOUBLE_QUOTE || ptr1->type == QOUTE))
		{
			if (ptr1->next && ptr1->next->type != WHITE_SPACE)
			{
				if (ptr1->prev && ptr1->prev->type == WORD)
					ptr1->prev->type = TEMP;
			}
		}
		if (!ptr1)
			break ;
		ptr1 = ptr1->next;
	}
}

void	less_red(t_elm **ptr1)
{
	char	*hold;

	*ptr1 = (*ptr1)->next;
	if ((*ptr1)->next)
	{
		*ptr1 = (*ptr1)->next;
		while ((*ptr1)->type == WHITE_SPACE)
			*ptr1 = (*ptr1)->next;
		if ((*ptr1)->type == TEMP)
			*ptr1 = (*ptr1)->next;
		while ((*ptr1)->type == IGNOR || (*ptr1)->type == IGNO)
			(*ptr1) = (*ptr1)->next;
		if ((*ptr1)->type == DOUBLE_QUOTE || (*ptr1)->type == QOUTE)
		{
			hold = (*ptr1)->content;
			(*ptr1)->content = parse_quotes2((*ptr1), (*ptr1)->type, LIMIT);
			(*ptr1)->state = IN_DQUOTE;
			(*ptr1)->type = LIMIT;
			free(hold);
		}
		else
			(*ptr1)->type = LIMIT;
	}
}

void	all_red(t_elm **ptr1)
{
	char	*hold;

	if ((*ptr1)->type == MORE_RED)
		(*ptr1) = (*ptr1)->next;
	if ((*ptr1)->next)
	{
		(*ptr1) = (*ptr1)->next;
		while ((*ptr1)->type == WHITE_SPACE)
			(*ptr1) = (*ptr1)->next;
		if ((*ptr1)->type == TEMP)
			(*ptr1) = (*ptr1)->next;
		while ((*ptr1)->type == IGNOR || (*ptr1)->type == IGNO)
			(*ptr1) = (*ptr1)->next;
		if ((*ptr1)->type == DOUBLE_QUOTE || (*ptr1)->type == QOUTE)
		{
			hold = (*ptr1)->content;
			(*ptr1)->content = parse_quotes2((*ptr1), (*ptr1)->type, FILE_NAME);
			(*ptr1)->type = FILE_NAME;
			free(hold);
		}
		else
			(*ptr1)->type = FILE_NAME;
	}
}

void	parse_red(t_elm *ptr1)
{
	while (ptr1)
	{
		if (ptr1->type == LESS_RED)
		{
			less_red(&ptr1);
			if (!ptr1)
				break ;
		}
		else if (ptr1->type == IN_RED || ptr1->type == MORE_RED
			|| ptr1->type == OUT_RED)
		{
			all_red(&ptr1);
			if (!ptr1)
				break ;
		}
		ptr1 = ptr1->next;
	}
}
