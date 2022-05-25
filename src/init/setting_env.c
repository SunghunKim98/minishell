/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 03:13:25 by soahn             #+#    #+#             */
/*   Updated: 2022/05/23 22:10:23 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parse_env_path(t_data *data, char **envp)
{
	int		i;

	while (*envp && ft_strncmp(*envp, "PATH", 4))
		++envp;
	if (!(*envp))
		return (FALSE);
	data->env_path = ft_split((*envp) + 5, ':');
	i = -1;
	while (data->env_path[++i])
		data->env_path[i] = ft_strjoin(data->env_path[i], "/");
	if (!(data->env_path))
		return (FALSE);
	return (TRUE);
}

int_fast16_t	parse_env_home(t_data *data, char **envp)
{
	while (*envp && ft_strncmp(*envp, "HOME", 4))
		++envp;
	if (!(*envp))
		return (FALSE);
	data->home = (*envp) + 5;
	if (!(data->home))
		return (FALSE);
	return (TRUE);
}

void	setting_env_things(t_data *data, char **envp)
{
	data->env = envp;
	parse_env_home(data, envp);
	parse_env_path(data, envp);
}