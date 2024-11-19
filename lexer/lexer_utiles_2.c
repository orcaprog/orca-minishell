/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utiles_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooussaad <ooussaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:34:31 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/22 20:25:21 by ooussaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	get_env_var(t_list *tokens, char *str, enum e_state state)
{
	int	i;

	i = 1;
	if (str[i] == '?' || (str[i] >= '0' && str[i] <= '9'))
		i++;
	else
		while (str[i] && (ft_isalpha(str[i])
				|| ft_isdigit(str[i]) || str[i] == '_'))
			i++;
	add_link(tokens, new_elem(str, i, ENV, state));
	return (i);
}

int	env_white(t_list *token, char *str, enum e_state *state)
{
	int	i;

	i = 1;
	add_link(token, new_elem(str, i, WORD, *state));
	return (i);
}

int	env_signe(t_list *token, char *str, enum e_state *state)
{
	int	i;

	i = 2;
	add_link(token, new_elem(str, i, ENV, *state));
	return (i);
}
