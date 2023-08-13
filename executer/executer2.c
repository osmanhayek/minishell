/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:14:35 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/12 23:24:40 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_set_heredoc(t_lexer *temp)
{
	while (temp)
	{
		if (!ft_strcmp(temp->str, "<<"))
		{
			if (g_global.in_her)
			{
				close(g_global.in_her);
				g_global.in_her = 0;
			}
			g_global.in_her = ft_her(temp, "single_temp.txt");
			if (g_global.in_her == -1)
				return ;
		}
		temp = temp->next->next;
	}
}

int	ft_set_less(t_lexer *temp)
{
	if (access(temp->next->str, F_OK))
	{
		ft_putstr_fd("bash: No such file or directory\n", 2);
		return (-1);
	}
	if (access(temp->next->str, R_OK))
	{
		ft_putstr_fd("bash: Premission denied\n", 2);
		return (-1);
	}
	if (g_global.in_red)
	{
		close(g_global.in_red);
		g_global.in_red = 0;
	}
	g_global.in_red = open(temp->next->str, O_RDONLY);
	return (0);
}

int	ft_set_append(t_lexer *temp)
{
	if (g_global.out_red)
	{
		close(g_global.out_red);
		g_global.out_red = 0;
	}
	if (ft_search_slash(temp->next->str))
	{
		if (!access(temp->next->str, F_OK))
		{
			if (access(temp->next->str, W_OK))
			{
				ft_putstr_fd("bash: Premision denied\n", 2);
				g_global.out_red = 0;
				return (-1);
			}
		}
	}
	g_global.out_red = open(temp->next->str, O_WRONLY | O_CREAT | O_APPEND, \
	0666);
	return (0);
}

int	ft_set_great(t_lexer *temp)
{
	if (g_global.out_red)
	{
		close(g_global.out_red);
		g_global.out_red = 0;
	}
	if (ft_search_slash(temp->next->str))
	{
		if (!access(temp->next->str, F_OK))
		{
			if (access(temp->next->str, W_OK))
			{
				ft_putstr_fd("bash: Premision denied\n", 2);
				g_global.out_red = 0;
				return (-1);
			}
		}
	}
	g_global.out_red = open(temp->next->str, O_WRONLY | O_CREAT | O_TRUNC, \
	0666);
	return (0);
}

int	ft_set_red(t_lexer *temp)
{
	while (temp)
	{
		if (!ft_strcmp(temp->str, "<"))
		{
			if (ft_set_less(temp))
				return (-1);
		}
		else if (!ft_strcmp(temp->str, ">>"))
		{
			if (ft_set_append(temp))
				return (-1);
		}
		else if (!ft_strcmp(temp->str, ">"))
		{
			if (ft_set_great(temp))
				return (-1);
		}
		temp = temp->next->next;
	}
	return (1);
}
