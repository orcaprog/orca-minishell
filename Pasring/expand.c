/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:49:26 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/21 10:37:00 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*get_env_expand(t_env *env, char *s)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strcmp(ptr->key, s))
		{
			return (ptr->value);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

void	expan_var(t_elm **data, t_env *env)
{
	t_elm	*ptr;
	char	*hold;

	expand_quot(data);
	convert_to_word(data);
	expand_env(data, env);
	ptr = *data;
	while (ptr)
	{
		if (ptr->next && ptr->type == WORD && ptr->next->type == WORD)
		{
			ptr->type = IGNOR;
			hold = ptr->next->content;
			ptr->next->content = ft_strjoin(ptr->content, ptr->next->content);
			ptr->next->len = ft_strlen(ptr->next->content);
			free(hold);
		}
		ptr = ptr->next;
	}
}
