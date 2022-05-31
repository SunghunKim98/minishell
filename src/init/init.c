/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 00:59:46 by soahn             #+#    #+#             */
/*   Updated: 2022/05/31 19:34:37 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

void	init_all(t_data *data, int argc, char **argv, char **envp)
{
	if (!argc || !argv)
		exit(0);
	g_exit_code = 0;
	data->env = NULL;
	data->env_path = NULL;
	data->pipe_fd = NULL;
	data->pid = NULL;
	data->n_cmd = 0;
	data->cmd_lst = NULL;
	data->now_cmd = NULL;
	data->now_path = NULL;
	data->pwd = getcwd(NULL, 0);
	setting_env_things(data, envp);
	signal(SIGUSR1, execute_handler);
}

static void	free_cmd(t_data *data)
{
	int		i;
	t_cmd	*tmp;

	i = -1;
	tmp = data->cmd_lst;
	while (++i < data->n_cmd)
	{
		if (tmp[i].args)
			clear_cmd_args(tmp[i].args);
		if (tmp[i].redi)
			clear_cmd_redi(tmp[i].redi);
	}
	if (data->cmd_lst)
		free(data->cmd_lst);
	data->cmd_lst = NULL;
}

static void	free_pipe(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_cmd - 1)
		free(data->pipe_fd[i]);
	if (data->pipe_fd)
		free(data->pipe_fd);
	data->pipe_fd = NULL;
}

void	free_all(t_data *data)
{
	free_cmd(data);
	free_pipe(data);
	if (data->pid)
		free(data->pid);
	data->pid = NULL;
	if (data->heredoc.pipe_read)
		free(data->heredoc.pipe_read);
	data->heredoc.pipe_read = NULL;
}

void	free_now_cmd(t_data *data)
{
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
}
