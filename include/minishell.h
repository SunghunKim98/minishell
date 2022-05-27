/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:09:41 by soahn             #+#    #+#             */
/*   Updated: 2022/05/19 03:36:16 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/include/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

// 성훈 추가
# define FAIL 0
# define SUCCESS 1

#define BUFF_SIZE 10000

typedef struct s_env
{
	char			*key;
	char			*value;
	int				env_flag;
	struct s_env	*next;
	struct s_env	*prev;
}			t_env;

typedef struct s_env_deq
{
	int		size;
	t_env	*head;
	t_env	*last;
}			t_env_deq;

typedef struct s_exit
{
	int	code;
	int	sig_flag;
}			t_exit;

// -------------------

# define TRUE 1
# define FALSE 0
# define ERROR 2
# define READ 0
# define WRITE 1

# define _CANT_EXEC 126 // 파일이 존재하지만 실행 불가
# define _NO_COMMAND 127 // 존재하지 않는 파일 또는 디렉토리

# define R_S_REDIRECT 1 // >
# define R_D_REDIRECT 2 // >>
# define L_S_REDIRECT 3 // <
# define L_D_REDIRECT 4 // <<

int   g_exit_code;

typedef struct s_args
{
	char			*str;
	struct s_args	*next;
}			t_args;

typedef struct s_redi
{
	int				flag; 
	char			*file_name;
	struct s_redi	*next;
}			t_redi;
typedef struct s_cmd
{
	t_args	*args;
	t_redi *redi;
}			t_cmd;
typedef struct s_data
{
	char		**env;
	char		**env_path;
	int			**pipe_fd;
	int			*pid;
    int			n_cmd;
	t_cmd		*cmd_lst;
	t_env_deq	*env_deq; // 성훈 추가
    
}		t_data;

/*init.c*/
void   init_all(int *argc, char **argv, char **envp, t_data *data);

/*parse.c*/
int   parsing(char *line, t_data *data);

/*error*/
void   malloc_error(void *addr);
void   error_message(char *cmd, char *msg);

/*execute*/
/*pipe.c*/
void   arrange_pipe_fd(t_data *data, char *cmd, int i, int fd[]);
void   execute_command(t_data *data);
void   go_execute(t_data *data);
int    execve_command(t_data *data, int i);
void   wait_child_processes(t_data *data);

void	setting_env_things(t_data *data, char **envp);
int	ft_strcmp(const char *s1, const char *s2);
char	**to_arr(t_args *cmd);
char	*get_path(char **paths, char *cmd);
void	init_process(t_data *data);
void	init_pipe(t_data *data);
void	create_pipe(t_data *data, int i);
void	fork_process(t_data *data, int i);
void	redirection(t_data *data, int i, int fd[]);
int		is_builtin(char *cmd);
void	exec_builtin(t_data *data, char *cmd, int i);

// ------- 성훈 추가 ------- //
/* errorcheck.c */
int 	line_error_check(char *line);
int		check_error_case_0(char *line);
int		check_error_case_1(char *line);

/* check_case.c */
int		check_different_case(char *p);
int		check_case_other(char *p);
int		check_case_redi(char *p);
int		check_case_pipe(char *p);


int		deal_error(int i);
int		check_quoto_closed(int flag_sq, int flag_dq);
int		line_parsing(char *line, t_data *p_data);
void	get_command_from_line(char **command_arr, t_data *p_data);
t_cmd	*init_cmd_lst(t_data *p_data);
void	set_command_data(char *command, t_cmd *cmd);
void	set_t_redi(t_redi *new_node, t_redi **node);
void	set_t_args(t_args *new_node, t_args **node);
t_redi	*init_cmd_redi(char *command);
void	free_split_one(char **arr);
void	set_cmd_redi_flag(char *arr, t_redi *p);
t_args	*init_cmd_node(char *command);
char	**convert_line_to_command(char *line);
void	deal_with_redirection(char **command, int idx, char **p);
char	*make_str_by_pointer(char *start, char *end);
char	**set_command_with_line(char *line, t_data *p_data);
void	set_command_count(char *line, t_data *p_data);
void	if_pipe_opened(char **line);
char	*make_standard_line(char *line, t_data *p_data);
char	*trim_line(int *start, int divider, char *line, t_data *p_data);
void	double_char_array_free(char **arr);
char	*join_strings(char *line, char **separator, int *start);
char	*fillin_buf(char *origin, t_data *p_data);
char	*return_new_line(char *buffer, int length);
char	select_quoto_type(char *buffer, int length);
void	set_env(char **line, int *i, t_data *p_data);
char	*parse_env_after_dollar(char **line, int *i, t_data *p_data);
char	*get_env_by_key(char *key, t_data *p_data);
t_env	*check_env_list(char *key, t_data *p_data);
int		check_char_special(char ch);
char	*advanced_itoa(int n);
char	*make_buffer(void);
void	init_variables(int *i, int *j, int *flag_sq, int *flag_dq);
char	**separate_by_div(char *line, int start, int divider);

char	*malloc_single_char(int size);
char	**malloc_double_char(int size);
void	set_divider(char *line, int start, int *divider);
char	*make_line_without_space(char *line, int *start);
char	*trim_space_line(char *line, int start);
char	*advanced_strlcpy(char *line, int start);
int		check_if_sep(char ch);
char	*advanced_strdup_no_free(char *line);
char	*advanced_strdup(char *line);
void	init_utils(int *start, int *divider, int *flag);
char	*strdup_with_pointer(char *start, char *end);
char	*find_pointer_for_separation(char *start);




// ---------------- //

#endif