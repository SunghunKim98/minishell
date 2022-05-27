/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:53:21 by soahn             #+#    #+#             */
/*   Updated: 2022/05/27 06:41:06 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

int		check_new(t_data *data, char **env, int key_len)
{
	char	**prev_env;
	char	*now;
	int		i;
	int		j;

	prev_env = data->env;
	i = -1;
	while (prev_env[++i])
	{
		now = prev_env[i];
		while (now && ft_strncmp(now, "=", 1) && ft_strncmp(now, env[0], key_len)) // key 찾기
			++now;
		if (!now || !ft_strncmp(now, "=", 1)) // 끝까지 갔거나 =를 만난 경우
			continue ;
		return (FALSE);
	}
	return (TRUE);
}

void	add_new_env(t_data *data, char **env)
{
	int		len;
	int		i;
	char	**new_env;
	char	*key_with_equal;

	len = -1;
	while (data->env[++len])
		;
	// prev len = len + 1 + 1, new len = len + 1 + 1 + 1
	new_env = (char **)malloc(sizeof(char *) * (len + 3));
	malloc_error(new_env);
	new_env[len + 2] = NULL;
	i = 0;
	while (new_env[++i])
		new_env[i - 1] = ft_strdup(data->env[i - 1]);
	key_with_equal = ft_strjoin(env[0], "=");
	new_env[i - 1] = ft_strdup(ft_strjoin(key_with_equal, env[1]));
	free_split_one(data->env);
	data->env = new_env;
}

int		incorrect_env(char *key)
{
	int	i;

	if (!ft_strcmp(key, "_"))
		return (TRUE);
	i = 0;
	if (ft_isalpha(key[i]))
		return (TRUE);
	while (ft_isalnum(key[i]))
		++i;
	if (key[i] == '\0')
		return (FALSE);
	return (TRUE);
}

void	add_env(t_data *data, char **env, int key_len)
{
	char	**prev_env;
	char	*now;
	int		i;
	char	*new;

	prev_env = data->env;
	i = -1;
	while (prev_env[++i])
	{
		now = prev_env[i];
		while (now && ft_strncmp(now, "=", 1) && ft_strncmp(now, env[0], key_len)) // key 찾기
			++now;
		if (!now || !ft_strncmp(now, "=", 1)) // 끝까지 갔거나 =를 만난 경우
			continue ;
		break ; // 찾았다 (오마이걸)
	}
	if (!prev_env[i])
	{
		new = ft_strdup(prev_env[i]);
		free(prev_env[i]);
		prev_env[i] = new;
	}
}

int	export(t_data *data, char **cmd, int *fd)
{
	int		i;
	char	**env;
	int		key_len;

	i = 1;
	if (!cmd[1]) // only export
	{
		print_export(data, fd);
		return (0);
	}
	while (cmd[++i])
	{
		env = env_dict(cmd[i]);
		if (incorrect_env(env[0]))
		{
			error_message_arg("export", env[0], "not a valid identifier");
			g_exit_code = 1;
		}
		key_len = ft_strlen(env[0]);
		if (check_new(data, env, key_len))
			add_new_env(data, env);
		else
			add_env(data, env, key_len);
		free_split_one(env);
	}
	return (g_exit_code);
}
