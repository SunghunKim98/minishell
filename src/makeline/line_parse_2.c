#include "../../include/minishell.h"

char	*trim_line(int *start, int divider, char *line, t_data *p_data)
{
	char	**result;
	char	*new_line;

	result = separate_by_div(line, *start, divider);

	new_line = fillin_buf(result[1], p_data);
	if (!new_line)
		exit(-1);

	new_line = join_strings(new_line, result, start); // 여기서 문제
	double_char_array_free(result);
	return (new_line);
}

char	**separate_by_div(char *line, int start, int divider)
{
	char	**list;

	list = malloc_double_char(3);
	list[0] = malloc_single_char(start);
	list[1] = malloc_single_char(divider - start);
	list[2] = malloc_single_char(ft_strlen(line) - divider);
	ft_strlcpy(list[0], line, start + 1);
	ft_strlcpy(list[1], line + start, divider - start + 1);
	ft_strlcpy(list[2], line + divider, ft_strlen(line) - divider + 1);
	free(line);
	return (list);
}

char	*fillin_buf(char *origin, t_data *p_data)
{
	int		i;
	int		j;
	char	*new_line;
	int		flag_sq;
	int		flag_dq;
	char	*buffer;

	init_variables(&i, &j, &flag_sq, &flag_dq);
	new_line = advanced_strdup_no_free(origin);

	buffer = make_buffer();
	while (new_line[i] && (j < BUFF_SIZE - 1))
	{
		if (new_line[i] == '\'' && !flag_dq)
			set_quoto_flag(new_line[i++], &flag_sq, &flag_dq);
		else if (new_line[i] == '\"' && !flag_sq)
			set_quoto_flag(new_line[i++], &flag_sq, &flag_dq);
		else if (!flag_sq && new_line[i] == '$')
			set_env(&new_line, &i, p_data);
		else
			buffer[j++] = new_line[i++];
	}

	free(new_line);
	return (return_new_line(buffer, j));
}

char	*join_strings(char *line, char **separator, int *start)
{
	char	*tmp;
	char	*new_line;

	tmp = ft_strjoin(separator[0], line);
	if (!tmp)
		exit(-1);
	free(line);
	*start = ft_strlen(tmp);
	new_line = ft_strjoin(tmp, separator[2]);
	if (!new_line)
		exit(-1);
	free(tmp);
	return (new_line);
}

char	*return_new_line(char *buffer, int length)
{
	char	*line;
	char	quote;

	if (length >= BUFF_SIZE - 1)
	{
		free(buffer);
		return (0);
	}
	line = (char *)malloc(sizeof(char) * (length + 3));
	if (!line)
		exit(-1);
	quote = select_quoto_type(buffer, length);
	line[0] = quote;
	ft_strlcpy(line + 1, buffer, length + 1);
	line[length + 1] = quote;
	line[length + 2] = '\0';
	free(buffer);
	return (line);
}
