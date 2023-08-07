/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:37:06 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/06 18:21:04 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expand_count(char *line, char **ev)
{
	int		i;
	int		size;
	char	*to_expand;
	char	*to_search;

	i = 0;
	to_search = ft_strdup(line);
	free(line);
	line = ft_strjoin(to_search, "=");
	free(to_search);
	while (ev[i])
	{
		to_expand = ft_strnstr(ev[i], line, ft_strlen(line) + 1);
		if (to_expand)
		{
			size = ft_strlen(to_expand + ft_strlen(line));
			free(line);
			return (size);
		}
		i++;
	}
	free(line);
	return (0);
}

int	ft_num(int num)
{
	int		size;
	long	nbr;

	size = 0;
	if (!num)
		return (1);
	nbr = num;
	if (nbr < 0)
	{
		size++;
		nbr = -nbr;
	}
	while (nbr)
	{
		size++;
		nbr = nbr / 10;
	}
	return (size);
}

void	ft_set_when_nvalid(char *line, int *i, int *size)
{
	if (!ft_is_valid(line[*i + 1]) && line[*i + 1] != '?')
	{
		while (line[*i] && line[++*i] != '$')
			size++;
		if (line[*i] == '$' && !line[*i + 1])
			size++;
	}
}

void	ft_set_when_valid(char *line, int *i, int *j, int *size)
{
	if (line[*i + 1] == '?')
	{
		*i = *i + 1;
		*size += ft_num(g_global.error_num);
	}
	else
	{
		*j = ++*i;
		while ((ft_is_valid(line[*i]) || ft_isalnum(line[*i])) && \
		line[*i])
			*i = *i + 1;
		*size += ft_expand_count(ft_substr(line, *j, *i - *j), g_global.env);
	}
}

int	ft_count(char *line, char **ev)
{
	int	i;
	int	size;
	int	j;

	i = 0;
	size = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (!ft_is_valid(line[i + 1]) && line[i + 1] != '?')
			{
				ft_set_when_nvalid(line, &i, &size);
				continue ;
			}
			else
			{
				ft_set_when_valid(line, &i, &j, &size);
				continue ;
			}
		}
		size++;
		i++;
	}
	return (size);
}
