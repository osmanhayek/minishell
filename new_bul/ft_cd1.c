/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 06:16:06 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/12 11:32:55 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_path(char **ev, char *str)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		if (!ft_strncmp(ev[i], str, ft_strlen(str)))
			return (ev[i] + ft_strlen(str));
		i++;
	}
	return (NULL);
}

int	ft_setdir(t_global *mini, char *str)
{
	char	*path;
	int		ret;

	path = ft_find_path(mini->env, str);
	ret = chdir(path);
	if (ret)
	{
		while (*str && *str != '=')
			write(2, str++, 1);
		ft_putendl_fd(" not set", 2);
	}
	return (ret);
}

void	ft_set_one_n(t_global *mini, char **tmp, char **oldpwd, char *pwd)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		if (mini->env[i] && !ft_strncmp(mini->env[i], "PWD=", 4))
		{
			*tmp = ft_strjoin("PWD=", pwd);
			*oldpwd = ft_strdup(mini->env[i] + 4);
			free(mini->env[i]);
			mini->env[i] = *tmp;
		}
		else if (mini->env[i] && *oldpwd && !ft_strncmp(mini->env[i], \
		"OLDPWD=", 7))
		{
			*tmp = ft_strjoin("OLDPWD=", *oldpwd);
			free(mini->env[i]);
			mini->env[i] = *tmp;
		}
		i++;
	}
}

void	ft_set_pwd(t_global *mini, char *str)
{
	char	*tmp;
	char	pwdsave[1024];
	char	*pwd;
	char	*oldpwd;

	getcwd(pwdsave, sizeof(pwdsave));
	pwd = ft_strdup(pwdsave);
	oldpwd = NULL;
	ft_set_one_n(mini, &tmp, &oldpwd, pwd);
	free(oldpwd);
	free(pwd);
	(void)str;
}
