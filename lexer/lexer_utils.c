/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:07:46 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/17 19:57:50 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f'
		|| c == '\n');
}

t_list	*in_list(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
	{
		return (NULL);
	}
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

t_elm	*new_elem(char *content, int len, enum e_token type, enum e_state state)
{
	t_elm	*elm;
	char	*content_copy;

	elm = malloc(sizeof(t_elm));
	if (!elm)
	{
		return (NULL);
	}
	content_copy = malloc(len + 1);
	if (!content_copy)
	{
		free(elm);
		return (NULL);
	}
	ft_memcpy(content_copy, content, len);
	content_copy[len] = '\0';
	elm->content = content_copy;
	elm->len = len;
	elm->type = type;
	elm->state = state;
	elm->next = NULL;
	elm->prev = NULL;
	return (elm);
}

void	add_link(t_list *list, t_elm *new)
{
	if (ft_check_emp(list))
		list->head = new;
	else
	{
		list->tail->next = new;
		new->prev = list->tail;
	}
	list->tail = new;
	list->size++;
}

int	ft_word(t_list *token, char *str, enum e_state state)
{
	int	i;

	i = 0;
	while (!is_char(str[i]))
		i++;
	add_link(token, new_elem(str, i, WORD, state));
	return (i);
}
