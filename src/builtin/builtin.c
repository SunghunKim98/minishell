/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 08:43:56 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 19:08:43 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (TRUE);
	return (FALSE);
}

void	exec_builtin(t_data *data, char **cmd, int *fd)
{
	if (!ft_strcmp(cmd[0], "echo"))
		g_exit_code = echo(cmd, fd);
	else if (!ft_strcmp(cmd[0], "cd"))
		g_exit_code = cd(data, cmd[1]);
	else if (!ft_strcmp(cmd[0], "pwd"))
		g_exit_code = pwd(data, fd);
	else if (!ft_strcmp(cmd[0], "export"))
		g_exit_code = export(data, cmd, fd);
	else if (!ft_strcmp(cmd[0], "unset"))
		g_exit_code = unset(data, cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		g_exit_code = env(data, fd);
	else if (!ft_strcmp(cmd[0], "exit"))
		g_exit_code = go_exit(data, cmd);
}
