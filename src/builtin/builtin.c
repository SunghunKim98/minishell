/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 08:43:56 by soahn             #+#    #+#             */
/*   Updated: 2022/05/19 03:21:49 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit")) //todo: handle register cmd
		return (TRUE);
	return (FALSE);	
}

void	exec_builtin(t_data *data, char *cmd, int i)
{
	(void)data;
	(void)cmd;
	(void)i;
	
	//todo
	// if (!ft_strcmp(cmd, "echo"))
	// 	echo(data);
	// else if (!ft_strcmp(cmd, "cd"))
	// 	cd(data);
	// else if (!ft_strcmp(cmd, "pwd"))
	// 	pwd(data);
	// else if (!ft_strcmp(cmd, "export"))
	// 	export(data);
	// else if (!ft_strcmp(cmd, "unset"))
	// 	unset(data);
	// else if (!ft_strcmp(cmd, "env"))
	// 	env(data);
	// else if (!ft_strcmp(cmd, "exit"))
	// 	go_exit(data);
}