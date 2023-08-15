/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:12:03 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/15 22:49:20 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_replace_dollar(char **exp, int *j, char *str, char **ev)
{
	int		c;
	int		i;
	char	*path;
	char	*save;

	c = 1;
	i = 0;
	if (str[i + 1] == '?')
		return (ft_handle_qmark(exp, j));
	while (str[c] && ft_allvalid(str[c]))
		c++;
	save = ft_substr(str, 1, c - 1);
	path = ft_pathof(save, ev);
	if (path[0])
	{
		ft_stradd(exp, path + ft_strlen(save) + 1, *j);
		*j += ft_strlen(path + ft_strlen(save) + 1);
	}
	free(path);
	free(save);
	return (c - 1);
}

int	ft_check_flag_status(char *str, int i, int *flag)
{
	if (*flag == 2 && str[i] == '\"')
	{
		*flag = 0;
		return (0);
	}
	else if (*flag == 1 && str[i] == '\'')
	{
		*flag = 0;
		return (0);
	}
	else if (*flag == 0 && str[i] == '\'')
	{
		*flag = 1;
		return (0);
	}
	else if (*flag == 0 && str[i] == '\"')
	{
		*flag = 2;
		return (0);
	}
	return (1);
}

int	ft_ifvalid(char c)
{
	if (c == '_' || ft_isalpha(c) || c == '?')
		return (1);
	return (0);
}

void	ft_expandmainly(char **exp, char *str, char **ev)
{
	int	i;
	int	j;
	int	flag;

	ft_quicklyinitialize(&i, &flag, &j);
	while (str[++i])
	{
		if (str[i] == '$' && flag != 1 && ft_ifvalid(str[i + 1]))
			i += ft_replace_dollar(exp, &j, str + i, ev);
		else if (ft_check_flag_status(str, i, &flag))
		{
			(*exp)[j] = str[i];
			j++;
		}
		(*exp)[j] = '\0';
	}
	(*exp)[j] = str[i];
}

int	ft_add_dollar(char *str, char **ev)
{
	int		c;
	int		j;
	char	*path;
	char	*save;
	char	*bruh;

	c = 1;
	if (str[1] == '?')
	{
		save = ft_itoa(g_global.error_num);
		j = ft_strlen(save);
		free(save);
		return (j);
	}
	while (str[c] && ft_allvalid(str[c]))
		c++;
	save = ft_substr(str, 1, c - 1);
	bruh = ft_pathof(save, ev);
	path = ft_strdup(bruh);
	j = ft_strlen(path + ft_strlen(save) + 1);
	free(save);
	free(path);
	free(bruh);
	return (j);
}
