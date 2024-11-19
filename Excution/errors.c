/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooussaad <ooussaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:47:29 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/18 00:04:21 by ooussaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	check_error(char *str, int n)
{
	if (n == -1)
	{
		perror(str);
		exit(1);
	}
}

void	p_error(char *str)
{
	ft_putstr_fd(str, 2);
	g_data.glob_exit = 1;
}

void	free_cmds(t_cmd *ptr)
{
	t_cmd		*hold;
	t_redirect	*red;
	t_redirect	*hold1;

	while (ptr)
	{
		red = ptr->list_of_red;
		while (red)
		{
			free(red->here_lim);
			free(red->filename);
			hold1 = red->next;
			free(red);
			red = hold1;
		}
		free_all(ptr->args, ptr->cmd);
		hold = ptr->next;
		free(ptr);
		ptr = hold;
	}
}
