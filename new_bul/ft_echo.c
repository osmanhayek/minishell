/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:25:32 by baer              #+#    #+#             */
/*   Updated: 2023/08/12 11:33:18 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd(str[i++], 1);
		if (str[i])
			ft_putchar_fd(' ', 1);
	}
}

int	ft_echo(t_global *mini, t_simple_cmds *parser)
{
	int	i;
	int	j;
	int	n_flag;

	(void)mini;
	n_flag = 0;
	i = 1;
	while (parser->str[i] && parser->str[i][0] == '-' && \
	parser->str[i][1] == 'n')
	{
		j = 1;
		while (parser->str[i][j] == 'n')
			j++;
		if (parser->str[i][j] != '\0')
			break ;
		else
			n_flag = 1;
		i++;
	}
	ft_print(parser->str + i);
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
