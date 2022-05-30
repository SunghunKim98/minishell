/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 00:59:46 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 16:28:38 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_all(t_data *data)
{
	data->env = NULL;
	data->env_path = NULL;
	data->pipe_fd = NULL;
	data->pid = NULL;
	data->n_cmd = 0;
	data->cmd_lst = NULL;
	data->now_cmd = NULL;
	data->now_path = NULL;
	data->pwd = getcwd(NULL, 0);
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
