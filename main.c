/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:52:25 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/02 02:15:30 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display(t_global *mini)
{
	t_lexer	*temp;

	temp = mini->head;
	while (temp)
	{
		printf("%d %s %d\n", temp->i, temp->str, temp->token);
		temp = temp->next;
	}
}

int	main(int ac, char **av, char **ev)
{
	char		*line;
	t_global	mini;

	if (ac > 1)
		exit(1);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			exit(1);
		ft_init_lexer(&mini, line);
		free(line);
	}
}
