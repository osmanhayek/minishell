/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initbuiltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 04:16:29 by baer              #+#    #+#             */
/*   Updated: 2023/08/12 05:28:16 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	(*ft_controlbuiltin(char *str)) (t_global *mini, struct s_simple_cmds *temp)
{
	if (!str)
		return (NULL);
	if (!ft_strcmp(str, "export"))
		return (&ft_export);
	else if (!ft_strcmp(str, "echo"))
		return (&ft_echo);
	else if (!ft_strcmp(str, "env"))
		return (&ft_env);
	else if (!ft_strcmp(str, "exit"))
		return (&ft_exit);
	else if (!ft_strcmp(str, "cd"))
		return (&ft_cd);
	else if (!ft_strcmp(str, "pwd"))
		return (&ft_pwd);
	else if (!ft_strcmp(str, "unset"))
		return (&ft_unset);
	else
		return (NULL);
}

void	ft_init_builtin(t_global *mini)
{
	t_simple_cmds	*temp;

	temp = mini->p_head;
	while (temp)
	{
		temp->builtin = ft_controlbuiltin(temp->str[0]);
		temp = temp->next;
	}
}
