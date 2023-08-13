/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:25:28 by baer              #+#    #+#             */
/*   Updated: 2023/08/12 22:55:44 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checkexportexists(t_global *mini, char *str)
{
	int		i;
	char	*save;

	i = 0;
	save = ft_substr(str, 0, ft_ifequalexists(str));
	while (mini->export[i])
	{
		if (!ft_strncmp(mini->export[i], str, ft_ifequalexists(str) + 1) \
		|| !ft_strcmp(mini->export[i], save))
		{
			free(mini->export[i]);
			mini->export[i] = ft_addquotes(str);
			free(save);
			return (1);
		}
		i++;
	}
	free(save);
	return (0);
}

int	ft_checkexists(t_global *mini, char *str)
{
	int		j;

	j = 0;
	while (mini->env[j])
	{
		if (!ft_strncmp(mini->env[j], str, ft_ifequalexists(str) + 1))
		{
			free(mini->env[j]);
			mini->env[j] = ft_strdup(str);
			return (1);
		}
		j++;
	}
	j = 0;
	return (0);
}

int	ft_ifequalexists(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*ft_addquotes(char *str)
{
	char	*quoted;
	int		i;

	i = 0;
	if (ft_ifequalexists(str) == 0)
		return (ft_strdup(str));
	quoted = malloc(sizeof(char) * ft_strlen(str) + 3);
	while (*(str - 1) != '=')
		quoted[i++] = *str++;
	quoted[i++] = '\"';
	while (*str)
		quoted[i++] = *str++;
	quoted[i++] = '\"';
	quoted[i] = '\0';
	return (quoted);
}

int	ft_export(t_global *mini, t_simple_cmds *parser)
{
	int		i;
	int		flag;
	int		flag2;
	int		flag3;
	char	*quoted;

	i = 1;
	if (!parser->str[1])
		return (ft_printexport(mini->export));
	while (parser->str[i])
	{
		quoted = ft_addquotes(parser->str[i]);
		flag = ft_checkvalid(parser->str[i]);
		flag2 = ft_checkexists(mini, parser->str[i]);
		flag3 = ft_checkexportexists(mini, parser->str[i]);
		if (!flag && !flag2 && ft_ifequalexists(parser->str[i]))
			mini->env = ft_added(mini->env, parser->str[i]);
		if (!flag && !flag3)
			mini->export = ft_added(mini->export, quoted);
		i++;
		free(quoted);
	}
	if (flag)
		return (1);
	return (0);
}
