/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 22:07:47 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/12 11:34:29 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_printexport(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		printf("declare -x %s\n", str[i++]);
	return (0);
}

int	ft_pwd(t_global *mini, struct s_simple_cmds *head)
{
	char	cwd[1024];

	(void)head;
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
	return (0);
}
