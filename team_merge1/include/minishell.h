/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:45:17 by jihyeki2          #+#    #+#             */
/*   Updated: 2025/03/19 04:24:11 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termcap.h>
# include <unistd.h>
# include <limits.h>

# define ERR -1
# define AR 2 //"Append_Redirect" // ">>"
# define RO 3 //"Redirect_Out" // ">"
# define RI 4 //"Redirect_In" // "<"
# define H 5  //"Heredoc" // "<<"
# define P 6  //"Pipe"
# define SQ 7 //"Single_quotes"
# define DQ 8 //"Double_quotes"
# define S 15 //"Space"
# define W 16 //"Word"

# define TEMP ".temp_heredoc.txt"
# define OUTPUT ".temp.txt"
# define WORD 9
# define PIPE_N 10
# define REDIR_IN 11
# define REDIR_OUT 12
# define HEREDOC_IN 13
# define REDIR_APP 14
# define SIN_QUOTE 20
# define DOUB_QUOTE 21
# define TOKEN_EX_STT 22

/* before struct */

typedef struct s_data	t_data;

typedef struct s_pars	t_pars;

typedef struct s_pipe
{
	int					num_pipes;
	int					**fds;
	int					*pids;
	int					fd;
}						t_pipe;

// 파이프의 갯수를 저장하는 리스트 (실행)

typedef struct s_cmds
{
	int					flag;
	int					code_id;
	char				*name;
	struct s_cmds		*prev;
	struct s_cmds		*next;
	// struct s_file	**file;
	char				**env;
}						t_cmds;

// s_pars 를 만들기 위한 1차로 들어온 변수를 파싱하는 리스트 (파싱)

typedef struct s_envp
{
	char				*name;
	char				*value;
	char				*origin_env;

	struct s_envp		*next;
	struct s_envp		*prev;
}						t_envp;

typedef struct s_ori
{
	t_data				*data;
	t_envp				**envs;
	t_pars				**parsee;
	char				*request;
	char				**env;
}						t_ori;

typedef enum s_type_redir
{
	REDIR_IN_S,
	REDIR_OUT_S,
	HEREDOC,
	REDIR_OUT_D,
}						t_type_redir;

typedef struct s_redir
{
	t_type_redir		type;
	char				*filename;
	int					fd;
	FILE				*f;
	struct s_redir		*next;
}						t_redir;
// 리다이랙션과 파일 디스크립터 저장 (파싱 & 실행)

typedef struct s_pars
{
	char				*command;
	char				**arguments;
	t_redir				*redirections;
	struct s_pars		*next;
}						t_pars;
// ori 의 값을 실행하기 편하도록 분할 (파싱 & 실행)

extern int				g_exit_code;

