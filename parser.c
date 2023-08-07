/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:05:12 by baer              #+#    #+#             */
/*   Updated: 2023/08/07 04:38:33 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_forwardtwo(
// 	t_global *mini, t_simple_cmds *temp, t_lexer *lexer)
// {
// 	int	i;

// 	i = lexer->i;
// 	if (lexer->token == LESS_LESS)
// 		temp->hd_file_name = ft_strdup(lexer->next->str);
// 	ft_parser_lexpush_back(temp, lexer->str);
// 	lexer = lexer->next;
// 	ft_parser_lexpush_back(temp, lexer->str);
// 	ft_delete_node(i, mini);
// 	ft_delete_node(i, mini);
// 	temp->num_redirections++;
// }

// void	ft_init_parser_matrix(t_simple_cmds *temp, t_lexer *lexer)
// {
// 	int		i;
// 	int		j;
// 	t_lexer	*save;

// 	j = 0;
// 	i = 0;
// 	save = lexer;
// 	while (lexer && lexer->token != PIPE)
// 	{
// 		j++;
// 		lexer = lexer->next;
// 	}
// 	temp->str = malloc(sizeof(char *) * (j + 1));
// 	lexer = save;
// 	while (lexer && lexer->token != PIPE)
// 	{
// 		temp->str[i++] = ft_strdup(lexer->str);
// 		lexer = lexer->next;
// 	}
// 	temp->str[i] = NULL;
// }

// void	ft_parser_firstnode(t_global *mini, t_lexer *lexer)
// {
// 	mini->p_head = malloc(sizeof(t_simple_cmds));
// 	mini->p_head -> next = NULL;
// 	mini->p_head -> prev = NULL;
// 	mini->p_head->num_redirections = 0;
// 	mini->p_head->redirections = NULL;
// 	while (lexer && lexer->token != PIPE)
// 	{
// 		if (lexer->token)
// 		{
// 			ft_forwardtwo(mini, mini->p_head, lexer);
// 			lexer = lexer->next;
// 			continue ;
// 		}
// 		else
// 			lexer = lexer->next;
// 	}
// 	ft_init_parser_matrix(mini->p_head, mini->head);
// }


// void	ft_parser_lastnode(t_global *mini, t_lexer *lexer)
// {
// 	t_simple_cmds	*new;
// 	t_simple_cmds	*temp;
// 	t_lexer			*save;

// 	save = lexer;
// 	new = malloc(sizeof(t_simple_cmds));
// 	new->next = NULL;
// 	new ->redirections = NULL;
// 	temp = mini->p_head;
// 	while (temp->next)
// 		temp = temp->next;
// 	new->prev = temp;
// 	temp->next = new;
// 	new->num_redirections = 0;
// 	while (lexer && lexer->token != PIPE)
// 	{
// 		if (lexer->token)
// 		{
// 			ft_forwardtwo(mini, new, lexer);
// 			lexer = lexer->next;
// 			continue ;
// 		}
// 		else
// 			lexer = lexer->next;
// 	}
// 	ft_init_parser_matrix(new, save);
// }

// void	ft_parser_pushback(t_global *mini, t_lexer *lexer)
// {
// 	if (mini->p_head)
// 		ft_parser_lastnode(mini, lexer);
// 	else
// 		ft_parser_firstnode(mini, lexer);
// }

// void	ft_init_parser(t_global *mini)
// {
// 	t_simple_cmds	*temp;
// 	t_lexer			*lexer;

// 	if (!mini->head)
// 		return ;
// 	lexer = mini->head;
// 	while (lexer)
// 	{
// 		ft_parser_pushback(mini, lexer);
// 		while (lexer && lexer->token != PIPE)
// 			lexer = lexer->next;
// 		if (lexer)
// 			lexer = lexer->next;
// 	}
// }

void	ft_parser_firstnode(t_global *mini, t_lexer *lexer)
{
	t_simple_cmds	*new;
	t_lexer			*save;
	int				i;

	ft_skipinit(&new);
	new->prev = NULL;
	save = lexer;
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token)
		{
			ft_parser_lexpush_back(new, lexer->str);
			ft_parser_lexpush_back(new, lexer->next->str);
			i = lexer->i;
			lexer = lexer->next->next;
			ft_delete_node(i, mini);
			ft_delete_node(i, mini);
			new->num_redirections++;
			continue ;
		}
		lexer = lexer->next;
	}
	mini->p_head = new;
}

void	ft_skipinit(t_simple_cmds **new)
{
	(*new) = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
	(*new)->next = NULL;
	(*new)->num_redirections = 0;
	(*new)->hd_file_name = NULL;
	(*new)->str = NULL;
	(*new)->redirections = NULL;
}


void	ft_parser_lastnode(t_global *mini, t_lexer *lexer)
{
	t_simple_cmds	*new;
	t_simple_cmds	*temp;
	int				i;

	ft_skipinit(&new);
	temp = mini->p_head;
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token)
		{
			ft_parser_lexpush_back(new, lexer->str);
			ft_parser_lexpush_back(new, lexer->next->str);
			i = lexer->i;
			lexer = lexer->next->next;
			ft_delete_node(i, mini);
			ft_delete_node(i, mini);
			new->num_redirections++;
			continue ;
		}
		lexer = lexer->next;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

void	ft_parser_pushback(t_global *mini, t_lexer *lexer)
{
	if (!mini->p_head)
		ft_parser_firstnode(mini, lexer);
	else
		ft_parser_lastnode(mini, lexer);
}
