/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:15:24 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/12 04:58:58 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_search_slash(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	ft_search_builtin(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "export") || \
	!ft_strcmp(str, "exit") || !ft_strcmp(str, "unset"))
		return (1);
	return (0);
}

int	ft_wait(int fd, char **line)
{
	*line = readline("> ");
	if (g_global.a)
	{
		free(*line);
		close(fd);
		return (-1);
	}
	return (1);
}

int	ft_her(t_lexer *temp, char *file)
{
	int		fd;
	char	*delimiter;
	char	*line;
	char	*temp_str;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	delimiter = temp->next->str;
	g_global.test1 = 1;
	while (1)
	{
		if (ft_wait(fd, &line) == -1)
			return (-1);
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		free(line);
		temp_str = ft_strjoin(line, "\n");
		write(fd, temp_str, ft_strlen(temp_str));
		free(temp_str);
	}
	close(fd);
	return (open(file, O_RDONLY));
}
