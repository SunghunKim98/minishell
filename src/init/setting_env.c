/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 03:13:25 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 10:28:51 by soahn            ###   ########.fr       */
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

int	parse_env_home(t_data *data, char **envp)
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
	data->n_env = get_double_string_len(envp);
	data->env = set_data_env(data->n_env, envp); // 이거 동적할당으로 저장해줘야 나중에 오류 안남!!
	parse_env_home(data, data->env); // for cd ~
	parse_env_path(data, data->env);  // for exec
}
