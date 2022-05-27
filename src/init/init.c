/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungkim <sungkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 00:59:46 by soahn             #+#    #+#             */
/*   Updated: 2022/05/27 17:23:54 by sungkim          ###   ########.fr       */
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
}
