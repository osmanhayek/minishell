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
#include <string.h>

int is_space_or_tab(char c)
{
    return c == ' ' || c == '\t';
}

char **ft_split(const char *s, char *c)
{
    char **arr = NULL;
    int arr_size = 0;

    while (*s)
    {
        // Skip leading spaces and tabs
        while (is_space_or_tab(*s) && *s)
            s++;

        if (*s == '\0')
            break;

        const char *start = s;
        int in_quote = 0;

        while (*s)
        {
            if (*s == '"' || *s == '\'')
            {
                if (!in_quote)
                {
                    in_quote = *s;
                }
                else if (in_quote == *s)
                {
                    in_quote = 0;
                }
            }
            else if (in_quote)
            {
                // Inside a quote, just continue
            }
            else if (is_space_or_tab(*s) || strchr(c, *s))
            {
                break;  // Delimiter found
            }
            s++;
        }

        int length = s - start;
        if (length > 0)
        {
            arr = realloc(arr, (arr_size + 1) * sizeof(char *));
            arr[arr_size] = malloc(length + 1);
            strncpy(arr[arr_size], start, length);
            arr[arr_size][length] = '\0';
            arr_size++;
        }

        // Skip delimiters
        while (*s && (is_space_or_tab(*s) || strchr(c, *s)))
            s++;
    }

    arr = realloc(arr, (arr_size + 1) * sizeof(char *));
    arr[arr_size] = NULL;

    return arr;
}