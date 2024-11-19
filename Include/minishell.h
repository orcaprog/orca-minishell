/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:31:44 by abouassi          #+#    #+#             */
/*   Updated: 2023/05/20 23:46:27 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>

enum	e_token
{
	WORD = -1,
	WHITE_SPACE = 0,
	QOUTE = 1,
	DOUBLE_QUOTE = 2,
	ENV = 3,
	PIPE_LINE = 4,
	IN_RED = 5,
	OUT_RED = 6,
	MORE_RED = 7,
	LESS_RED = 8,
	LIMIT = 10,
	FILE_NAME = 11,
	TEMP = 12,
	IGNOR = 13,
	IGNO = 14,
};

enum						e_redirect
{
	HEREDOC = 7,
	LESS = 8,
	GREAT = 9,
	EXPAND = 10
};

enum						e_state
{
	IN_DQUOTE = 2,
	IN_QUOTE = 1,
	GENERAL = 0,
};
typedef struct pipe_ft		t_cmd_pipe;
typedef struct s_elem		t_elem;
typedef struct s_redir_elem	t_redir_elem;
typedef union u_union		t_union;
typedef struct s_ast_node	t_ast_node;
typedef struct s_redir_list	t_redir_list;

typedef struct s_elm
{
	char					*content;
	int						len;
	enum e_token			type;
	enum e_token			tmp;
	enum e_state			state;
	struct s_elm			*next;
	struct s_elm			*prev;
}							t_elm;

typedef struct l_list
{
	int						size;
	t_elm					*head;
	t_elm					*tail;
}							t_list;

typedef struct s_redirect
{
	int						my_redirect;
	char					*here_lim;
	int						here_doc_expand;
	char					*filename;
	struct s_redirect		*next;
}							t_redirect;

typedef struct s_data
{
	int						glob_exit;
	t_list					*lex;
	t_cmd_pipe				*parcecmd;
	t_list					*listt;
}							t_data;

t_data						g_data;

typedef struct s_cmd
{
	char					*cmd;
	char					**args;
	int						here_doc;
	int						out_fd;
	int						in_fd;
	int						cheak_in;
	t_redirect				*list_of_red;
	int						in_of_next;
	int						cheak;
	int						errr;
	struct s_cmd			*prev;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_redir
{
	char					*arg;
	enum e_token			type;
	int						state;
	struct s_redir			*next;
}							t_redir;

typedef struct s_env
{
	int						cheak;
	char					*key;
	char					*value;
	char					*content;
	struct s_env			*next;
}							t_env;

typedef struct s_val
{
	int						last_fd;
	char					*small;
	int						fd;
	int						fd_p[2];
	char					**join;
	char					**help;
	int						i;
	int						j;
	int						k;
}							t_val;

typedef struct s_global
{
	t_cmd					*all_cmd;
	t_env					*env_list;
}							t_global;

typedef struct pipe_ft
{
	char					**args;
	t_redir					*reder;
	struct pipe_ft			*next;
}							t_cmd_pipe;

void						siiig(int sig);
void						wait_signal(int pid);
void						ft_dup_io1(t_cmd *cmds, int *fd);
void						ft_dup_io2(t_cmd *cmds, int *fd, int last_fd);
void						get_herdoc(t_redirect *red, t_env *env,
								int *fd_pipe);
void						free_cmds(t_cmd *ptr);
void						cmd_env(t_env *env, int fd);
char						*cheak_expand(t_env *env, t_elm *elem);
void						p_error(char *str);
t_env						*ft_lstnew_mini(char *content);
void						ft_lstadd_back_mini(t_env **lst, t_env *new);
char						*ft_strchr(const char *str, int c);
char						**var_val(char *env);
void						del_node(t_env **head, char *key);
int							cmd_unset(char **arg, t_env **env);
void						cmd_export(t_env **env, char **arg, int fd);
void						cmd_cd(char **path, t_env **env, int fd);
char						*cmd_pwd(int fd, int k);
int							check_key(char *env);
void						cmd_exit(char **str);
void						cmd_echo(char **cmd, int fd);
char						*get_env(t_env *env, char *s, char *s2, int cheack);
void						print_order(t_env *env, t_val *val, t_env *ptr2,
								t_env *ptr3);
int							ft_lstsize_mini(t_cmd *lst);
void						if_unset_pwd(t_env **env);
int							ch_join(char *str);
int							her_doc(t_redirect *red, t_env *env);
int							set_her_doc(t_cmd *cmds, t_env *env);
char						*my_path(char *cmd1, char **env);
void						free_all(char **str, char *str2);
void						check_error2(char *str);
void						ft_puterr(char *str);
void						check_error(char *str, int n);
int							set_red(t_cmd *cmd);
char						*cheak_key(t_env *env, char *key, int k);
void						cmd_excution(t_global *all, char **env);
int							cheackis_buil(char *cmd);
int							exucute_builtine(t_global *all, t_cmd *cmds);
void						execution_mini(t_global *all, char **env);
void						handle_sig(int signum);
char						*get_env_expand(t_env *env, char *s);
void						expan_var(t_elm **data, t_env *env);
void						parse_cmd(t_elm **ptr, t_cmd **fcmd);
void						free_lexr_n2(t_elm *ptr);
void						free_arg2(t_cmd_pipe *ptr1);
int							is_redir(enum e_token type);
t_redir						*red_list(t_elm *ptr);
t_redirect					*my_red(t_redir *red);
char						*parse_quotes(t_elm **ptr, enum e_token type);
char						*parse_quotes2(t_elm *ptr1, enum e_token type,
								enum e_token type2);
void						fille_cmd(t_cmd **fcmd, t_cmd_pipe *full_cmd);
char						**fill_arg(char **src);
int							count_args(t_elm *elem);
int							lunch_shell(char *line, t_global *all);
void						parse1(t_elm *ptr, t_global *all);
t_elm						*check_unclosed_quotes(t_elm **ptr,
								enum e_token type);
t_elm						*skip_spaces(t_elm *ptr);
int							pipe_error(t_elm *ptr);
int							redir_error(t_elm *ptr);
void						lstadd_back_red2(t_redirect **lst, t_redirect *new);
t_cmd_pipe					*cmd_new(void);
t_cmd						*lstnew_cmd(t_cmd_pipe *cmds);
void						lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void						ft_lstadd_back1(t_cmd_pipe **lst,
								t_cmd_pipe *newnode);
void						lstadd_back_red(t_redir **lst, t_redir *new);
t_redir						*lstnew_red(t_elm *ptr, int type, int stat);
t_redirect					*new_nodered(int red, char *lim, char *file,
								int her);
void						lstadd_back_red2(t_redirect **lst, t_redirect *new);
void						lstadd_back_red(t_redir **lst, t_redir *new);
char						**fill_arg(char **src);
void						free_lexer(t_elm *ptr);
int							check_operator(t_list *token, char *str, int i,
								enum e_state *state);
int							is_alpha(int c);
t_elm						*new_elem(char *content, int len, enum e_token type,
								enum e_state state);
int							ft_check_emp(t_list *list);
t_list						*in_list(void);
int							is_space(char c);
void						add_link(t_list *list, t_elm *new);
int							ft_word(t_list *token, char *str,
								enum e_state state);
void						quotes(t_list *token, char *str,
								enum e_state *state, int flag);
int							is_char(char c);
int							toke_init(t_list *token, char *line, int i,
								enum e_state *state);
t_list						*lexer(char *line);
int							get_env_var(t_list *tokens, char *str,
								enum e_state state);
int							env_white(t_list *token, char *str,
								enum e_state *state);
int							env_signe(t_list *token, char *str,
								enum e_state *state);
void						rl_replace_line(const char *text, int clear_undo);
int							set_doublquot(t_elm **data, enum e_token type,
								enum e_token type2, enum e_token type3);
void						lotof_quot(t_elm **elem, enum e_token type1,
								enum e_token type2, enum e_token type3);
void						to_word(t_elm **elem);
void						parse_red(t_elm *ptr1);
void						parse_word(t_elm **ptr, char **args, int *i);
void						expand_env_var(t_elm *ptr, t_env *env);
void						expand_quot(t_elm **data);
void						convert_to_word(t_elm **data);
void						expand_env(t_elm **data, t_env *env);
void						between_quot(t_elm *ptr);
#endif