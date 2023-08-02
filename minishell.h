/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:02:01 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/02 03:43:22 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef enum e_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS
}t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct	s_cmds
{
	char	**str;
	
}t_cmds;

typedef struct s_global
{
	t_lexer	*head;
}t_global;

void	ft_init_lexer(t_global *mini, char *line);
void	display(t_global *mini);
void	free_tokens(char **tokens);
char	**ft_split_tok(char *str, char *del);