/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:32:28 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/17 22:04:55 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_pipes(t_global *mini)
{
	t_simple_cmds	*temp;

	temp = mini->p_head;
	while (temp->next)
	{
		if (pipe(temp->prcs.fd) == -1)
		{
			perror("bash: ");
			g_global.error_num = 1;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

void	close_pipes(t_global *mini, int current)
{
	t_simple_cmds	*temp;

	(void)current;
	temp = mini->p_head;
	while (temp->next)
	{
		if (temp->prcs.fd[0])
			close(temp->prcs.fd[0]);
		if (temp->prcs.fd[1])
			close(temp->prcs.fd[1]);
		temp = temp->next;
	}
}

void	ft_wait_prcs(t_global *mini, int *status)
{
	t_simple_cmds	*temp;

	temp = mini->p_head;
	while (temp)
	{
		if (!temp->next)
			waitpid(temp->prcs.pid, status, 0);
		else
			waitpid(temp->prcs.pid, NULL, 0);
		temp = temp->next;
	}
}

void	set_heredoc_for_multi(t_global *mini)
{
	t_simple_cmds	*temp;
	t_lexer			*red;

	temp = mini->p_head;
	while (temp)
	{
		if (temp->redirections)
		{
			red = temp->redirections;
			while (red)
			{
				if (red->token == LESS_LESS)
				{
					if (temp->in_her)
						close(temp->in_her);
					// bunu degistir UNUTMA!!!
					temp->in_her = ft_her(red, "simple_temp.txt");
					if (temp->in_her == -1)
						return ;
				}
				red = red->next->next;
			}
		}
		temp = temp->next;
	}
}

void	ft_set_pipes(t_global *mini, t_simple_cmds *temp, int i)
{
	if (i != 0)
	{
		if (dup2(temp->prev->prcs.fd[0], 0) < 0)
		{
			perror("bash: ");
			exit(EXIT_FAILURE);
		}
	}
	if (temp->next)
	{
		if (dup2(temp->prcs.fd[1], 1) < 0)
		{
			perror("bash: ");
			exit(EXIT_FAILURE);
		}
	}
	close_pipes(mini, i);
}