/* jihye code */
typedef struct s_token
{
	int					type;
	char				*str;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_token_list
{
	int					cnt;
	int					open_quote_flag;
	struct s_token		*top;
	struct s_token		*bottom;
}						t_token_list;

typedef struct s_env
{
	char				*key;
	char				*value;
	char				*origin_env;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_env_list
{
	int					flag;
	int					dollar_cnt;
	t_env				*top;
	t_env				*bottom;
}						t_env_list;

typedef struct s_data
{
	char				*prompt;
	t_token_list		*token_list;
	t_env_list			*env_list;
}						t_data;

// transfer_env.c
void					transfer_env(t_data *data, t_ori *ori, char **envp);
void					synchro_env(t_data *data, t_ori *ori);
t_env					*create_envp_node2(t_envp *origin);

// debug.c
void					env_list_check_print(t_env_list *env_list);
void					token_list_check_print(t_token_list *token_list);
void					token_check_print(t_token *token);
void					parser_check_print(t_pars **parser);

// init.c
void					init_data(t_data *data, int arc, char **argv);
void					init_token_list(t_token_list **token_list);
void					init_env_list(t_env_list **env_list);
t_env					*init_envp(void);
t_token					*init_token(void);

// add_list_node.c
t_env_list				*add_env_list_node(t_env *new_env,
							t_env_list *env_list);
void					add_token_list_node(t_token *new_token,
							t_token_list *token_list);

// compare_env_key.c
char					*compare_env_key(char *curr_str, int dollar,
							t_env_list *env_list);
char					*find_key(char *curr, int dollar, t_env_list *env_list);
int						check_only_dollar(char *curr, int dollar);
int						check_multiple_dollar(char *curr, int dollar); //, t_env_list *env_list);
char					*special_dollar_sign(char c);

// env_parse.c
void					env_parse(t_env_list **env_list, char **envp);
t_env					*create_envp_node(char *env_entry);
t_env					*check_only_key(char *env_entry);
bool					check_have_value(t_env *new_env, char *env_entry,
							int equal_pos);
int						find_equal(char *envp);

// error.c
void					ft_malloc_fail(char *str);
void					ft_err_print_minishell(char *str);
void					open_quote(t_data *data);
void					ft_syntax_err(char *str);

// expand_env.c
void					expand_env(t_token_list *token_list,
							t_env_list *env_list);
void					process_token(t_token *curr, t_env_list *env_list);
char					*env_value_merge(char *curr, int dollar,
							t_env_list *env_list);
int						find_dollar(char *str);

// free.c
void					free_all(t_data *data, char **prompt);
void					free_env_list(t_env_list **env_list);
void					free_env(t_env **env);
void					free_token_list(t_token_list **token_list);
void					free_token(t_token **token);

// merge_token.c
void					merge_token_str(t_token_list *token_list);
void					merge_token_node(t_token *first, t_token *sec,
							t_token_list *list);

// tokenizer_read.c
char					*read_until_quote(char **cmd, char stop_quote,
							t_data *data);
char					*read_only_space(char **cmd, char space);
char					*read_word(char **cmd, char stop);

// tokenizer.c
void					tokenizer(char *cmd, t_data *data);
t_token					*is_special(char **cmd);
t_token					*add_special_token(char **cmd, char *symbol, int type,
							int step);
bool					is_really_special(char c);
t_token					*add_token(char *cmd, int type);
t_token					*add_token_special(char *cmd, int type);

// utils3.c
void					remove_space_token(t_token_list **token_list);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strndup(const char *str, int stop);
char					*get_suffix(char *curr, int dollar);
char					*get_suffix2(char *curr, int dollar);

// syntax_check.c
int						syntax_check(t_token_list *token_list);
int						pipe_syntax_check(t_token *first, t_token *second);
int						redirect_syntax_check(t_token *first, t_token *second);
int						newline_syntax_check(t_token *first);

// main_utils.c
void					init_all(t_data *data, int ac, char **av, char **envp);
char					*ft_readline(t_data *data);

// in main.c
bool					find_space(char c);
bool					prompt_only_space(char *prompt);
int						parsing(t_data *data, char *prompt);
void					restart_readline(t_data *data, char **prompt);
void					set_signal(void);

/*before team code*/

// change_struct_parser.c
int						keep_pars(t_pars *new, t_token *token);
int						keep_pars2(t_pars *new, t_cmds *cmd);

int						add_arg(t_pars *pars, char *token_str);
t_pars					**change_struct(t_token_list *list);
t_cmds					*pars_state2(t_pars *new, t_cmds *current, t_pars **ret);
void					pars_state(t_pars *par_node, t_token *token_curr,
							t_pars **pars_list);

// parser_utils.c
void					free_pars_list(t_pars **parsee);
void					add_last_par(t_pars **pars, t_pars *new);
int						add_last_redir(t_redir *new, t_pars *pars);
char					**free_pars_arguments(char **arguments);
t_redir					*new_redir(t_type_redir type, char *filename);

// parser_init.c
t_pars					*init_pars_node(void);
t_pars					**init_parser(void);

/* team code */


int					ft_occur(char *str, char c);
char				*ft_strlimdup(char *str, int lim);
t_cmds				**ft_last_tcmd(char *str, int code, t_cmds **list_cmd);
int					non_print(char *str);
t_cmds				**split_token(char *request);
int					ft_pos_c(char *str, char c);
char				*end_quote(char *str, char c);
int					is_not_word(char *str);
int					syn_err(char *str);
int					code_lex(char *str);
int					is_not_word(char *str);
int					meta_type(char *str);
int					type_quote(char *str);
int					ft_tablen(char **env);
int					is_token(char *str);
int					tok_acc(char *str);
t_envp				**add_envplast(t_envp **ret, char *str);
t_envp				**add_envplast_null(t_envp **ret, char *str);
void				*free_envp(t_envp **lst);
// t_envp				**lst_env(char **env);
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
int					ft_echo(t_pars *cmd);
int					ft_env(t_envp **lst);
int					ft_exit(t_pars *cmd);
int					ft_export(t_pars *pars, t_envp **env);
int					ft_pwd(void);
int					ft_unset(t_envp **lst, t_pars *pars);
int					ft_env(t_envp **lst);
void				check_exit_code(t_pars **commands,
						int exit_code, t_envp **lst, t_ori *ori);
int					convert_code(int num);
int					ch_err(int num, int cpy_stdin_out[]);
int					reset_stdin_out(int copy_stdin_out[]);
char				*expanding_hd(char *str, t_envp **envp);
char				*free_ret_nul(char *str);
void				cp_exp_beg(char **str, char **ret, int *j);
void				init_1(int *i, int *j, t_cmds ***ret);
char				**freee_error(char **tab);
int					free_ori(t_ori *ori);
void				free_pars_ls(t_pars **parsee);
char				*rep_ex_sig_hd(char *str, char *ptr);
char				*rep_ex_sig(char *str, char *ptr);
int					all_toge(t_ori *ori);
int					exp_exception_hd(char *str);
int					parsing_command(t_pars *c, t_envp **lst, t_ori *ori);
int					check_error(char *command, char **arguments, int status);
int					oper_redir_in(t_pars *c, int stdin_save);
int					oper_redir_out(t_pars *c, int stdout_save);
int					oper_heredoc_in(int stdin_save,
						t_ori *ori, t_pipe *pipe, t_redir *save);
int					read_heredoc(int flag, t_ori *ori,
						t_pipe *pipe, t_redir *save);
int					exec_heredoc(int flag, t_redir	*redirections, t_ori *ori);
int					oper_redir_app(t_pars *c, int stdout_save);
int					redirec_main(t_pars	*command,
						t_envp **lst, t_ori *ori, t_pipe *pipe);
int					execute_parsing(int std_s[],
						t_ori *ori, t_pipe *pipe, t_redir *save);
int					close_file(t_redir *redirections);
int					reset_stdin_out(int copy_stdin_out[]);
int					pipe_main(t_pars	**commands, t_envp **list, t_ori *ori);
int					count_pipes(t_pars **commands);
void				free_tori(t_ori *ori);
int					print_buff(char *buffer, int filenum);
int					check_heredoc(t_pars **commands);
int					check_place(t_pars **commands, int place);
int					ft_cd(t_ori *ori, t_pars *pars);
int					create_redir_in_order(t_pars	*command);
void				free_redirections(t_redir *redirections);
int					pipe_helper(t_pars	**commands, t_ori *ori);
void				print_no_command(char *argument);
void				sigquit_handler(int sig);
void				sigint_handler(int sig);
int					signal_exit_check(int status, int *flag);
void				exec_ve(char *command, t_pars *c, char **env);
int					ft_stricmp(const char *first,
						const char *second, size_t length);
t_redir				*new_redir(t_type_redir type, char *filename);
void				pers_free(void *ptr);
int					check_ch(char *str, char checker, int i);
bool				print_error(char *str);
void				check_error_code(char *name);
void				free_child(t_ori *ori, int free_flag,
						t_pipe *pipe, t_redir *save);
void				free_child1(t_envp **lst, t_ori *ori,
						int free_flag, int files[]);
char				*get_next_line(int fd);
int					read_heredoc1(char *end_str,
						int flag, t_ori *ori, int files[]);
// int					ft_strlen(const char *str);
t_pars				*put_command(t_pars	**c, int i);
void				free_fds(int **fds, int end);
int					bad_id(char *str);
int					check_hypen(char *str);
int					check_direc(char *cmd);
void				print_message(char *argument, int num);
int					free_finish(int num_pipes, int *pids, int **fds);
void				free_pipe(t_pipe *pipe);
void				pipe_operation(t_pipe *pipe, int i);
int					malloc_pipe(t_pipe *p);
char				*new_expanded_hd(char *str, char *ptr, t_envp *match);
int					nb_expand_hd(char *str);
int					exec_command(t_pars *c, t_envp **lst, char **env);

#endif