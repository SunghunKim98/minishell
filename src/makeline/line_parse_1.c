#include "../../include/minishell.h"


char	*make_standard_line(char *line, t_data *p_data)
{
	int		start;
	int		divider;
	int		flag;
	char	*new_line;

	init_utils(&start, &divider, &flag);
	new_line = advanced_strdup(line);
	while (1)
	{
		new_line = make_line_without_space(new_line, &start);
		set_divider(new_line, start, &divider);

		if (!new_line[divider])
			flag = 1;
		new_line = trim_line(&start, divider, new_line, p_data);

		if (!new_line)
			return (0);
		if (flag)
			break ;

	}
	return (new_line);
}

char	*make_line_without_space(char *line, int *start)
{
	char	*new_line;

	new_line = advanced_strdup(line);

	while (check_if_sep(new_line[*start]))
	{
		new_line = trim_space_line(new_line, *start);
		while (check_if_sep(new_line[*start]))
		{
			if (new_line[*start] == ' ' || !new_line[*start])
				break;
			(*start)++;
		}
		if (!new_line[*start])
			break;
	}
	return (new_line);
}

void	set_divider(char *line, int start, int *divider)
{
	int		flag_sq;
	int		flag_dq;
	int		p;

	flag_sq = 0;
	flag_dq = 0;
	while (line[start])
	{
		p = line[start];
		if (p == '\'' && flag_dq == 0 && flag_sq)
            flag_sq = 0;
        else if ((p == '\'' && flag_dq == 0 && !flag_sq))
            flag_sq = 1;
        else if (p == '\"' && flag_sq == 0 && flag_dq)
            flag_dq = 0;
        else if (p == '\"' && flag_sq == 0 && !flag_dq)
            flag_dq = 1;
		if (p == ' ' || p == '|' || p == '>' || p == '<')
			if (!flag_sq && !flag_dq)
				break;
		start++;
	}
	*divider = start;
}
