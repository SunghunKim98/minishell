
#include "../include/minishell.h"

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
	p = (char*)malloc(sizeof(char) * (end - start + 3));
	tmp = p;
	*(tmp++) = '\"';
	while (start < end)
		*(tmp++) = *(start++);
	*(tmp++) = '\"';
	*tmp = 0;
	return (p);
}

char	*make_standard_line(char *line)
{
	char	*p;
	char	*tmp;
	char	*standard_line;

	p = line;
	standard_line = 0;
	while (1)
	{
		while (*p == ' ')
			p++;
		tmp = p;
		p = find_pointer_for_separation(tmp);
		standard_line = ft_strjoin(standard_line, strdup_with_pointer(tmp, p)); // strjoin안에서 free하겠지?
		if (*p == 0)
			break;
		else
			p++;
	}
	free(line);
	return (standard_line);
}