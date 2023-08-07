/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:22:03 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/06 18:54:15 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_replace_dolar(char *expanded_str, int *x, char *line, char **ev)
{
	char	*to_expand;
	char	*to_search;
	int		i;
	int		j;

	to_search = ft_strdup(line);
	free(line);
	line = ft_strjoin(to_search, "=");
	free(to_search);
	i = 0;
	while (ev[i])
	{
		to_expand = ft_strnstr(ev[i], line, ft_strlen(line) + 1);
		if (to_expand)
		{
			j = ft_strlen(line);
			while (ev[i][j])
				expanded_str[(*x)++] = ev[i][j++];
			free(line);
			return ;
		}
		i++;
	}
	free(line);
}

void	ft_get_num(char *expanded_str, int *x)
{
	char	*num;
	int		c;

	num = ft_itoa(g_global.error_num);
	c = 0;
	while (num[c])
		expanded_str[(*x)++] = num[c++];
	free(num);
}

void	process_dollar(char *line, char *expanded_str, int *x, int *i)
{
	int		j;

	if (!ft_is_valid(line[*i + 1]) && line[*i + 1] != '?')
	{
		while (line[*i] && line[++(*i)] != '$')
			expanded_str[(*x)++] = line[*i - 1];
		if (line[*i] == '$' && !line[*i + 1])
			expanded_str[(*x)++] = line[*i];
	}
	else
	{
		if (line[*i + 1] == '?')
		{
			ft_get_num(expanded_str, x);
			*i += 2;
			return ;
		}
		j = ++(*i);
		while ((ft_is_valid(line[*i]) || ft_isalnum(line[*i])) && line[*i])
			(*i)++;
		ft_replace_dolar(expanded_str, x, ft_substr(line, j, *i - j), \
		g_global.env);
	}
}

char	*ft_expand_str(char *line, char **ev)
{
	int		size;
	char	*expanded_str;
	int		i;
	int		x;

	size = ft_count(line, ev);
	expanded_str = (char *)malloc(sizeof(char) * size + 1);
	i = 0;
	x = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			process_dollar(line, expanded_str, &x, &i);
			continue ;
		}
		expanded_str[x++] = line[i++];
	}
	expanded_str[x] = '\0';
	return (expanded_str);
}

void	ft_expand(t_global *mini)
{
	t_lexer	*temp;
	char	*to_expand;

	temp = mini->head;
	while (temp)
	{
		if (temp->is_quote % 2 == 0)
		{
			to_expand = ft_strtrim(temp->str, "\"");
			free(temp->str);
			temp->str = ft_expand_str(to_expand, mini->env);
			free(to_expand);
		}
		else
		{
			to_expand = ft_strtrim(temp->str, "'");
			free(temp->str);
			temp->str = ft_strdup(to_expand);
			free(to_expand);
		}
		temp = temp->next;
	}
	ft_check_delete(mini);
}
