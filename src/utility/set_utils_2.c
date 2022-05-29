#include "../../include/minishell.h"

extern int g_exit_code;

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
	char	*p;
	char	*tmp;
	int		i;
	int		j;

	p = line;
	command = malloc_double_char(p_data->n_cmd);
	i = -1;
	tmp = p;
	while (1)
	{
		if (*p == '|' || *p == 0)
		{
			j = -1;
			command[++i] = malloc_single_char(p - tmp);
			while (++j < p - tmp)
				command[i][j] = *(tmp + j);
			if (*p == 0)
				break ;
			else
				tmp = p + 1;
		}
		p++;
	}
	return (command);
}

void	set_command_count(char *line, t_data *p_data)
{
	char	*p;
	int		count;

	p = line;
	count = 0;
	while (*p)
		if (*(p++) == '|')
			count++;
	p_data->n_cmd = count + 1;
}

void	set_quoto_flag(char ch, int *flag_sq, int *flag_dq)
{
	if (ch == '\'')
		*flag_sq ^= 1;
	else
		*flag_dq ^= 1;
}
