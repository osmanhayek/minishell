/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:52:25 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/07 05:19:01 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display(t_global *mini)
{
	t_lexer	*temp;

	temp = mini->head;
	while (temp)
	{
		printf("%d %s %d %d \n", temp->i, temp->str, temp->token, temp->is_quote);
		temp = temp->next;
	}
}

int	main(int ac, char **av, char **ev)
{
	char		*line;
	t_global	mini;

	if (ac > 1)
		exit(1);
	mini.env = ev;
	g_global.env = ev;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			exit(1);
		add_history(line);
		ft_init_lexer(&mini, line);
		if (ft_check_error(&mini))
		{
			ft_deallocate_lexer(&mini);
			free(line);
			continue ;
		}
		ft_expand(&mini);
		ft_init_parser(&mini);
		free(line);
	}
}
