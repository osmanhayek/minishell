/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:11:08 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/03 16:14:38 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
