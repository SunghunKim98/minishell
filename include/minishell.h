/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:09:41 by soahn             #+#    #+#             */
/*   Updated: 2022/05/25 05:06:09 by soahn            ###   ########.fr       */
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

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define READ 0
# define WRITE 1

# define _CANT_EXEC 126 // 파일이 존재하지만 실행 불가
# define _NO_COMMAND 127 // 존재하지 않는 파일 또는 디렉토리

# define R_S_REDIRECT 1 // >
# define R_D_REDIRECT 2 // >>
# define L_S_REDIRECT 3 // <
# define L_D_REDIRECT 4 // <<

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

typedef struct s_here
{
	int		*pipe_read;
	int		seq; // 현재 sequence
	int		n_here; // 전체 개수
}			t_here;

typedef struct s_data
{
	char		**env;
	char		**env_path;
	char		*home;
	int			**pipe_fd;
	int			*pid;
    int			n_cmd;
	t_here		heredoc;
	t_cmd		*cmd_lst;
    
}		t_data;

/*parse.c*/
int	parsing(char *line, t_data *data);
void	main_handler(int signo);

/*error*/
void	malloc_error(void *addr);
void	error_message(char *cmd, char *msg);
void	error_message_arg(char *cmd, char *arg, char *msg);

/*execute*/
/*pipe.c*/
void   arrange_pipe_fd(t_data *data, char *cmd, int i, int fd[]);
void   execute_command(t_data *data);
int    execve_command(t_data *data, int i);
void   wait_child_processes(t_data *data);

void	setting_env_things(t_data *data, char **envp);
int		ft_strcmp(const char *s1, const char *s2);
char	**to_arr(t_args *cmd);
char	*get_path(char **paths, char *cmd);
void	init_process(t_data *data);
void	init_pipe(t_data *data);
void	create_pipe(t_data *data, int i);
void	fork_process(t_data *data, int i);
void	redirection(t_data *data, int i, int *fd);
int		is_builtin(char *cmd);
void	exec_builtin(t_data *data, char **cmd, int *fd);
void	init_all(t_data *data);
void	execute_handler(int signo);
void	heredoc_handler(int signo);

int		cd(t_data *data, char *path);
int		echo(char **words, int *fd);
int		pwd(int *fd);
int		go_exit(t_data *data, char **cmd); // unsigned char 로 내보내야 함
int		ft_isspace(char c);

int	heredoc_main(t_data *data);
int	heredoc_count(t_data *data);

#endif