#include "../../include/minishell.h"

char	*find_pointer_for_separation(char *start)
{
	char	*p;
	int		flag_sq;
	int		flag_dq;

	p = start;
	flag_sq = 0;
	flag_dq = 0;
	while (*p)
	{
		if (*p == '\'' && flag_dq == 0 && flag_sq)
            flag_sq = 0;
        else if ((*p == '\'' && flag_dq == 0 && !flag_sq))
            flag_sq = 1;
        else if (*p == '\"' && flag_sq == 0 && flag_dq)
            flag_dq = 0;
        else if (*p == '\"' && flag_sq == 0 && !flag_dq)
            flag_dq = 1;
		if (*p == ' ' || *p == '|' || *p == '>' || *p == '<')
			if (!flag_sq && !flag_dq)
				break;
		p++;
	}
	return (p);
}

char	*strdup_with_pointer(char *start, char *end)
{
	char	*p;
	char	*tmp;

	if (*start == '|' || *start == '<' || *start == '>')
	{
		p = (char*)malloc(sizeof(char) * (2));
		tmp = p;
		*(tmp++) = *start;
		*tmp = 0;
		return (p);
	}
	else if ((*start == '\"' && *(end - 1) == '\"') || (*start == '\'' && *(end - 1) == '\''))
	{
		if ((start++) == (end--) - 1)
			return (0);
	}
	p = (char*)malloc(sizeof(char) * (end - start + 3));
	tmp = p;
	*(tmp++) = '\"';
	while (start < end)
		*(tmp++) = *(start++);
	*(tmp++) = '\"';
	*tmp = 0;
	return (p);
}

int		check_if_sep(char ch)
{
	if (!ch)
		return (1);
	if (ch == ' ' || ch == '|' || ch == '>' || ch == '<')
		return (1);
	return (0);
}

char	*trim_space_line(char *line, int start)
{
	int		i;
	char	*line_0;
	char	*line_1;
	char	*new_line;

	if (line[start] != ' ')
		return (line);
	i = start;
	if (line[i] == ' ')
		i++;
	line_0 = advanced_strlcpy(line, start);
	line_1 = advanced_strdup_no_free(line + i);
	new_line = ft_strjoin(line_0, line_1);
	free(line);
	free(line_0);
	free(line_1);
	return (new_line);
}
