/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 08:27:13 by ooussaad          #+#    #+#             */
/*   Updated: 2023/05/20 23:45:22 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

t_redirect	*my_red(t_redir *red)
{
	t_redirect	*ptr;
	t_redir		*hold;

	hold = red;
	ptr = NULL;
	while (red)
	{
		hold = red->next;
		if (red->type == LESS_RED)
			lstadd_back_red2(&ptr, new_nodered(HEREDOC, red->arg, NULL,
					red->state));
		else if (red->type == IN_RED)
			lstadd_back_red2(&ptr, new_nodered(LESS, NULL, red->arg, 0));
		else if (red->type == OUT_RED)
			lstadd_back_red2(&ptr, new_nodered(GREAT, NULL, red->arg, 0));
		else if (red->type == MORE_RED)
			lstadd_back_red2(&ptr, new_nodered(EXPAND, NULL, red->arg, 0));
		free(red);
		red = hold;
	}
	free(hold);
	return (ptr);
}

t_redir	*red_list(t_elm *ptr)
{
	int		temp;
	t_redir	*list_red;

	temp = 0;
	list_red = NULL;
	while (ptr && ptr->type != PIPE_LINE)
	{
		if (ptr->type == LESS_RED)
		{
			while (ptr->type != LIMIT)
				ptr = ptr->next;
			lstadd_back_red(&list_red, lstnew_red(ptr, LESS_RED, ptr->state));
		}
		else if (ptr->type == IN_RED || ptr->type == MORE_RED
			|| ptr->type == OUT_RED)
		{
			temp = ptr->type;
			while (ptr->type != FILE_NAME)
				ptr = ptr->next;
			lstadd_back_red(&list_red, lstnew_red(ptr, temp, ptr->state));
		}
		ptr = ptr->next;
	}
	return (list_red);
}
