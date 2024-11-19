/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:09:33 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/18 15:11:04 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	copy_to(char *env, char **dst, size_t i, int j)
{
	while (env[i] != '=' && env[i] != '+' && env[i])
	{
		dst[0][i] = env[i];
		i++;
	}
	dst[0][i++] = '\0';
	if (!env[i - 1])
	{
		free(dst[1]);
		dst[1] = NULL;
		return ;
	}
	if (env[i] == '=')
		i++;
	if (!env[i - 1])
		i--;
	while (env[i])
	{
		dst[1][j] = env[i];
		i++;
		j++;
	}
	dst[1][j] = '\0';
}

char	**var_val(char *env)
{
	size_t	i;
	char	**dst;
	int		j;

	j = 0;
	i = 0;
	while (env[i] && env[i] != '=' && env[i] != '+')
		i++;
	dst = malloc(sizeof(char *) * 3);
	dst[0] = malloc(i + 1);
	dst[1] = malloc((ft_strlen(env) - i) + 1);
	i = 0;
	copy_to(env, dst, i, j);
	dst[2] = NULL;
	return (dst);
}

void	store_env(t_env **envi, char **env)
{
	int		i;
	t_env	*ptr;

	ptr = *envi;
	i = 0;
	while (env[i])
	{
		ft_lstadd_back_mini(envi, ft_lstnew_mini(env[i]));
		i++;
	}
	if (!get_env(*envi, "OLDPWD", NULL, 0))
	{
		ft_lstadd_back_mini(envi, ft_lstnew_mini("OLDPWD"));
	}
	else
	{
		del_node(envi, "OLDPWD");
		ft_lstadd_back_mini(envi, ft_lstnew_mini("OLDPWD"));
	}
}

void	read_miniline(t_global all, char **env)
{
	char	*input;

	while (1)
	{
		input = readline("minishell>");
		if (!input)
		{
			printf("exit\n");
			exit(g_data.glob_exit);
		}
		all.all_cmd = NULL;
		if (input && input[0])
			add_history(input);
		if (!lunch_shell(input, &all))
		{
			execution_mini(&all, env);
			free_cmds(all.all_cmd);
		}
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_global	all;

	(void)ac;
	(void)av;
	g_data.glob_exit = EXIT_SUCCESS;
	store_env(&all.env_list, env);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	read_miniline(all, env);
}
