/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 02:28:10 by soahn             #+#    #+#             */
/*   Updated: 2022/05/19 03:36:09 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_fd(char *file, int flag)
{
	int	fd;

	fd = open(file, flag, 0644);
	if (fd < 0)
	{
		error_message(file, strerror(errno));
		exit(_NO_COMMAND);
	}
	return (fd);
}

void	redirection(t_data *data, int i, int fd[])
{
	t_redi	*now;

	now = data->cmd_lst[i].redi;
	while (now)
	{
		if (now->flag == L_S_REDIRECT)
			fd[READ] = open_fd(now->file_name, O_RDONLY);
		else if (now->flag == R_S_REDIRECT)
			fd[WRITE] = open_fd(now->file_name, O_WRONLY | O_CREAT | O_TRUNC);
		else if (now->flag == R_D_REDIRECT)
			fd[WRITE] = open_fd(now->file_name, O_WRONLY | O_APPEND | O_CREAT);
		//todo: << 이해하고 만들기 get here doc
		now = now->next;
	}
}