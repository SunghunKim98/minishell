/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:11:51 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 18:58:09 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

static void	cd_home(t_data *data)
{
	if (chdir(data->home) == -1)
	{
		error_message_arg("cd", data->home, "No such file or directory");
		g_exit_code = 1;
	}
}

int	cd(t_data *data, char *path)
{
	if ((path[0] == '~' && !path[1]) || !path)
		cd_home(data);
	else if (chdir(path) == -1)
	{
		error_message(path, "No such file or directory");
		g_exit_code = 1;
		exit(g_exit_code);
	}
	return (0);
}
