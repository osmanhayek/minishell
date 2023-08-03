/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:03:39 by baer              #+#    #+#             */
/*   Updated: 2023/08/03 17:09:27 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	ft_ifin(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static	char	*move(char *prevnext, char *c)
{
	prevnext++;
	while (!ft_ifin(c, *prevnext) && *prevnext != '\0')
		prevnext++;
	return (prevnext);
}

static	char	*pass(char *prevnext, char *c)
{
	while (ft_ifin(c, *prevnext) && *prevnext != '\0')
		prevnext++;
	return (prevnext);
}

static	int	count_split(char *act, char *c)
{
	int	count;
	int	check;

	count = 0;
	check = 0;
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
			while (*act != '"' && *act != '\'' && *(act + 1))
				act++;
			act++;
		}
		else
			act = move(act, c);
	}
	return (count + 1);
}

static	char	*ft_strndup(char *prev, char *next)
{
	char	*arr;
	char	*temp;

	arr = (char *)malloc(sizeof(char) * (next - prev + 1));
	temp = arr;
	while (prev < next)
		*arr++ = *prev++;
	*arr = '\0';
	return (temp);
}

char	*ft_skipnext(char *next, char *c)
{
	if (*next == '"' || *next == '\'')
	{
		next++;
		while (*next != '"' && *next != '\'' && *(next + 1))
			next++;
		next++;
	}
	else
		next = move(next, c);
	return (next);
}

char	**ft_split(const char *s, char *c)
{
	char	**arr;
	char	*next;
	char	*prev;
	int		i;

	arr = (char **)malloc(sizeof(char *) * count_split((char *)s, c));
	if (!arr)
		return (0);
	arr[count_split((char *)s, c) - 1] = NULL;
	i = 0;
	next = pass((char *)s, c);
	prev = next;
	while (i < count_split((char *)s, c) - 1)
	{
		next = ft_skipnext(next, c);
		arr[i++] = ft_strndup(prev, next);
		next = pass(next, c);
		prev = next - 1;
		prev++;
	}
	return (arr);
}
