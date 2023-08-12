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

#include "libft.h"

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
		ft_quotemove(&next);
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

	arr = (char **)malloc(sizeof(char *) * count_split((char *)s, c, 0));
	if (!arr)
		return (0);
	arr[count_split((char *)s, c, 0) - 1] = NULL;
	i = 0;
	next = pass((char *)s, c);
	prev = next;
	while (i < count_split((char *)s, c, 0) - 1)
	{
		next = ft_skipnext(next, c);
		arr[i++] = ft_strndup(prev, next);
		next = pass(next, c);
		prev = next - 1;
		prev++;
	}
	return (arr);
}
