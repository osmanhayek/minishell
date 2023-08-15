/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:25:30 by baer              #+#    #+#             */
/*   Updated: 2023/08/15 21:09:33 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_set_export_according_to_env(t_global *mini)
{
	int	size;
	int	i;

	size = 0;
	while (mini->env[size])
		size++;
	free_tokens(mini->export);
	mini->export = (char **)malloc(sizeof(char *) * size + 1);
	i = 0;
	while (mini->env[i])
	{
		mini->export[i] = ft_strdup(mini->env[i]);
		i++;
	}
	mini->export[i] = NULL;
}

int	no_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
			return (0);
		i++;
	}
	return (1);
}

void	ft_delete_oldpwd(t_global *mini)
{
	char	**env;
	int		i;
	int		j;

	env = ft_setenv(mini->env);
	free_tokens(mini->env);
	i = 0;
	while (env[i])
		i++;
	mini->env = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7))
			mini->env[j++] = ft_strdup(env[i]);
		i++;
	}
	mini->env[j] = NULL;
	free_tokens(env);
}

int	ft_cdskip(t_global *mini, t_simple_cmds *parser, int ret)
{
	if (!parser->str[1] || !parser->str[1][0])
		ret = ft_setdir(mini, "HOME=");
	else if (!ft_strcmp(parser->str[1], "-"))
		ret = ft_setdir(mini, "OLDPWD=");
	else if (!ft_strcmp(parser->str[1], "~"))
		ret = ft_setdir(mini, "HOME=");
	else
	{
		ret = chdir(parser->str[1]);
		if (ret)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(parser->str[1], 2);
			perror(" ");
		}
	}
	if (ret)
	{
		g_global.error_num = 1;
		return (1);
	}
	if (no_pwd(mini->env))
	{
		ft_delete_oldpwd(mini);
		return (0);
	}
	ft_set_pwd(mini, parser->str[1]);
	ft_set_export_according_to_env(mini);
	return (0);
}

int	ft_cd(t_global *mini, t_simple_cmds *parser)
{
	int	ret;

	ret = 0;
	if (parser->str[1] && parser->str[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	return (ft_cdskip(mini, parser, ret));
}
