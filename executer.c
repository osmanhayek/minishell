/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 23:04:41 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/15 22:47:28 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_directory(char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (!dir)
		return (0);
	closedir(dir);
	return (1);
}

int	ft_check_slash(char *str)
{
	if (access(str, F_OK))
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		return (127);
	}
	if (ft_check_directory(str))
	{
		ft_putstr_fd("minishell: Is a directory\n", 2);
		return (126);
	}
	return (0);
}

void	ft_set_when_no_red(t_global *mini, int has_slash)
{
	int	status;

	if (!has_slash && !mini->p_head->builtin && mini->p_head->str[0][0])
		if (ft_check_replace(mini->p_head, mini) == -1)
			exit(127);
	if (has_slash)
	{
		status = ft_check_slash(mini->p_head->str[0]);
		if (status)
			exit(status);
	}
	if (mini->p_head->builtin)
		exit(mini->p_head->builtin(mini, mini->p_head));
	if (mini->p_head->str[0][0] == '\0')
	{
		ft_putstr_fd("bash: Command not found\n", 2);
		exit(127);
	}
	execve(mini->p_head->str[0], mini->p_head->str, mini->env);
	perror("bash: ");
	if (errno == 13)
		exit(126);
	exit(1);
}

void	ft_set_has(t_global *mini, int *has_slash, int *is_spec)
{
	*has_slash = ft_search_slash(mini->p_head->str[0]);
	*is_spec = ft_search_builtin(mini->p_head->str[0]);
	g_global.test2 = 1;
}

void	ft_wait_single(pid_t pid, int *wait_status)
{
	waitpid(pid, wait_status, 0);
	if (WIFEXITED(*wait_status))
		g_global.error_num = WEXITSTATUS(*wait_status);
	else if (WIFSIGNALED(*wait_status))
		g_global.error_num = 128 + WTERMSIG(*wait_status);
}

void	ft_single_command(t_global *mini)
{
	int		has_slash;
	int		is_spec;
	int		wait_status;
	pid_t	pid;

	ft_set_has(mini, &has_slash, &is_spec);
	if (has_slash || !is_spec)
	{
		pid = fork();
		if (pid == 0)
		{
			if (mini->p_head->redirections)
			{
				ft_check_red(mini, has_slash);
				if (g_global.in_her == -1)
					exit(1);
			}
			else
				ft_set_when_no_red(mini, has_slash);
		}
		ft_wait_single(pid, &wait_status);
	}
	else
		ft_parent(mini);
}

void	ft_executer(t_global *mini)
{
	int	size;

	size = ft_size_cmds(mini);
	if (size == 0)
		return ;
	else if (size == 1)
		ft_single_command(mini);
	else
		ft_multiple_command(mini);
}
