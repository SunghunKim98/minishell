/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:09:41 by soahn             #+#    #+#             */
/*   Updated: 2022/05/17 05:15:24 by soahn            ###   ########.fr       */
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
# define ERROR 2
# define READ 0
# define WRITE 1

# define _CANT_EXEC 126 // 파일이 존재하지만 실행 불가
# define _NO_COMMAND 127 // 존재하지 않는 파일 또는 디렉토리

# define R_S_RIDIRECT 1 // >
# define R_D_RIDIRECT 2 // >>
# define L_S_RIDIRECT 3 // <
# define L_D_RIDIRECT 4 // <<

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
    int			n_cmd;
	t_cmd		*cmd_lst;
    
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
int      execve_command(t_data *data, int i);
void   wait_child_processes(t_data *data);
#endif