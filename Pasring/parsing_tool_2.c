/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tool_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooussaad <ooussaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 00:52:16 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/22 20:45:39 by ooussaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

t_elm	*check_unclosed_quotes(t_elm **ptr, enum e_token type)
{
	while (*ptr)
	{
		*ptr = (*ptr)->next;
		if (!*ptr || (*ptr)->type == type)
			break ;
	}
	if (!*ptr)
		write(2, "minishell: syntax error\n", 25);
	return (*ptr);
}

void	lotof_quot(t_elm **elem, enum e_token type1, enum e_token type2,
	enum e_token type3)
{
	if (set_doublquot(elem, type1, type2, type3))
	{
		if ((!(*elem)->next || (*elem)->next->type == WHITE_SPACE))
		{
			(*elem)->type = WORD;
			free((*elem)->content);
			(*elem)->content = ft_strdup("");
		}
	}
}

void	to_word(t_elm **elem)
{
	*elem = (*elem)->next;
	while (*elem && (*elem)->type != DOUBLE_QUOTE)
	{
		while ((*elem)->type == ENV)
			*elem = (*elem)->next;
		if ((*elem)->type == DOUBLE_QUOTE)
		{
			break ;
		}
		if ((*elem)->type != DOUBLE_QUOTE && (*elem)->type != IGNOR)
			(*elem)->type = WORD;
		*elem = (*elem)->next;
	}
	if ((*elem) && (*elem)->type == DOUBLE_QUOTE)
		*elem = (*elem)->next;
}

void	expand_env_var(t_elm *ptr, t_env *env)
{
	char	*str;

	if (!ft_strcmp(ptr->content, "$?"))
	{
		free(ptr->content);
		ptr->content = ft_itoa(g_data.glob_exit);
		ptr->len = ft_strlen(ptr->content);
	}
	else if (ft_strcmp(ptr->content, "$"))
	{
		str = get_env_expand(env, ptr->content + 1);
		if (str)
		{
			free(ptr->content);
			ptr->content = ft_strdup(str);
			ptr->len = ft_strlen(ptr->content);
		}
		else
		{
			free(ptr->content);
			ptr->content = ft_strdup("");
		}
	}
	ptr->type = WORD;
}
