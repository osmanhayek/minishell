/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:11:08 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/11 21:34:16 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freearr(char ***str)
{
	int	i;

	i = 0;
	if (!(*str))
		return ;
	while ((*str)[i])
		free((*str)[i++]);
	free((*str));
	*str = NULL;
}

void	ft_deallocate_lexer(t_global *mini)
{
	t_lexer	*temp;

	temp = mini->head;
	while (mini->head)
	{
		free(mini->head->str);
		temp = mini->head->next;
		free(mini->head);
		mini->head = temp;
	}
}

void	ft_deallocate_lexlist(t_lexer **list)
{
	t_lexer	*temp;

	temp = (*list);
	if (!(*list))
		return ;
	while ((*list))
	{
		free((*list)->str);
		(*list)->str = NULL;
		temp = (*list)->next;
		free((*list));
		(*list) = temp;
	}
}

void	ft_deallocate_parser(t_global *mini)
{
	t_simple_cmds	*temp;

	temp = mini->p_head;
	while (mini->p_head)
	{
		if (mini->p_head->hd_file_name)
		{
			free(mini->p_head->hd_file_name);
			mini->p_head->hd_file_name = NULL;
		}
		ft_deallocate_lexlist(&(mini->p_head->redirections));
		ft_freearr(&(mini->p_head->str));
		temp = mini->p_head->next;
		free(mini->p_head);
		mini->p_head = temp;
	}
}

void	ft_deallocate_all(t_global *mini)
{
	ft_skipinit(NULL, 1);
	ft_deallocate_parser(mini);
	ft_deallocate_lexer(mini);
}
