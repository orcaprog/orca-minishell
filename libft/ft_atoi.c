/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:18:32 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/18 08:54:17 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	print_err(char *str, char *str1, char *str2)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(str2, 2);
}

int	print_retun(char *str)
{
	print_err("exit: ", str, ": numeric argument required");
	return (255);
}

int	tak_sign(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

int	ft_atoi(char *str)
{
	int					i;
	int					sign;
	size_t				rslt;

	i = 0;
	rslt = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+' )
	{
		sign *= tak_sign(str[i]);
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		rslt = (rslt * 10) + (str[i] - '0');
		if ((rslt > __LONG_MAX__ && sign == 1)
			|| (rslt > __LONG_MAX__ && sign == -1))
			return (print_retun(str));
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (print_retun(str));
	return ((rslt * sign));
}
