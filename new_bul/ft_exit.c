/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:53:02 by baer              #+#    #+#             */
/*   Updated: 2023/08/15 22:52:58 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_atol(char *nptr)
{
	long long	result;
	int			a;

	while (*nptr == '\n' || *nptr == '\t' || *nptr == '\r' \
	|| *nptr == '\v' || *nptr == '\f' || *nptr == ' ')
		nptr++;
	a = *nptr == '-';
	nptr += (a || *nptr == '+');
	result = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = (result * 10) + *nptr++ - '0';
	}
	return (result * ((a * -2) + 1));
}

int	ft_isalldigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

void	ft_bexit(t_global *mini, int exitcode)
{
	ft_deallocate_all(mini);
	exit(exitcode);
}

int	ft_exit(t_global *mini, struct s_simple_cmds *parser)
{
	ft_putendl_fd("exit", 2);
	if (parser->str[1] && parser->str[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (parser->str[1] && !ft_isalldigit(parser->str[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(parser->str[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_bexit(mini, -1);
	}
	else if (parser->str[1])
		ft_bexit(mini, ft_atol(parser->str[1]));
	else
		ft_bexit(mini, 0);
	return (0);
}
