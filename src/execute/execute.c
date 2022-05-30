/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungkim <sungkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 08:17:34 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 15:53:21 by sungkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

void	wait_child_processes(t_data *data)
{
	int	status;
	int	ret;
	int	pid_last;
	int	i;

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
		ret = waitpid(0, &status, 0); // 더 이상 기다릴 프로세스가 없으면 -1을 반환함.
		// printf("waiting..");
		if (ret == -1)
			break ;
		if (pid_last == ret && g_exit_code > 128) // 128 + N으로 시그널 발생 시 exit code 설정됨
			g_exit_code = WEXITSTATUS(status); // 정상 종료 시 (-> sigchld) exit code 받아오기 매크로 사용해도 되지?
	}
}

int		execve_command(t_data *data, int i)
{
	// char	**cmd;
	// char	*cmd_path;
	int		fd[2];

	if (data->now_cmd)
	{
		double_char_array_free(data->now_cmd);
		data->now_cmd = NULL;
	}
	if (data->now_path)
	{
		free(data->now_path);
		data->now_path = NULL;
	}


	data->now_cmd = to_arr(data->cmd_lst[i].args); // 명령어 + 옵션 들어있는 리스트 배열로 바꾸기
	data->now_path = get_path(data->env_path, data->now_cmd[0]);

	arrange_pipe_fd(data, data->now_cmd[0], i, fd); //dup2 함수 호출//문제여
	if (is_builtin(data->now_cmd[0]))
		exec_builtin(data, data->now_cmd, fd);
	else
	{
		kill(0, SIGUSR1);
		// execve(cmd_path, cmd, data->env); // todo: env 저장 변수 이름 맞추기 pipex에서 env 파싱 가져오기

		execve(data->now_path, data->now_cmd, data->env); // todo: env 저장 변수 이름 맞추기 pipex에서 env 파싱 가져오기
	}

	return (1);
}

static void	go_execute(t_data *data, int i)
{
	if (i > data->n_cmd - 1)
		return ;
	create_pipe(data, i);
	fork_process(data, i);
	/* 자식 프로세스 */
	if (data->pid[i] == 0)
	{
		signal(SIGUSR1, SIG_IGN);
		execve_command(data, i);
		exit(g_exit_code);
	}
	/* 부모 프로세스 */
	else if (data->pid[i] > 0)
	{
		signal(SIGINT, SIG_IGN); // ignore sigint signal
		//todo: ./minishell 커맨드 들어왔을 때sigusr1 이해해서 무시하는 부분 추가
		if (i == data->n_cmd - 1)
			wait_child_processes(data);
		go_execute(data, i + 1); // 재귀적으로 들어가서 다음 명령어 호출
	}
}

void	execute_command(t_data *data)
{
	char	**cmd;
	int		flag;

	init_process(data);
	if (data->n_cmd > 1)
		init_pipe(data);
	if (heredoc_count(data)) // heredoc sign (<<) 이 있으면, 표준입력 받아서 heredoc 파이프에 따로 저장.
		if (heredoc_main(data) == ERROR)
			return ;
	data->heredoc.seq = 0;
	cmd = to_arr(data->cmd_lst[0].args);
	flag = is_builtin(cmd[0]);
	double_char_array_free(cmd);
	cmd = NULL;
	if (flag && (data->n_cmd == 1))
		execve_command(data, 0);
	else
		go_execute(data, 0);
}
