/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutiple_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:52:17 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/17 22:08:37 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_red_multi(t_global *mini, t_simple_cmds *temp, int has_slash)
{
	if (ft_set_red(temp->redirections) == -1)
		exit(1);
	if (!has_slash && !temp->builtin)
		if (ft_check_replace(temp, mini) == -1)
			exit(127);
	if (ft_check_last(temp->redirections))
	{
		if (g_global.in_red)
		{
			close(g_global.in_red);
			g_global.in_red = 0;
		}
		dup2(temp->in_her, 0);
	}
	else if (!ft_check_last(temp->redirections) && g_global.in_red)
	{
		if (g_global.in_her)
			close(g_global.in_her);
		dup2(g_global.in_red, 0);
	}
	if (g_global.out_red)
		dup2(g_global.out_red, 1);
}

void	ft_fork_multi(t_global *mini, t_simple_cmds *temp, int *has_slash, \
int i)
{
	int	status;

	*has_slash = ft_search_slash(temp->str[0]);
	temp->prcs.pid = fork();
	if (temp->prcs.pid == 0)
	{
		ft_set_pipes(mini, temp, i);
		if (temp->redirections)
			ft_set_red_multi(mini, temp, *has_slash);
		else if (!*has_slash && !temp->builtin && temp->str[0][0])
			if (ft_check_replace(temp, mini) == -1)
				exit(127);
		if (*has_slash && temp->str[0])
		{
			status = ft_check_slash(temp->str[0]);
			if (status)
				exit(status);
		}
		if (temp->builtin)
			exit(temp->builtin(mini, temp));
		if (!temp->str[0][0])
		{
			ft_putstr_fd("bash: Command not found\n", 2);
			exit(127);
		}
		execve(temp->str[0], temp->str, mini->env);
		perror("bash: ");
		exit(EXIT_FAILURE);
	}
	else if (temp->prcs.pid < 0)
	{
		perror("bash: ");
		exit(EXIT_FAILURE);
	}
}

int	one_of_them(t_global *mini)
{
	t_simple_cmds	*temp;

	temp = mini->p_head;
	if (!temp)
		return (0);
	while (temp)
	{
		if (temp->in_her == -1)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	ft_set_status(int status)
{
	if (WIFEXITED(status))
		g_global.error_num = WEXITSTATUS(status);
}

void	ft_multiple_command(t_global *mini)
{
	t_simple_cmds	*temp;
	int				i;
	int				status;
	int				has_slash;

	if (ft_open_pipes(mini) == 0)
		return ;
	temp = mini->p_head;
	i = 0;
	set_heredoc_for_multi(mini);
	if (one_of_them(mini))
	{
		close_pipes(mini, 10);
		return ;
	}
	g_global.test2 = 1;
	while (temp)
	{
		ft_fork_multi(mini, temp, &has_slash, i);
		temp = temp->next;
		i++;
	}
	close_pipes(mini, i);
	ft_wait_prcs(mini, &status);
	ft_set_status(status);
}
