/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:20:09 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/12 12:46:24 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_spik2(char ***tokens, int *index, int *token_length, char **str)
{
	if (*token_length > 0)
	{
		(*tokens)[*index] = (char *)malloc(((*token_length) + 1) \
			* sizeof(char));
		ft_strncpy((*tokens)[*index], (*str) \
		- (*token_length), (*token_length));
		(*tokens)[*index][*token_length] = '\0';
		(*index)++;
	}
	(*tokens)[*index] = (char *)malloc(2 * sizeof(char));
	ft_strncpy((*tokens)[*index], (*str), 1);
	(*tokens)[*index][1] = '\0';
	(*index)++;
	(*str)++;
	(*token_length) = 0;
}

void	ft_spik4(char ***tokens, int *index, int *token_length, char **str)
{
	(*tokens)[*index] = (char *)malloc((*token_length + 1) * sizeof(char));
	ft_strncpy((*tokens)[*index], (*str) - *token_length, *token_length);
	(*tokens)[*index][*token_length] = '\0';
	(*index)++;
}

void	ft_spik3(int *token_length, char **str)
{
	(*token_length)++;
	(*str)++;
}

void	ft_spik5(int *a, int *b)
{
	*a = 0;
	*b = 0;
}

char	**ft_split_tok(char *str, char *del)
{
	int		token_count;
	char	**tokens;
	int		index;
	int		token_length;

	token_count = count_tokens(str, del);
	tokens = (char **)malloc((token_count + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	ft_spik5(&index, &token_length);
	while (*str)
	{
		if (ft_strncmp(str, ">>", 2) == 0 \
		|| ft_strncmp(str, "<<", 2) == 0)
			ft_spik(&tokens, &index, &token_length, &str);
		else if (is_delimiter(*str, del))
			ft_spik2(&tokens, &index, &token_length, &str);
		else
			ft_spik3(&token_length, &str);
	}
	if (token_length > 0)
		ft_spik4(&tokens, &index, &token_length, &str);
	tokens[index] = NULL;
	return (tokens);
}
