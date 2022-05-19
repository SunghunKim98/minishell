/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 03:13:25 by soahn             #+#    #+#             */
/*   Updated: 2022/05/19 03:36:36 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parse_env_path(t_data *data, char **envp)
{
	while (*envp && ft_strncmp(*envp, "PATH", 4))
		++envp;
	if (!(*envp))
		return (FALSE);
	data->env_path = ft_split((*envp) + 5, ':');
	if (!(data->env_path))
		return (FALSE);
	return (TRUE);
}

void	setting_env_things(t_data *data, char **envp)
{
	parse_env_path(data, envp);
}