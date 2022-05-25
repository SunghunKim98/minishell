/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:08:44 by soahn             #+#    #+#             */
/*   Updated: 2022/05/25 05:08:32 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// 전체 커맨드에서 heredoc 개수 세기
int	heredoc_count(t_data *data)
{
	int		i;
	int		cnt;
	t_redi	*now;

	i = -1;
	cnt = 0;
	while (++i < data->n_cmd)
	{
		now = data->cmd_lst[i].redi;
		while (now)
		{
			if (now->flag == L_D_REDIRECT)
				cnt++;
			now = now->next;
		}
	}
	data->heredoc.n_here = cnt;
	return (cnt);
}

int	write_from_stdin(char *limiter, int fd[])
{
	char	*in;

	signal(SIGINT, heredoc_handler);
	while (TRUE)
	{
		in = readline("> ");
		if (!in || !ft_strcmp(in, limiter))
			break ;
		ft_putendl_fd(in, fd[WRITE]);
		free(in);
	}
	exit(0);
}

int	save_if_here_doc(t_data *data, t_redi *now)
{
	int		fd[2];
	int		pid;
	int		status;
	char	*limiter;

	if (now->flag == L_D_REDIRECT)
	{
		limiter = now->file_name;
		if (pipe(fd) == ERROR)
			return (ERROR);
		pid = fork();
		if (pid > 0)
		{
			signal(SIGINT, SIG_IGN);
			wait(&status);
			if (WEXITSTATUS(status) == 1) // heredoc에서 ctrl c 눌렀을 때 exit code 1
				return (ERROR);
		}
		else if (!pid)
			write_from_stdin(limiter, fd);
		close(fd[WRITE]);
		data->heredoc.pipe_read[data->heredoc.seq++] = fd[READ];
		return (fd[READ]);
	}
	return (-2);
}

int	heredoc_main(t_data *data)
{
	t_redi	*now;
	int		i;

	i = -1;
	data->heredoc.pipe_read = (int *)malloc(sizeof(int) * data->heredoc.n_here);
	malloc_error(data->heredoc.pipe_read);
	data->heredoc.seq = 0;
	while (++i < data->n_cmd)
	{
		now = data->cmd_lst[i].redi;
		while (now)
		{
			if (save_if_here_doc(data, now) == ERROR)
				return (ERROR);
			now = now->next;
		}
	}
	return (0);
}