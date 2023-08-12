/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:02:01 by ohayek            #+#    #+#             */
/*   Updated: 2023/08/12 12:45:13 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include "libft/libft.h"
#include <fcntl.h>

typedef enum e_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS
}t_tokens;

typedef struct s_proc
{
	int		fd[2];
	pid_t	pid;
}t_proc;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				is_quote;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_global
{
	t_lexer					*head;
	struct s_simple_cmds	*p_head;
	char					**env;
	char					**export;
}t_global;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_global *, struct s_simple_cmds *);
	int						num_redirections;
	int						in_her;
	char					*hd_file_name;
	t_proc					prcs;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

typedef struct s_globals
{
	int		a;
	int		error_num;
	int		in_her;
	int		in_red;
	int		test1;
	int		out_red;
	int		test2;
	char	**env;
}t_globals;

t_globals	g_global;

void	ft_init_lexer(t_global *mini, char *line);
void	free_tokens(char **tokens);
void	ft_deallocate_lexer(t_global *mini);
void	ft_parser_lexpush_back(t_simple_cmds *temp, char *str);
void	ft_parser_lexlast_node(t_simple_cmds *temp, char *str);
void	ft_parser_lexfirst_node(t_simple_cmds *temp, char *str);
void	ft_init_parser(t_global *mini);
void	ft_init_matrix(t_global *mini);
void	ft_delete_node(int index, t_global *mini);
void	ft_skipinit(t_simple_cmds **new, int flag);
void	ft_parser_pushback(t_global *mini, t_lexer *lexer);
void	ft_parent(t_global *mini);
void	ft_check_delete(t_global *mini);
void	ft_expand(t_global *mini);
void	ft_deallocate_all(t_global *mini);
void	ft_init_builtin(t_global *mini);
void	ft_freearr(char ***str);
void	ft_executer(t_global *mini);
void	ft_multiple_command(t_global *mini);
void	ft_set_global(t_global *mini);
void	ft_set_pipes(t_global *mini, t_simple_cmds *temp, int i);
void	ft_wait_prcs(t_global *mini, int *status);
void	close_pipes(t_global *mini, int current);
void	ft_set_heredoc(t_lexer *redirection);
void	set_heredoc_for_multi(t_global *mini);
void	ft_set_pwd(t_global *mini, char *str);;
void	ft_handler(int sig);
void	ft_spik(char ***tokens, int *index, int *token_length, char **str);
char	*ft_addquotes(char *str);
void	ft_check_red(t_global *mini, int has_slash);
char	**ft_setenv(char **ev);
char	**ft_added(char **ev, char *str);
char	**ft_split_tok(char *str, char *del);
char	*ft_strncpy(char *dest, char *src, int n);
int		ft_check_tokens(t_global *mini);
int		ft_checkvalid(char *str);
int		ft_check_valid_identifier(char c);
int		ft_exporterror(char *c);
int		count_tokens(char *str, char *del);
char	**ft_setenvplus(char **ev);
int		ft_search_builtin(char *str);
int		ft_setdir(t_global *mini, char *str);
int		ft_printexport(char **str);
int		ft_is_valid(char c);
int		ft_checkvalid(char *str);
int		ft_check_error(t_global *mini);
int		ft_find_token(char *str);
int		ft_cd(t_global *mini, t_simple_cmds *parser);
int		ft_echo(t_global *mini, t_simple_cmds *parser);
int		ft_pwd(t_global *mini, struct s_simple_cmds *head);
int		ft_export(t_global *mini, t_simple_cmds *parser);
int		ft_unset(t_global *mini, t_simple_cmds *parser);
int		ft_env(t_global *mini, struct s_simple_cmds *head);
int		ft_exit(t_global *mini, struct s_simple_cmds *parser);
int		ft_strcmp(char *s1, char *s2);
int		ft_size_cmds(t_global *mini);
int		ft_search_slash(char *str);
int		ft_her(t_lexer *temp, char *file);
int		ft_open_pipes(t_global *mini);
int		ft_set_red(t_lexer *redirection);
int		ft_check_replace(t_simple_cmds *temp, t_global *mini);
int		ft_check_last(t_lexer *redirection);
int		ft_ifequalexists(char *str);
int		ft_replace_dollar(char **exp, int *j, char *str, char **ev);
int		ft_check_flag_status(char *str, int i, int *flag);
int		ft_ifvalid(char c);
int		is_delimiter(char c, char *del);
void	ft_expandmainly(char **exp, char *str, char **ev);
int		ft_add_dollar(char *str, char **ev);
int		ft_handle_qmark(char **exp, int *j);
int		ft_replace_dollar(char **exp, int *j, char *str, char **ev);
int		ft_check_flag_status(char *str, int i, int *flag);
void	ft_stradd(char **exp, char *str, int j);
int		ft_allvalid(char c);
char	*ft_pathof(char *str, char **ev);
void	ft_quicklyinitialize(int *i, int *flag, int *j);
char	**ft_split_tok(char *str, char *del);
void	ft_spik5(int *a, int *b);
void	ft_spik3(int *token_length, char **str);
void	ft_spik4(char ***tokens, int *index, int *token_length, char **str);
void	ft_spik2(char ***tokens, int *index, int *token_length, char **str);
void	ft_spik(char ***tokens, int *index, int *token_length, char **str);
void	free_tokens(char **tokens);
