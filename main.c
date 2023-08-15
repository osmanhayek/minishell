/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:52:25 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/14 02:02:18 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredoc(int sig)
{
	(void)sig;
	g_global.a = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
}

void	ft_handler(int sig)
{
	if (g_global.test1)
	{
		close_heredoc(sig);
		return ;
	}
	else
	{
		if (g_global.test2)
		{
			ft_putstr_fd("\n", 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			return ;
		}
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(1, "\033[A", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	minishell_loop(char *line,	t_global *mini)
{
	while (1)
	{
		g_global.test1 = 0;
		g_global.a = 0;
		g_global.test2 = 0;
		line = readline("minishell$ ");
		if (line == NULL)
			exit(1);
		if (line[0])
			add_history(line);
		ft_init_lexer(mini, line);
		if (ft_check_error(mini))
		{
			ft_deallocate_lexer(mini);
			free(line);
			continue ;
		}
		ft_expand(mini);
		ft_init_parser(mini);
		ft_executer(mini);
		ft_deallocate_all(mini);
		free(line);
	}
}

void	sigquit_handler(int sig)
{
	(void)sig;
	return ;
}

int	main(int ac, char **av, char **ev)
{
	char		*line;
	t_global	mini;

	if (ac > 1)
		exit(1);
	line = NULL;
	(void)av;
	mini.env = ft_setenv(ev);
	mini.export = ft_setenv(ev);
	mini.head = NULL;
	mini.p_head = NULL;
	g_global.env = ev;
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, ft_handler);
	minishell_loop(line, &mini);
	return (0);
}
