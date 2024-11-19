/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 00:48:22 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/17 19:57:50 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	**fill_arg(char **src)
{
	int		i;
	int		j;
	char	**dst;

	i = 1;
	j = 0;
	if (!src[0])
		return (NULL);
	while (src[i])
		i++;
	dst = malloc((i + 1) * (sizeof(char *)));
	i = 1;
	while (src[i] != NULL)
	{
		dst[j] = ft_strdup(src[i]);
		free(src[i]);
		i++;
		j++;
	}
	dst[j] = NULL;
	return (dst);
}

void	fille_cmd(t_cmd **fcmd, t_cmd_pipe *full_cmd)
{
	*fcmd = NULL;
	while (full_cmd)
	{
		lstadd_back_cmd(fcmd, lstnew_cmd(full_cmd));
		full_cmd = full_cmd->next;
	}
}

void	free_lexr_n2(t_elm *ptr)
{
	t_elm	*hold;

	while (ptr)
	{
		if (ptr->type != LIMIT && ptr->type != FILE_NAME)
			free(ptr->content);
		hold = ptr->next;
		free(ptr);
		ptr = hold;
	}
}

void	free_arg2(t_cmd_pipe *ptr1)
{
	t_cmd_pipe	*hold;

	while (ptr1)
	{
		free(ptr1->args);
		hold = ptr1->next;
		free(ptr1);
		ptr1 = hold;
	}
}
