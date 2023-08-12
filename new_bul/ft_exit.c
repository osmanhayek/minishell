/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:53:02 by baer              #+#    #+#             */
/*   Updated: 2023/08/12 06:18:45 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalldigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
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
		ft_bexit(mini, 255);
	}
	else if (parser->str[1])
		ft_bexit(mini, ft_atoi(parser->str[1]));
	else
		ft_bexit(mini, 0);
	return (0);
}
