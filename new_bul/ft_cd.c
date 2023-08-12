/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:25:30 by baer              #+#    #+#             */
/*   Updated: 2023/08/12 12:52:42 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_return_path(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
			return (i);
		i++;
	}
	return (i);
}

void	ft_set_export_according_to_env(t_global *mini)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	i = ft_return_path(mini->env, "PWD=");
	j = ft_return_path(mini->export, "PWD=");
	tmp = ft_strdup(mini->env[i]);
	free(mini->export[j]);
	mini->export[j] = tmp;
	i = ft_return_path(mini->env, "OLDPWD=");
	j = ft_return_path(mini->export, "OLDPWD=");
	tmp = ft_strdup(mini->env[i]);
	free(mini->export[j]);
	mini->export[j] = tmp;
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
	ft_set_pwd(mini, parser->str[1]);
	ft_set_export_according_to_env(mini);
	return (0);
}

int	ft_cd(t_global *mini, t_simple_cmds *parser)
{
	int	ret;

	ret = 0;
	return (ft_cdskip(mini, parser, ret));
}
