/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:25:11 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/18 11:06:28 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	check_nbword(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c)
			word++;
		i++;
	}
	return (word);
}

int	num_arg(char **str)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (str[i])
	{
		k += check_nbword(str[i], ' ');
		i++;
	}
	return (k);
}

char	**join_strs(char **str)
{
	t_val	val;

	val.j = 0;
	val.i = 0;
	val.k = 0;
	val.k = num_arg(str);
	val.join = malloc(sizeof(char *) * (val.k + 1));
	val.i = 0;
	val.k = 0;
	while (str[val.i])
	{
		val.j = 0;
		val.help = ft_split(str[val.i], ' ');
		while (val.help[val.j])
		{
			val.join[val.k] = val.help[val.j];
			val.k++;
			val.j++;
		}
		free(val.help);
		val.i++;
	}
	val.join[val.k] = NULL;
	return (val.join);
}

int	cheack_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	cmd_exit(char **ptr)
{
	int		i;
	char	**str;

	i = 0;
	str = join_strs(ptr);
	printf("exit\n");
	if (!str[0])
		exit(g_data.glob_exit);
	if (str[0] && cheack_is_num(str[0]) && str[1])
	{
		free_all(str, NULL);
		p_error("exit");
		p_error(": too many arguments\n");
	}
	else
		exit(ft_atoi(str[0]));
}
