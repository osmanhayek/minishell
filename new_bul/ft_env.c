/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:24:28 by baer              #+#    #+#             */
/*   Updated: 2023/08/08 20:32:57 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
