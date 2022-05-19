/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 08:17:34 by soahn             #+#    #+#             */
/*   Updated: 2022/05/19 03:49:59 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_child_processes(t_data *data)
{
	int	status;
	int	ret;
	int	pid_last;
	int	i;

	// ret = -1; //굳이 초기화 필요?
	pid_last = data->pid[data->n_cmd - 1];
	//close pipe
	i = -1;
	while (++i < data->n_cmd - 1)
	{
		if (data->pipe_fd[i][READ] != STDIN_FILENO)
			close(data->pipe_fd[i][READ]);
		if (data->pipe_fd[i][WRITE] != STDOUT_FILENO)
			close(data->pipe_fd[i][WRITE]);
	}
	while (TRUE)
	{
		ret = waitpid(0, &status, 0);
		if (ret == ERROR)
			break ;
		if (pid_last == ret && g_exit_code > 128) // 128 + N으로 시그널 발생 시 exit code 설정됨
			g_exit_code = WEXITSTATUS(status); // 정상 종료 시 exit code 받아오기 매크로 사용해도 되지?
	}
}

int		execve_command(t_data *data, int i)
{
	char	**cmd;
	char	*cmd_path;
	int		fd[2];

	cmd = to_arr(data->cmd_lst[i].args); // 명령어 + 옵션 들어있는 리스트 배열로 바꾸기
	cmd_path = get_path(data->env_path, cmd[0]);
	arrange_pipe_fd(data, cmd[0], i, fd); //dup2 함수 호출
	if (is_builtin(cmd[0]))
		exec_builtin(data, cmd[0], i);
	else
		execve(cmd_path, cmd, data->env); // todo: env 저장 변수 이름 맞추기 pipex에서 env 파싱 가져오기
	return (0); //todo: exit code 넣어주기
}

void	go_execute(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_cmd)
	{
		create_pipe(data, i);
		fork_process(data, i);
		printf("3");
		/* 자식 프로세스 */
		if (data->pid[i] == 0)
		{
			//todo: sigusr 설정하고 ignore 주기
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			exit(execve_command(data, i));
		}
		/* 부모 프로세스 */
		else if (data->pid[i] > 0)
		{
			signal(SIGINT, SIG_IGN); // ignore sigint signal
			//todo: ./minishell 커맨드 들어왔을 때sigusr1 이해해서 무시하는 부분 추가
			if (i == data->n_cmd - 1)
				wait_child_processes(data);
		}
	}
}

void	execute_command(t_data *data)
{
	init_process(data);
	if (data->n_cmd > 1)
		init_pipe(data);
	go_execute(data);
}