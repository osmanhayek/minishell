/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:13:51 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/14 12:05:18 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_complete(char *str, char **paths)
{
	int		i;
	char	*complete;
	char	*to_check;

	i = 0;
	while (paths[i])
	{
		to_check = ft_strjoin(paths[i], "/");
		complete = ft_strjoin(to_check, str);
		if (!access(complete, F_OK))
		{
			free(to_check);
			return (complete);
		}
		free(to_check);
		free(complete);
		i++;
	}
	return (NULL);
}

char	*ft_abs_path(t_simple_cmds *temp, t_global *mini)
{
	char	*path_var;
	char	**paths;
	char	*complete_path;
	int		i;

	path_var = NULL;
	i = 0;
	while (mini->env[i])
	{
		if (!ft_strncmp(mini->env[i], "PATH=", 5))
		{
			path_var = ft_strdup(mini->env[i] + 5);
			break ;
		}
		i++;
	}
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ":");
	complete_path = ft_complete(temp->str[0], paths);
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (complete_path);
}

int	ft_check_replace(t_simple_cmds *temp, t_global *mini)
{
	char	*abs_path;

	abs_path = ft_abs_path(temp, mini);
	if (!abs_path)
	{
		ft_putstr_fd("bash: command not found\n", 2);
		return (-1);
	}
	free(temp->str[0]);
	temp->str[0] = ft_strdup(abs_path);
	return (1);
}

int	ft_check_last(t_lexer *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (!ft_strcmp(temp->str, "<<"))
			i = 1;
		else if (!ft_strcmp(temp->str, "<"))
			i = 0;
		temp = temp->next;
	}
	return (i);
}

void	ft_set_global(t_global *mini)
{
	if (g_global.out_red)
		dup2(g_global.out_red, 1);
	if (mini->p_head->builtin)
		exit(mini->p_head->builtin(mini, mini->p_head));
	if (!mini->p_head->str[0][0])
		exit(0);
	execve(mini->p_head->str[0], mini->p_head->str, mini->env);
	perror("bash: ");
	exit(1);
}
