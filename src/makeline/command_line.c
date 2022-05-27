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

		// int	k = -1;
		// while (one_command[++k])
		// 	printf("{%s}\n", one_command[k]);

		j = -1;
		while (one_command[++j])
			set_command_data(one_command[j], &(p_data->cmd_lst[i]));

	}
	// double_array_free(one_command);
}

char	**convert_line_to_command(char *line)
{
	char	**command;
	char	*p;
	char	*tmp;
	int		count;

	p = line;
	count = 0;
	while (*p)
		if (*(p++) == '\"')
			count++;

	command = (char**)malloc(sizeof(char*) * (count / 2 + 1));
	p = line;
	tmp = line;
	count = 0;
	while (*p)
	{
		if (*p == '\"')
		{
			tmp = ++p;
			while (*p != '\"')
				p++;
			command[count++] = make_str_by_pointer(tmp, p++);
		}
		if (*p == '>' || *p == '<')
			deal_with_redirection(command, count++, &p);
	}
	command[count] = 0;
	return (command);
}

char	*make_str_by_pointer(char *start, char *end)
{
	char	*result;
	int		i;

	if (start == end)
		return (0);
	result = (char*)malloc(sizeof(char) * (end - start + 1));
	i = -1;
	while (++i < end - start)
		result[i] = *(start + i);
	result[i] = 0;
	return result;
}

void	deal_with_redirection(char **command, int idx, char **p)
{
	char	*start;
	int		count;

	printf("here here\n");

	start = *p;
	count = 0;
	while (count < 2)
		if (*((*p)++) == '\"')
			count++;
	command[idx] = make_str_by_pointer(start, *p - 1);
}
