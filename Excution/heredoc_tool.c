/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooussaad <ooussaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:52:29 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/22 18:07:05 by ooussaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	handle_sig(int signum)
{
	(void)signum;
	g_data.glob_exit = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*cheak_expand(t_env *env, t_elm *elem)
{
	char	*new_input;
	t_elm	*ptr;

	ptr = elem;
	while (ptr && ptr->type != ENV && !get_env_expand(env, &ptr->content[1]))
		ptr = ptr->next;
	if (!ptr)
		return (NULL);
	ptr = elem;
	new_input = ft_strdup("");
	while (ptr)
	{
		if (get_env_expand(env, &ptr->content[1]))
			new_input = ft_strjoin2(new_input, get_env_expand(env,
						&ptr->content[1]));
		else
			new_input = ft_strjoin2(new_input, ptr->content);
		ptr = ptr->next;
	}
	return (new_input);
}

void	free_this(t_elm	*elem, char *new_input)
{
	free_lexer(elem);
	free(g_data.listt);
	free(new_input);
}

void	get_herdoc(t_redirect *red, t_env *env, int *fd_pipe)
{
	char	*input;
	char	*new_input;
	t_elm	*elem;

	while (1)
	{
		input = readline(">");
		if (ft_strcmp(input, red->here_lim) == 0 || input == NULL)
			break ;
		elem = lexer(input)->head;
		if (!red->here_doc_expand)
		{
			new_input = cheak_expand(env, elem);
			if (new_input)
				free(input);
			else
				new_input = input;
		}
		else
			new_input = input;
		close(fd_pipe[0]);
		ft_putendl_fd(new_input, fd_pipe[1]);
		free_this(elem, new_input);
	}
	free(input);
}
