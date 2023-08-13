/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 06:44:05 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/12 23:21:04 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parent(t_global *mini)
{
	if (mini->p_head->redirections)
	{
		ft_set_heredoc(mini->p_head->redirections);
		if (g_global.in_her == -1)
			return ;
		if (ft_set_red(mini->p_head->redirections) == -1)
		{
			g_global.error_num = 1;
			return ;
		}
	}
	if (g_global.in_her)
		close(g_global.in_her);
	if (g_global.out_red)
		close(g_global.out_red);
	if (g_global.in_red)
		close(g_global.in_red);
	g_global.error_num = mini->p_head->builtin(mini, mini->p_head);
}

void	ft_check_red(t_global *mini, int has_slash)
{
	ft_set_heredoc(mini->p_head->redirections);
	if (g_global.in_her == -1)
		return ;
	if (ft_set_red(mini->p_head->redirections) == -1)
		exit(1);
	if (!has_slash && !mini->p_head->builtin)
		if (ft_check_replace(mini->p_head, mini) == -1)
			exit(127);
	if (ft_check_last(mini->p_head->redirections))
	{
		if (g_global.in_red)
			close(g_global.in_red);
		dup2(g_global.in_her, 0);
	}
	else if (!ft_check_last(mini->p_head->redirections) && g_global.in_red)
	{
		if (g_global.in_her)
			close(g_global.in_her);
		dup2(g_global.in_red, 0);
	}
	ft_set_global(mini);
}
