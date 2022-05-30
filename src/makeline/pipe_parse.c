#include "../../include/minishell.h"

extern int   g_exit_code;

int		check_pipe_opened(char **line)
{
	char	*extend_line;
	char	*origin;

	if (if_pipe_opened(*line))
		return (0);
	if (check_pipe_can_get_input(*line))
	{
		// 여기서 무슨 시그널을 줌!
		extend_line = get_more_line();
		if (!extend_line)
		{
			deal_error(4);
			return (0);
		}
		origin = advanced_strdup(*line);
		*line = ft_strjoin(origin, extend_line);
		if (!*line)
			exit(-1);
		free(origin);
		free(extend_line);
	}
	return (1);
}

int		check_pipe_can_get_input(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] == '|')
			break ;
	if (!line[i++])
		return (0);
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (1);
	return (0);
}

char	*get_more_line(void)
{
	char	*new_line;

	while (1)
	{
		new_line = readline("pipe> ");
		if (!new_line)
			return (error_util0());
		if (ft_strlen(new_line) > 0)
			break;
		free(new_line);
	}
	return (new_line);
}

int		if_pipe_opened(char *line)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (line[++i])
		if (line[i] == '|')
			break ;
	if (!line[i])
		return (0);
	while (++j < i)
		if (check_char_special(line[j]) == 0)
			return (0);
	deal_error(3);
	return (1);
}
