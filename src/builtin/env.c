/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 06:23:54 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 19:18:38 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env(t_data *data, int *fd)
{
	char	**env;
	int		i;

	env = data->env;
	i = -1;
	while (env[++i])
		ft_putendl_fd(env[i], fd[WRITE]);
	return (0);
}
