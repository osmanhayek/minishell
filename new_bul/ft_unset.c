/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:25:37 by baer              #+#    #+#             */
/*   Updated: 2023/08/12 11:34:59 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset_errors(t_global *mini, t_simple_cmds *parser)
{
	int	i;

	(void)mini;
	i = 0;
	if (!parser->str[0])
	{
		write(2, "minishell: unset: not enough arguments\n", 39);
		return (1);
	}
	if (!parser->str[1])
	{
		write(2, "minishell: unset: not enough arguments\n", 39);
		return (1);
	}
	while (parser->str[i])
	{
		if (parser->str[1][i++] == '/')
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(parser->str[1], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (EXIT_FAILURE);
		}
	}
	return (0);
}

char	**ft_setenvminus(char **ev, int j)
{
	int		i;
	int		k;
	int		c;
	char	**arr;

	i = 0;
	while (ev[i])
		i++;
	arr = malloc(sizeof(char *) * (--i + 1));
	arr[i] = NULL;
	k = 0;
	c = 0;
	while (k < i)
	{
		if (c != j)
			arr[k++] = ft_strdup(ev[c++]);
		else
			c++;
	}
	return (arr);
}

void	ft_delvar(t_global *mini, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (mini->env[j])
	{
		if (!ft_strncmp(mini->env[j], str, ft_ifequalexists(str) + 1))
			mini->env = ft_setenvminus(mini->env, j--);
		j++;
	}
	j = 0;
	while (mini->export[j])
	{
		if (!ft_strncmp(mini->export[j], str, ft_ifequalexists(str) + 1))
			mini->export = ft_setenvminus(mini->export, j--);
		j++;
	}
}

int	ft_unset(t_global *mini, t_simple_cmds *parser)
{
	int	i;

	i = 0;
	if (ft_unset_errors(mini, parser))
		return (1);
	while (parser->str[i])
		ft_delvar(mini, parser->str[i++]);
	return (0);
}
