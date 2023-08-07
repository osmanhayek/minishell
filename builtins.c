/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 22:07:47 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/07 00:14:25 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_global *mini, struct s_simple_cmds *head)
{
	char	cwd[1024];

	if (head->str[1])
	{
		ft_putstr_fd("pwd: too many arguments", 2);
		g_global.error_num = 1;
		return (0);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putchar_fd('\n', 1);
	}
	else
	{
		ft_putstr_fd("pwd: error getting current directory\n", 2);
		g_global.error_num = 1;
	}
	(void)mini;
	return (1);
}

int	ft_env(t_global *mini, struct s_simple_cmds *head)
{
	int	i;

	if (head->str[1])
	{
		ft_putstr_fd(head->str[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_global.error_num = 127;
		return (0);
	}
	i = 0;
	while (mini->env[i])
	{
		ft_putstr_fd(mini->env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (1);
}
