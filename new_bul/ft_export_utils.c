/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:03:41 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/12 11:04:05 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_setenvplus(char **ev)
{
	int		i;
	char	**arr;

	i = 0;
	while (ev[i])
		i++;
	arr = malloc(sizeof(char *) * (++i + 1));
	arr[i] = NULL;
	i--;
	arr[i] = NULL;
	while (i--)
		arr[i] = ft_strdup(ev[i]);
	return (arr);
}

char	**ft_added(char **ev, char *str)
{
	char	**newev;
	int		i;

	i = 0;
	newev = ft_setenvplus(ev);
	while (newev[i])
		i++;
	newev[i] = ft_strdup(str);
	ft_freearr(&ev);
	return (newev);
}

int	ft_exporterror(char *c)
{
	ft_putstr_fd("minishell: export: ", 2);
	if (c)
	{
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(c, 2);
		ft_putstr_fd("\': is ", 2);
	}
	if (c[0])
		ft_putendl_fd("not a valid identifier", 2);
	else
		ft_putendl_fd("not valid in this context:", 2);
	return (1);
}

int	ft_check_valid_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~'
		|| c == '=' || c == '-' || c == '?' || c == '&' || c == '*');
}

int	ft_checkvalid(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (ft_exporterror(str));
	while (str[i] != '=' && str[i])
	{
		if (ft_check_valid_identifier(str[i]))
			return (ft_exporterror(str));
		i++;
	}
	return (0);
}
