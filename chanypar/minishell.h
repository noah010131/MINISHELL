/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:20:33 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/27 13:41:26 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <termcap.h>

# define WORD 9
# define PIPE_N 10
# define REDIR_IN 11
# define REDIR_OUT 12
# define HEREDOC_IN 13
# define REDIR_APP 14
# define SIN_QUOTE 20
# define DOUB_QUOTE 21
# define TOKEN_EX_STT 22

# define TEMP ".temp_heredoc.txt"

typedef struct s_cmds
{
	int				flag;
	int				code_id;
	char			*name;
	struct s_cmds	*prev;
	struct s_cmds	*next;
	struct s_status	*status;
	struct s_file	**file;
}					t_cmds;

typedef struct s_envp
{
	char			*name;
	char			*value;

	struct s_envp	*next;
	struct s_envp	*prev;
	int				unset;
}					t_envp;

typedef struct s_ori
{
	t_cmds			*cmds;
	t_envp			*envs;
	char			*request;
}					t_ori;

typedef struct s_file
{
	int				fd;
	FILE			*f;
	char			*file_name;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

typedef struct s_pipe
{
	struct s_file	**file;
	struct s_cmds	**ret;
	struct s_cmds	**ret_save;
	struct s_envp	**lst;
	struct s_cmds	*current;
	int				num_pipes;
	int				**fds;
	int				*pids;
}					t_pipe;

typedef struct s_status
{
	int				isexit;
}					t_status;

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
char				*rep_ex_sig(char *str, char *ptr);
int					meta_type(char *str);
int					type_quote(char *str);
int					ft_tablen(char **env);
int					is_token(char *str);
int					tok_acc(char *str);
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
int					ft_echo(t_cmds *cmd, t_cmds **ret);
int					ft_pwd(t_cmds *cmd, t_envp **lst);
int					ft_unset(t_envp **lst, t_cmds *cmd);
int					ft_export(t_cmds *cmds, t_envp **env);
int					ft_exit(t_cmds **ret);
int					ft_env(t_envp **lst);
int					check_builtins(t_cmds **ret, t_envp **lst);
int					builtins_checker(t_cmds *current);
t_cmds				*find_name(t_cmds *current, char name);
int					parsing_command(int i, t_cmds *cmds, t_envp **lst,
						t_cmds **ret);
int					redirec_main(t_pipe *pipe, int flag);
int					parsing_redir(t_cmds *current, t_cmds **ret, t_envp **lst,
						t_file **file);
int					oper_redir_in(t_cmds *current, t_file **file,
						int stdin_save, t_status *stat);
int					oper_redir_out(t_cmds *current, t_file **file,
						int stdout_save, t_status *stat);
int					oper_heredoc_in(t_cmds *current, t_file **file,
						int stdin_save, t_status *stat);
int					oper_redir_app(t_cmds *current, t_file **file,
						int stdout_save, t_status *stat);
int					f_open(char *str, t_file **file);
FILE				*f_open2(char *str, t_file **file, int redir);
int					f_close(int fd, t_file **file);
int					f_close2(int fd, t_file **file, FILE *f);
int					close_file(t_file **file);
int					ft_new_tfile(t_file **file, char file_name[], int fd);
void				ft_del_tfile(t_file **file, int fd);
int					time_w(void);
int					read_heredoc(char *end_str, t_file **file, int flag);
int					exec_heredoc(t_file **file, int flag);
int					*set_posit(t_cmds **ret, int num);
int					count_pipes(t_cmds **ret);
int					set_command(t_cmds **ret, t_cmds ***new_ret, int i,
						int num);
void				set_pipe(t_cmds **ret, t_envp **list, t_file **file,
						t_pipe *pipe);
int					pipe_main(t_cmds **ret, t_envp **list, t_file **file);
void				check_exit_code(t_status *status, int exit_code);
int					check_flag(int flag, int res);
void				set_redir_parsing_param(int cpy_stdin_out[]);
int					convert_code(int num);
int					ch_err(int num, int cpy_stdin_out[]);
int					reset_stdin_out(int copy_stdin_out[]);
int					check_exec(char *command, int status);
void				sigint_handler(int sig);
int					exec_command(t_cmds *cmds, t_cmds **ret);

extern int g_exit_code;

#endif
