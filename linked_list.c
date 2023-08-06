/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:34:21 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/06 17:00:07 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_index(t_global *mini)
{
	t_lexer	*temp;
	int		i;

	temp = mini->head;
	i = 0;
	while (temp)
	{
		temp->i = i++;
		temp = temp->next;
	}
}

// void	ft_delete_node(int index, t_global *mini)
// {
// 	t_lexer	*temp;

// 	temp = mini->head;
// 	if (!temp)
// 		return ;
// 	while (temp->i != index)
// 		temp = temp->next;
// 	if (temp->prev && temp->next)
// 	{
// 		temp->prev->next = temp->next;
// 		temp->next->prev = temp->prev;
// 	}
// 	else if (temp->prev && !temp->next)
// 		temp->prev->next = temp->next;
// 	else if (!temp->prev && temp->next)
// 	{
// 		mini->head = temp->next;
// 		mini->head->prev = NULL;
// 	}
// 	free(temp->str);
// 	free(temp);
// 	ft_set_index(mini);
// }


void	ft_delete_node(int index, t_global *mini)
{
	t_lexer	*temp;

	temp = mini->head;
	if (!temp)
		return ;
	while (temp->i != index && temp->next)
		temp = temp->next;

	if (temp->i != index)
		return ;

	if (temp->prev)
		temp->prev->next = temp->next;
	else
		mini->head = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;

	free(temp->str);
	free(temp);
	ft_set_index(mini);
}
