/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 08:17:34 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 19:26:28 by soahn            ###   ########.fr       */
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
		if (pid_last == ret)
			g_exit_code = WEXITSTATUS(status);
		if (ret == -1)
			break ;
	}
}

int	execve_command(t_data *data, int i)
{
	int		fd[2];

	free_now_cmd(data);
	data->now_cmd = to_arr(data->cmd_lst[i].args);
	data->now_path = get_path(data->env_path, data->now_cmd[0]);
	arrange_pipe_fd(data, data->now_cmd[0], i, fd);
	if (is_builtin(data->now_cmd[0]))
		exec_builtin(data, data->now_cmd, fd);
	else
	{
		kill(0, SIGUSR1);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(data->now_path, data->now_cmd, data->env);
		error_message(data->now_cmd[0], "command not found");
		exit(127);
	}
	return (1);
}

static void	go_execute(t_data *data, int i)
{
	if (i > data->n_cmd - 1)
		return ;
	create_pipe(data, i);
	fork_process(data, i);
	if (data->pid[i] == 0)
	{
		signal(SIGUSR1, SIG_IGN);
		execve_command(data, i);
		exit(g_exit_code);
	}
	else if (data->pid[i] > 0)
	{
		signal(SIGINT, SIG_IGN);
		if (i == data->n_cmd - 1)
		{
			wait_child_processes(data);
			if (!ft_strcmp(data->cmd_lst[i].args->str, "exit"))
				exit(g_exit_code);
		}
		go_execute(data, i + 1);
	}
}

void	execute_command(t_data *data)
{
	char	**cmd;
	int		flag;

	init_process(data);
	if (data->n_cmd > 1)
		init_pipe(data);
	if (heredoc_count(data))
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
