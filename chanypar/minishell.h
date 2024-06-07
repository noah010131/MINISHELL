/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:20:33 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/07 16:22:40 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define WORD 9
# define PIPE_N 10
# define REDIR_IN 11
# define REDIR_OUT 12
# define HEREDOC_IN 13
# define REDIR_APP 14
# define SIN_QUOTE 20
# define DOUB_QUOTE 21
# define TOKEN_EX_STT 22

typedef struct s_cmds
{
	int				code_id;
	char			*name;
	struct s_cmds	*prev;
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_envp
{
	char			*name;
	char			*value;
	// Tableau de str contenant le nom et la valeur de chaque variable d'environnement
	struct s_envp	*next;
	struct s_envp	*prev;
}					t_envp;

typedef struct s_ori
{
	t_cmds			*cmds;
	t_envp			*envs;
	char			*request;
}					t_ori;

typedef struct s_file
{
	int					fd;
	char				file_name[30];
	struct s_file		*next;
	struct s_file		*prev;
}					t_file;

typedef struct s_pipe
{
	struct s_file	**file;
	struct s_cmds	**ret;
	struct s_envp	**lst;
}						t_pipe;


t_cmds				*ft_new_tcmd(char *str, int code);
int					code_attr(t_cmds **cmds);
int					ft_occur(char *str, char c);
char				*ft_strlimdup(char *str, int lim);
t_cmds				**ft_last_tcmd(char *str, int code, t_cmds **list_cmd);
int					non_print(char *str);
t_cmds				**split_token(char *request);
int					ft_pos_c(char *str, char c);
char				*end_quote(char *str, char c);
int					is_not_word(char *str);
int					syn_err(char *str);
int					open_quote(char *str);
int					code_lex(char *str);
int					is_not_word(char *str);
int					meta_type(char *str);
int					type_quote(char *str);
int					ft_tablen(char **env);
t_envp				**add_envplast(t_envp **ret, char *str);
void				*free_envp(t_envp **lst);
t_envp				**lst_env(char **env);
int					is_lim_exp(char c);
t_envp				*env_match(char *str, t_envp **lst);
int					expanding(t_cmds **cmds, t_envp **lst);
int					nb_expand(t_cmds *cmd);
int					exp_exception(char *str);
int					replace_exp(t_cmds *cmd, t_envp **lst);
char				*new_expanded(char *str, char *ptr, t_envp *match);
char				*nomatch(char *ptr, char *str);
void				reset_sp_tok(int *i, int *j);
int					skip_spcaes(int *i, char *request);
int					n_end_quote(char *str, int i, int j);
int					ft_isspace(char c);
int					go_last_lex(char *str, int i, int j);
void				init_0(int *i, int *j);
int					interpret(char *str, char *ptr);
void				free_tcmd(t_cmds **cmds);
t_cmds				**pptreatment(t_cmds **cmds);
int					replace_quote(t_cmds *cmds);
int					update_env(t_envp **lst, char *key, char *n_value);
int					ft_cd(t_cmds *cmd, t_envp **lst);
int					ft_echo(t_cmds *cmd);
int					check_builtins(t_cmds **ret, t_envp **lst);
int					builtins_checker(t_cmds *current);
t_cmds				*find_name(t_cmds *current, char name);
void				execute_command(int i, t_cmds *cmds, t_envp **lst);
int					redirec_main(t_cmds **ret, t_file **file, t_envp **lst);
int					f_open(char *str, t_file **file);
FILE				*f_open2(char *str, t_file **file, int redir);
int					f_close(int fd, t_file **file);
int					f_close2(int fd, t_file **file, FILE *f);
int					ft_new_tfile(t_file **file, char file_name[], int fd);
void				ft_del_tfile(t_file **file, int fd);
int					read_heredoc(char *end_str, t_file **file);
char				**making_cmds(t_cmds **ret);
char				*lst_to_char(t_cmds **ret);

#endif
