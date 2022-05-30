#include "../../include/minishell.h"

void	get_command_from_line(char **command_arr, t_data *p_data)
{
	int		i;
	char	**one_command;
	int		j;

	p_data->cmd_lst = init_cmd_lst(p_data);
	i = -1;
	while (++i < p_data->n_cmd)
	{
		one_command = convert_line_to_command(command_arr[i]);
		j = -1;
		while (one_command[++j])
			set_command_data(one_command[j], &(p_data->cmd_lst[i]));
	}
	double_char_array_free(one_command);
}

char	**convert_line_to_command(char *line)
{
	char	**command;
	int		i;
	int		prev;
	int		post;

	command = make_cmd_lst(line);
	i = -1;
	prev = 0;
	post = 0;
	while (check_if_quote(line, &post))
	{
		command[++i] = malloc_single_char(post - prev - 1);
		ft_strlcpy(command[i], line + prev + 1, post++ - prev);
		prev = post;
	}
	return (command);
}

char	**make_cmd_lst(char *line)
{
	int		count;
	int		idx;
	char	**command;

	count = 0;
	idx = 0;
	while (check_if_quote(line, &idx))
	{
		idx++;
		count++;
	}
	command = malloc_double_char(count);
	return (command);
}

int		check_if_quote(char *line, int *idx)
{
	while (line[*idx])
	{
		if (line[*idx] == '\'')
		{
			++(*idx);
			while (line[*idx] != '\'' && line[*idx] != 0)
				(*idx)++;
			break ;
		}
		else if (line[*idx] == '\"')
		{
			++(*idx);
			while (line[*idx] != '\"' && line[*idx] != 0)
				(*idx)++;
			break ;
		}
		else
			(*idx)++;
	}
	if (line[*idx] == '\'' || line[*idx] == '\"')
		return (TRUE);
	return (FALSE);
}
