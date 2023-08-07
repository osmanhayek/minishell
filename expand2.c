/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:22:56 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/06 18:54:21 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_valid(char c)
{
	if (c == '_' || ft_isalpha(c))
		return (1);
	return (0);
}

void	ft_check_delete(t_global *mini)
{
	t_lexer	*temp;

	temp = mini->head;
	while (temp)
	{
		if (!temp->str[0] && temp->is_quote == 0)
			ft_delete_node(temp->i, mini);
		temp = temp->next;
	}
}
