/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:17:41 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/13 01:34:24 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quicklyinitialize(int *i, int *flag, int *j)
{
	*i = -1;
	*flag = 0;
	*j = 0;
}

char	*ft_pathof(char *str, char **ev)
{
	char	*path;
	int		i;

	i = 0;
	path = ft_strjoin(str, "=");
	while (ev[i])
	{
		if (!ft_strncmp(ev[i], path, ft_strlen(path)))
		{
			free(path);
			return (ft_strdup(ev[i]));
		}
		i++;
	}
	free(path);
	return (ft_strdup(""));
}

int	ft_allvalid(char c)
{
	if (c == '_' || ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

void	ft_stradd(char **exp, char *str, int j)
{
	int	i;

	i = 0;
	while (str[i])
		(*exp)[j++] = str[i++];
	(*exp)[j] = '\0';
}
