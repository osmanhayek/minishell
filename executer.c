/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 23:04:41 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/12 13:08:11 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_when_no_red(t_global *mini, int has_slash)
{
	if (!has_slash && !mini->p_head->builtin)
		if (ft_check_replace(mini->p_head, mini) == -1)
			exit(127);
	if (mini->p_head->builtin)
		exit(mini->p_head->builtin(mini, mini->p_head));
	execve(mini->p_head->str[0], mini->p_head->str, mini->env);
	perror("bash: ");
	exit(1);
}

void	ft_set_has(t_global *mini, int *has_slash, int *is_spec)
{
	*has_slash = ft_search_slash(mini->p_head->str[0]);
	*is_spec = ft_search_builtin(mini->p_head->str[0]);
	g_global.test2 = 1;
}

void	ft_wait_single(pid_t pid, int *wait_status)
{
	waitpid(pid, wait_status, 0);
	if (WIFEXITED(wait_status))
		g_global.error_num = WEXITSTATUS(wait_status);
}

void	ft_single_command(t_global *mini)
{
	int		has_slash;
	int		is_spec;
	int		wait_status;
	pid_t	pid;

	ft_set_has(mini, &has_slash, &is_spec);
	if (has_slash || !is_spec)
	{
		pid = fork();
		if (pid == 0)
		{
			if (mini->p_head->redirections)
			{
				ft_check_red(mini, has_slash);
				if (g_global.in_her == -1)
					exit(1);
			}
			else
				ft_set_when_no_red(mini, has_slash);
		}
		ft_wait_single(pid, &wait_status);
	}
	else
		ft_parent(mini);
}

void	ft_executer(t_global *mini)
{
	int	size;

	size = ft_size_cmds(mini);
	if (size == 0)
		return ;
	else if (size == 1)
		ft_single_command(mini);
	else
		ft_multiple_command(mini);
}
