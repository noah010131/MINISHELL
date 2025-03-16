/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 02:36:00 by princessj         #+#    #+#             */
/*   Updated: 2025/03/14 22:04:40 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define ERR	-1
//# define CB		0 //"Command_builtin"
//# define CE		1 //"Command_exec"
# define AR		2 //"Append_Redirect" // ">>"
# define RO		3 //"Redirect_Out" // ">"
# define RI		4 //"Redirect_In" // "<"
# define H		5 //"Heredoc" // "<<"
# define P		6 //"Pipe"
//# define Q		7 //"Quotes"
# define SQ		8 //"Single_quotes"
# define DQ		9 //"Double_quotes"
//# define STR	10 //"String"
# define S		11 //"Space"
# define W		12 //"Word"
# define E		13 //"Environment"

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_token_list
{
	int				cnt; // 추후 삭제 (디버깅용)
	struct s_token	*top;
	struct s_token	*bottom;
}	t_token_list;

typedef struct s_env
{
	char			*key; // 환경변수 이름 (ex : "PATH")
	char			*value; // 환경변수 값 (ex : "/usr/bin:/bin")
	char			*origin_env; // 원본 환경변수 값 저장하기
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_env_list
{
	t_env	*top; // 리스트의 첫 번째 (최신) 노드 -> stack의 head 역할
	t_env	*bottom; // 리스트의 마지막 (가장 오래된) 노드 -> stack의 tail 역할 : 제일 처음에 들어온 노드
}	t_env_list;

typedef struct s_data
{
	t_token_list	*token_list;
	t_env_list		*env_list;
}	t_data;

//compare_env_key
char	*compare_env_key(char *curr_str, int dollar, t_env_list *env_list);
char	*find_key(char *curr, int dollar);
bool	check_only_dollar(char *curr, int dollar_after);
char	*get_suffix(char *curr, int dollar);
int		find_dollar(char *str);
char	*env_value_merge(char *curr, int dollar, t_env_list *env_list);
void	expand_env(t_token_list *token_list, t_env_list *env_list);

//env_parse
void		env_parse(t_env_list **env_list, char **envp);
t_env_list	*add_env_list_node(t_env *new_env, t_env_list *env_list);
int			find_equal(char *envp);
t_env 		*create_envp_node(char *env_entry);
t_env		*check_only_key(char *env_entry);
bool		check_have_value(t_env *new_env, char *env_entry, int equal_pos);

// 공백 찾기
bool		prompt_only_space(char *prompt);
bool		find_space(char c);

//init
void		init_token_list(t_token_list **token_list);
void		init_env_list(t_env_list **env_list);
void		init_data(t_data *data, int arc, char **argv);
t_token		*init_token(void);
t_env		*init_envp(void);
void		add_token_list_node(t_token *new_token, t_token_list *token_list);

//debug
void		token_check_print(t_token *token);
void		token_list_check_print(t_token_list *token_list);
void		env_list_check_print(t_env_list *env_list);

//err
void		ft_err_print_minishell(char *str);
void		ft_malloc_fail(char *str);

//utils
char		*ft_strndup(const char *str, int stop);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strcat_minishell(char *s1, const char *s2);

//tokenizer
void		tokenizer(char *cmd, t_token_list *token_list);
t_token		*add_token(char *cmd, int type);
t_token		*add_special_token(char **cmd, char *symbol, int type, int step);
t_token		*is_special(char **cmd);
bool		is_really_special(char c);
char		*read_word(char **cmd, char stop);
char		*read_only_space(char **cmd, char space);
char		*read_until_quote(char **cmd, char stop_quote);
void		open_quote(void);

//merge_token
void		merge_token_str(t_token_list *token_list);
char		*merge_string(char *curr_str, char *next_str);

//free
void		free_token(t_token **token);
void		free_env(t_env **env);
void		free_token_list(t_token_list **token_list);
void		free_env_list(t_env_list **env_list);
void		free_all(t_data *data, char **prompt);


void		parsing(t_data *data, char *prompt);
void		restart_readline(t_data *data, char **prompt);

#endif