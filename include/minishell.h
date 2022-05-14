/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:09:41 by soahn             #+#    #+#             */
/*   Updated: 2022/05/08 01:04:25 by soahn            ###   ########.fr       */
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

# define TRUE 1
# define FALSE 0
# define ERROR 2

typedef struct s_node
{
	char			*str;
	struct s_node	*next;
}			t_node;

typedef struct s_cmd
{
	t_node	*text;
	t_node	*redi;
}			t_cmd;
typedef struct s_data
{
    int			n_cmd;
	t_cmd		*cmd_lst;
    
}		t_data;

/*init.c*/
void	init_all(int *argc, char **argv, char **envp, t_data *data);

/*parse.c*/
int	parsing(char *line, t_data *data);

#endif
