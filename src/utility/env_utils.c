/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungkim <sungkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 02:57:05 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 19:17:42 by sungkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**set_data_env(int n_env, char **envp)
{
	int		i;
	char	**env;

	env = (char **)malloc(sizeof(char *) * (n_env + 1));
	malloc_error(env);
	i = -1;
	while (++i < n_env - 1)
		env[i] = ft_strdup(envp[i]);
	env[n_env - 1] = NULL;
	return (env);
}

int	get_env_index(t_data *data, char *key, int key_len)
{
	char	**prev_env;
	char	*now;
	int		i;

	prev_env = data->env;
	i = -1;
	while (prev_env[++i])
	{
		now = prev_env[i];
		while (now && ft_strncmp(now, "=", 1)
			&& ft_strncmp(now, key, key_len))
			++now;
		if (!now || !ft_strncmp(now, "=", 1))
			continue ;
		return (i);
	}
	return (-1);
}
