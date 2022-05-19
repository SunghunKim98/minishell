/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 05:48:09 by soahn             #+#    #+#             */
/*   Updated: 2022/05/18 15:38:32 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe(t_data *data)
{
	int	i;

	i = -1;
	data->pipe_fd = (int **)malloc(sizeof(int *) * (data->n_cmd - 1));
	malloc_error(data->pipe_fd);
	while (++i < data->n_cmd)
	{
		data->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		malloc_error(data->pipe_fd[i]);
		data->pipe_fd[i][READ] = STDIN_FILENO;
		data->pipe_fd[i][WRITE] = STDOUT_FILENO;
	}
}

void	create_pipe(t_data *data, int i)
{
	char	*msg;

	if (i == data->n_cmd - 1)
		return ;
	if (pipe(data->pipe_fd[i]) < 0)
	{
		msg = strerror(errno);
		ft_putendl_fd(msg, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

/*표준입력, 출력 제외하고 모두 close*/
void	close_pipe(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_cmd - 1)
	{
		if (data->pipe_fd[i][READ] != STDIN_FILENO)
			close(data->pipe_fd[i][READ]);
		if (data->pipe_fd[i][WRITE] != STDOUT_FILENO)
			clode(data->pipe_fd[i][WRITE]);
	}
}

void	arrange_pipe_fd(t_data *data, char *cmd, int i, int fd[])
{
	int		ret;

	fd[READ] = data->pipe_fd[i - 1][READ];
	fd[WRITE] = data->pipe_fd[i][WRITE];
	redirection(data, cmd, i, fd);
	//todo: ./minishell 처리
	if (!is_builtin(cmd)) // 빌트인 명령어는 어차피 다 stdin, stdout으로 동작해서 dup2 필요없어..!(아마)
	{
		if (fd[READ] != STDIN_FILENO)
			ret = dup2(fd[READ], STDIN_FILENO);
		if (fd[WRITE] != STDOUT_FILENO)
			ret = dup2(fd[WRITE], STDOUT_FILENO);
		if (ret < 0)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		close_pipe(data);
	}
}