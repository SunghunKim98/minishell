/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 06:29:25 by soahn             #+#    #+#             */
/*   Updated: 2022/05/19 03:47:01 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_process(t_data *data)
{
	data->pid = (int *)malloc(sizeof(int) * data->n_cmd);
	malloc_error(data->pid);
}

void	fork_process(t_data *data, int i)
{
	char	*msg;

	data->pid[i] = fork();
	if (data->pid[i] == ERROR)
	{
		msg = strerror(errno);
		ft_putendl_fd(msg, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}