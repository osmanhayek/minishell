/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsepushback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:36:05 by baer              #+#    #+#             */
/*   Updated: 2023/08/06 22:42:08 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser_lexfirst_node(t_simple_cmds *temporary, char *str)
{
	temporary->redirections = (t_lexer *)malloc(sizeof(t_lexer));
	if (!temporary->redirections)
		return ;
	temporary->redirections->next = NULL;
	temporary->redirections->prev = NULL;
	if (ft_find_token(str))
		temporary->redirections->token = ft_find_token(str);
	temporary->redirections->str = ft_strdup(str);
	temporary->redirections->i = 0;
	if (str[0] == '"')
		temporary->redirections->is_quote = 2;
	else if (str[0] == '\'')
		temporary->redirections->is_quote = 1;
	else
		temporary->redirections->is_quote = 0;
}

void	ft_parser_lexlast_node(t_simple_cmds *temporary, char *str)
{
	t_lexer	*new;
	t_lexer	*temp;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return ;
	new->next = NULL;
	if (ft_find_token(str))
		new->token = ft_find_token(str);
	new->str = ft_strdup(str);
	temp = temporary->redirections;
	while (temp->next)
		temp = temp->next;
	new->prev = temp;
	temp->next = new;
	new->i = new->prev->i + 1;
	if (str[0] == '"')
		new->is_quote = 2;
	else if (str[0] == '\'')
		new->is_quote = 1;
	else
		new->is_quote = 0;
}

void	ft_parser_lexpush_back(t_simple_cmds *temporary, char *str)
{
	if (!temporary->redirections)
	{
		ft_parser_lexfirst_node(temporary, str);
		return ;
	}
	ft_parser_lexlast_node(temporary, str);
}
