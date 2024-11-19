/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_qoutes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 00:09:24 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/17 19:57:50 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*parse_tool(t_elm *ptr, enum e_token type2, char *str)
{
	while (ptr && ptr->type != WHITE_SPACE && ptr->type != PIPE_LINE)
	{
		while (ptr && (ptr->type == DOUBLE_QUOTE || ptr->type == QOUTE
				|| ptr->type == IGNOR || ptr->type == IGNO))
		{
			free(ptr->content);
			ptr->type = type2;
			ptr = ptr->next;
		}
		if (!ptr || ptr->type == WHITE_SPACE || ptr->type == PIPE_LINE)
			break ;
		str = ft_strjoin2(str, ptr->content);
		free(ptr->content);
		ptr->type = type2;
		ptr = ptr->next;
	}
	return (str);
}

char	*parse_quotes2(t_elm *ptr1, enum e_token type, enum e_token type2)
{
	char	*str;
	t_elm	*ptr;

	(void)type;
	str = ft_strdup("");
	ptr = ptr1;
	if (ptr->prev && ptr->prev->type == TEMP)
		str = ft_strjoin2(str, ptr->prev->content);
	ptr = ptr->next;
	ptr->type = type2;
	return (parse_tool(ptr, type2, str));
}

char	*parse_quotes(t_elm **ptr, enum e_token type)
{
	char	*str;

	(void)type;
	str = ft_strdup("");
	if ((*ptr)->prev && (*ptr)->prev->type == TEMP)
		str = ft_strjoin2(str, (*ptr)->prev->content);
	*ptr = (*ptr)->next;
	while (*ptr && (*ptr)->type != WHITE_SPACE && (*ptr)->type != PIPE_LINE)
	{
		while (*ptr && ((*ptr)->type == DOUBLE_QUOTE || (*ptr)->type == QOUTE
				|| (*ptr)->type == IGNOR || (*ptr)->type == IGNO))
		{
			*ptr = (*ptr)->next;
		}
		if (!*ptr || (*ptr)->type == WHITE_SPACE || (*ptr)->type == PIPE_LINE)
		{
			break ;
		}
		str = ft_strjoin2(str, (*ptr)->content);
		*ptr = (*ptr)->next;
	}
	return (str);
}

void	count_quotes_redir_args(t_elm **elem, enum e_token type, int *i)
{
	if (type == DOUBLE_QUOTE || type == QOUTE)
	{
		(*elem) = (*elem)->next;
		while ((*elem) && (*elem)->type != type)
			(*elem) = (*elem)->next;
		(*i)++;
	}
	else if (is_redir(type))
	{
		while ((*elem)->type != WORD && (*elem)->type != ENV)
			(*elem) = (*elem)->next;
		(*elem) = (*elem)->next;
	}
}
