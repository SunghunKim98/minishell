/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:19:56 by sungkim           #+#    #+#             */
/*   Updated: 2022/05/30 17:42:41 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

void	set_env(char **line, int *i, t_data *p_data)
{
	char	*line_0;
	char	*line_1;
	char	*env;
	char	*tmp;

	line_0 = advanced_strlcpy(*line, *i);
	*i += 1;
	if ((*line)[*i] == '?')
	{
		(*i)++;
		env = advanced_itoa(g_exit_code);
	}
	else
		env = parse_env_after_dollar(line, i, p_data);
	line_1 = advanced_strdup_no_free(*line + *i);
	*i = ft_strlen(line_0);
	tmp = ft_strjoin(line_0, env);
	free(*line);
	*line = ft_strjoin(tmp, line_1);
	free(line_0);
	free(line_1);
	free(env);
	free(tmp);
}

char	**set_command_with_line(char *line, t_data *p_data)
{
	char	**command;
	int		i;
	int		prev;
	int		post;

	i = -1;
	command = malloc_double_char(p_data->n_cmd);
	prev = 0;
	set_divider(line, prev, &post);
	while (++i < p_data->n_cmd)
	{
		while (line[post] != '|' && line[post])
		{
			if (check_if_sep(line[post]) || (prev != post))
				post++;
			set_divider(line, post, &post);
		}
		command[i] = malloc_single_char(post - prev);
		ft_strlcpy(command[i], line + prev, (post - prev + 1));
		post += 1;
		prev = post;
	}
	return (command);
}

void	set_command_count(char *line, t_data *p_data)
{
	int		count;
	int		idx_sep;

	idx_sep = 0;
	count = 0;
	set_divider(line, idx_sep, &idx_sep);
	while (line[idx_sep])
	{
		while (line[idx_sep] && line[idx_sep] != '|')
		{
			++idx_sep;
			set_divider(line, idx_sep, &idx_sep);
		}
		if (line[idx_sep] == 0)
			break ;
		count++;
		idx_sep++;
		set_divider(line, idx_sep, &idx_sep);
	}
	p_data->n_cmd = count + 1;
}

void	set_quoto_flag(char ch, int *flag_sq, int *flag_dq)
{
	if (ch == '\'')
		*flag_sq ^= 1;
	else
		*flag_dq ^= 1;
}
