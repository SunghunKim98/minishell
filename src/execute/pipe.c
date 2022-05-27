/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 05:48:09 by soahn             #+#    #+#             */
/*   Updated: 2022/05/23 23:20:02 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_pipe(t_data *data)
{
	int	i;

	i = -1;
	data->pipe_fd = (int **)malloc(sizeof(int *) * (data->n_cmd - 1));
	malloc_error(data->pipe_fd);
	while (++i < data->n_cmd - 1)
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
			close(data->pipe_fd[i][WRITE]);
	}
}

void	arrange_pipe_fd(t_data *data, char *cmd, int i, int fd[])
{
	int		ret;

	// pipe 연결이 똑바로 안 됨!! 이제 되는듯!! 근데 프로세스 종료가 안됨!!
	ret = 0;
	if (i != 0)
		fd[READ] = data->pipe_fd[i - 1][READ];
	else
		fd[READ] = STDIN_FILENO;
	if (i != data->n_cmd - 1)
		fd[WRITE] = data->pipe_fd[i][WRITE];
	else
		fd[WRITE] = STDOUT_FILENO;
	// printf("cmd: %s\n", cmd);
	// printf("fd: read: %d, fd: write: %d\n", fd[READ], fd[WRITE]);
	redirection(data, i, fd);
	// printf("redi done\n");
	//todo: ./minishell 처리
	// printf("is builtin : %d\n", is_builtin(cmd));
	if (!is_builtin(cmd)) // 빌트인 명령어는 부모 프로세스에서 실행
	{
		// printf("5");
		if (fd[READ] != STDIN_FILENO)
		{
			// printf("read dup2: %d <-> STDIN\n", fd[READ]);
			ret = dup2(fd[READ], STDIN_FILENO);
		}
		if (fd[WRITE] != STDOUT_FILENO)
		{
			// printf("write dup2: %d <-> STDOUT\n", fd[WRITE]);
			ret = dup2(fd[WRITE], STDOUT_FILENO);
		}
		if (ret < 0)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		close_pipe(data);
	}
}