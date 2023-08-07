/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:02:01 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/07 05:23:45 by ohayek           ###   ########.fr       */
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

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_lexer *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

typedef struct s_global
{
	t_lexer			*head;
	t_simple_cmds	*p_head;
	char			**env;
}t_global;

typedef struct s_globals
{
	int		error_num;
	char	**env;
}t_globals;

t_globals	g_global;

void	ft_init_lexer(t_global *mini, char *line);
void	display(t_global *mini);
void	free_tokens(char **tokens);
void	ft_deallocate_lexer(t_global *mini);
void	ft_parser_lexpush_back(t_simple_cmds *temp, char *str);
void	ft_parser_lexlast_node(t_simple_cmds *temp, char *str);
void	ft_parser_lexfirst_node(t_simple_cmds *temp, char *str);
void	ft_init_parser(t_global *mini);
void	ft_init_matrix(t_global *mini);
void	ft_delete_node(int index, t_global *mini);
void	ft_skipinit(t_simple_cmds **new);
void	printmatrix(char **str);
void	ft_parser_pushback(t_global *mini, t_lexer *lexer);
void	ft_check_delete(t_global *mini);
void	ft_expand(t_global *mini);
char	**ft_split_tok(char *str, char *del);
int		ft_check_tokens(t_global *mini);
int		ft_is_valid(char c);
int		ft_count(char *line, char **ev);
int		ft_check_error(t_global *mini);
int		ft_lexer_size(t_lexer *list);
int		ft_find_token(char *str);
int		ft_cd(t_global *mini, t_simple_cmds parser);
int		ft_echo(t_global *mini, t_simple_cmds parser);
int		ft_pwd(t_global *mini, struct s_simple_cmds *head);
int		ft_export(t_global *mini, t_simple_cmds parser);
int		ft_unset(t_global *mini, t_simple_cmds parser);
int		ft_env(t_global *mini, struct s_simple_cmds *head);
int		ft_exit(t_global *mini, t_simple_cmds parser);