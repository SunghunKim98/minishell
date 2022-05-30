/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:53:21 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 19:24:42 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

void	add_new_env(t_data *data, char **env)
{
	int		len;
	int		i;
	char	**new_env;
	char	*key_with_equal;
	char	**tmp;

	len = -1;
	while (data->env[++len])
		;
	new_env = (char **)malloc(sizeof(char *) * (len + 2));
	malloc_error(new_env);
	new_env[len + 2] = NULL;
	i = -1;
	while (++i < len)
		new_env[i] = ft_strdup(data->env[i]);
	key_with_equal = ft_strjoin(env[0], "=");
	new_env[i] = ft_strdup(ft_strjoin(key_with_equal, env[1]));
	free(key_with_equal);
	tmp = data->env;
	data->env = new_env;
	double_char_array_free(tmp);
	data->n_env++;
}

void	replace_env(t_data *data, char *env, int replace_idx)
{
	int		i;
	char	**new_env;
	char	**tmp;

	new_env = (char **)malloc(sizeof(char *) * (data->n_env + 1));
	i = -1;
	while (data->env[++i])
	{
		if (i == replace_idx)
			new_env[i] = ft_strdup(env);
		else
			new_env[i] = ft_strdup(data->env[i]);
	}
	tmp = data->env;
	data->env = new_env;
	double_char_array_free(tmp);
}

static void	save_env(t_data *data, char **env, char **cmd, int i)
{
	int		key_len;
	int		replace_idx;

	key_len = ft_strlen(env[0]);
	replace_idx = get_env_index(data, env[0], key_len);
	if (replace_idx < 0)
		add_new_env(data, env);
	else
		replace_env(data, cmd[i], replace_idx);
}

int	export(t_data *data, char **cmd, int *fd)
{
	int		i;
	char	**env;

	if (!cmd[1])
		return (print_export(data, fd));
	i = 0;
	while (cmd[++i])
	{
		env = env_dict(cmd[i]);
		if (incorrect_env(env[0]))
		{
			error_message_arg("export", cmd[i], "not a valid identifier");
			g_exit_code = 1;
		}
		else
			save_env(data, env, cmd, i);
		double_char_array_free(env);
	}
	return (g_exit_code);
}
