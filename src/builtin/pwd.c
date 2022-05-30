/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:50:15 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 16:27:28 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

int	pwd(t_data *data, int *fd)
{
	free(data->pwd);
	data->pwd = getcwd(NULL, 0);
	ft_putendl_fd(data->pwd, fd[WRITE]);
	return (g_exit_code);
}
