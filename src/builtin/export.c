/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:53:21 by soahn             #+#    #+#             */
/*   Updated: 2022/05/23 03:38:28 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

int	export(t_data *data, char **cmd, int *fd)
{
	int	i;

	i = 1;
	if (!cmd[1]) // only export
	{
		print_export(data, fd);
		return (0);	
	}
	while (cmd[++i])
	{
		
	}
}