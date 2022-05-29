/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 21:24:22 by soahn             #+#    #+#             */
/*   Updated: 2022/05/29 03:39:16 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

void	unset_env(t_data *data, char *key, int key_len)
{
	int		i;
	int		j;
	int		unset_index;
	char	**new_env;
	char	**tmp;

	
	unset_index = get_env_index(data, key, key_len);
	data->n_env--;
	new_env = (char **)malloc(sizeof(char *) * (data->n_env + 1));
	i = -1;
	j = 0;
	while (data->env[++i])
	{
		if (i == unset_index)
			continue ;
		new_env[j] = ft_strdup(data->env[i]);
		j++;
	}
	tmp = data->env;
	data->env = new_env;
	double_char_array_free(tmp);
}

int	unset(t_data *data, char **cmd)
{
	int		i;
	char	*key;
	int		key_len;

	i = 0;
	while (cmd[++i])
	{
		key = cmd[i];
		key_len = ft_strlen(key);
		if (incorrect_env(key))
		{
			error_message_arg("unset", key, "not a valid identifier");
			g_exit_code = 1;
		}
		else
			unset_env(data, key, key_len);
	}
	return (g_exit_code);
}