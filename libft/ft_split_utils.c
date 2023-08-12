/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:29:14 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/12 10:29:59 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ifin(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*move(char *prevnext, char *c)
{
	prevnext++;
	while (!ft_ifin(c, *prevnext) && *prevnext != '\0')
		prevnext++;
	return (prevnext);
}

char	*pass(char *prevnext, char *c)
{
	while (ft_ifin(c, *prevnext) && *prevnext != '\0')
		prevnext++;
	return (prevnext);
}

void	ft_quotemove(char **next)
{
	if (*(*next - 1) == '"')
	{
		while ((*(*next) != '"' || *(*next + 1) == '\'') && *(*next))
			(*next)++;
	}
	else if (*(*next - 1) == '\'')
	{
		while ((*(*next) != '\'' || *(*next + 1) == '"') && *(*next))
			(*next)++;
	}
}

int	count_split(char *act, char *c, int count)
{
	while (1)
	{
		act = pass(act, c);
		if (!(*act))
			break ;
		else
			count++;
		if (*act == '"' || *act == '\'')
		{
			act++;
			ft_quotemove(&act);
			act++;
		}
		else
			act = move(act, c);
	}
	return (count + 1);
}
