/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:02:01 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/03 18:46:43 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
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
	int				is_quote;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

// typedef struct s_simple_cmds
// {
// 	char					**str;
// 	int						(*builtin)(t_tools *, struct s_simple_cmds *);
// 	int						num_redirections;
// 	char					*hd_file_name;
// 	t_lexer					*redirections;
// 	struct s_simple_cmds	*next;
// 	struct s_simple_cmds	*prev;
// }	t_simple_cmds;
typedef struct s_global
{
	t_lexer	*head;
}t_global;

typedef struct s_globals
{
	int		error_num;
}t_globals;

t_globals	g_global;

void	ft_init_lexer(t_global *mini, char *line);
void	display(t_global *mini);
void	free_tokens(char **tokens);
void	ft_deallocate_lexer(t_global *mini);
char	**ft_split_tok(char *str, char *del);
int		ft_check_tokens(t_global *mini);
int		ft_check_error(t_global *mini);