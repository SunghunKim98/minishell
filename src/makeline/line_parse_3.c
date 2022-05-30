/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parse_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungkim <sungkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:08:06 by sungkim           #+#    #+#             */
/*   Updated: 2022/05/30 19:08:18 by sungkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_char_special(char ch)
{
	if (ch == '\"' || ch == '\'' || ch == ' ' || ch == '|'
		|| ch == '\0' || ch == '>' || ch == '<' || ch < 48
		|| (ch >= 58 && ch <= 64) || (ch >= 91 && ch <= 96)
		|| ch > 122)
		return (1);
	else
		return (0);
}

char	*get_env_by_key(char *key, t_data *p_data)
{
	char	*env_value;
	char	**p;
	int		i;
	char	**lst;

	p = p_data->env;
	i = -1;
	while (p[++i])
	{
		if (!ft_strncmp(p[i], key, ft_strlen(key)))
		{
			lst = ft_split(p[i], '=');
			env_value = advanced_strdup_no_free(lst[1]);
			break ;
		}
	}
	if (p[i] == 0)
		return (0);
	double_char_array_free(lst);
	return (env_value);
}

char	*parse_env_after_dollar(char **line, int *i, t_data *p_data)
{
	char	*k_env;
	char	*v_env;
	int		idx;

	idx = *i;
	while (!check_char_special((*line)[*i]))
		(*i)++;
	k_env = advanced_strlcpy((*line + idx), (*i - idx));
	v_env = get_env_by_key(k_env, p_data);
	free(k_env);
	return (v_env);
}
