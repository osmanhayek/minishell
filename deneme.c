/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deneme.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 22:46:05 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/06 14:48:47 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exit_status = 127;


int ft_is_valid(char c)
{
    if (c == '_' || ft_isalpha(c))
        return (1);
    return (0);
}

int ft_expand_count(char *line, char **ev)
{
    int     i;
    int     size;
    char    *to_expand;
    char    *to_search;

    i = 0;
    to_search = ft_strdup(line);
    free(line);
    line = ft_strjoin(to_search, "=");
    free(to_search);
    while (ev[i])
    {
        to_expand = ft_strnstr(ev[i], line, ft_strlen(line) + 1);
        if (to_expand)
        {
            size = ft_strlen(to_expand + ft_strlen(line));
            free(line);
            return (size);
        }
        i++;
    }
    free(line);
    return (0);
}

int ft_num(int num)
{
    int     size;
    long    nbr;
    size = 0;
    if (!num)
        return (1);
    nbr = num;
    if (nbr < 0)
    {
        size++;
        nbr = -nbr;
    }
    while (nbr)
    {
        size++;
        nbr = nbr / 10;
    }
    return (size);
}

int ft_count(char *line, char **ev)
{
    int i;
    int size;
    int j;

    i = 0;
    size = 0;
    while (line[i])
    {
        if (line[i] == '$')
        {
            if (!ft_is_valid(line[i + 1]) && line[i + 1] != '?')
            {
                while (line[i] && line[++i] != '$')
                {
                    size++;
                }
                if (line[i] == '$' && !line[i + 1])
                    size++;
                continue ;
            }
            else
            {
                if (line[i + 1] == '?')
                {
                    i += 2;
                    size += ft_num(exit_status);
                    continue ;
                }
                j = ++i;
                while ((ft_is_valid(line[i]) || ft_isalnum(line[i])) && line[i])
                    i++;
                size += ft_expand_count(ft_substr(line, j, i - j), ev);
                continue ;
            }
        }
        size++;
        i++;
    }
    return (size);
}

void    ft_replace_dolar(char *expanded_str, int *x, char *line, char **ev)
{
    int     i;
    char    *to_expand;
    char    *to_search;
    int     j;

    i = 0;
    to_search = ft_strdup(line);
    free(line);
    line = ft_strjoin(to_search, "=");
    free(to_search);
    while (ev[i])
    {
        to_expand = ft_strnstr(ev[i], line, ft_strlen(line) + 1);
        if (to_expand)
        {
            j = ft_strlen(line);
            while (ev[i][j])
            {
                expanded_str[*x] = ev[i][j];
                j++;
                *x = *x + 1;
            }
            free(line);
            return ;
        }
        i++;
    }
    free(line);
    return ;
} 


char    *ft_expand(char *line, char **ev)
{
    int     size;
    char    *expanded_str;
    int     i;
    int     j;
    int     x;
    
    size = ft_count(line, ev);
    expanded_str = (char *)malloc(sizeof(char) * size + 1);
    i = 0;
    x = 0;
    while (line[i])
    {
        if (line[i] == '$')
        {
            if (!ft_is_valid(line[i + 1]) && line[i + 1] != '?')
            {
                while (line[i] && line[++i] != '$')
                    expanded_str[x++] = line[i - 1];
                if (line[i] == '$' && !line[i + 1])
                    expanded_str[x++] = line[i];
                continue ;
            }
            else
            {
                if (line[i + 1] == '?')
                {
                    i += 2;
                    char    *num = ft_itoa(exit_status);
                    int c;
                    c = 0;
                    while (num[c])
                        expanded_str[x++] = num[c++];
                    continue ;
                }
                j = ++i;
                while ((ft_is_valid(line[i]) || ft_isalnum(line[i])) && line[i])
                    i++;
                ft_replace_dolar(expanded_str, &x, ft_substr(line, j, i - j), ev);
                continue ;
            }
        }
        expanded_str[x++] = line[i];
        i++;
    }
    expanded_str[x] = '\0';
    return (expanded_str);
}

int main(int ac, char **av, char **ev)
{
    char    *line;
    char    *new_line;
    line = readline("hello: ");
    new_line = ft_expand(line, ev);
    printf("%s", new_line);
    free(new_line);
}