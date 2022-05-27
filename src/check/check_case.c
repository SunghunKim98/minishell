#include "../../include/minishell.h"

int		check_case_pipe(char *p)
{
	if (*p == '|' && *(p + 1) == '|')
		return (deal_error(0));
	return SUCCESS;
}

int		check_case_redi(char *p)
{
	char *q;
	int	redi_count;

	if (*p == '>' || *p == '<')
	{
		q = p;
		redi_count = 0;
		while (*p == *q && *q)
		{
			redi_count++;
			q++;
		}
		if (redi_count > 2)
			return (deal_error(1));
		while (*q == ' ')
			q++;
		if (!(*q))
			return (deal_error(1));
	}
	return SUCCESS;
}

int		check_case_other(char *p)
{
	if (*p == ';' || *p == '\\')
		return (deal_error(2));
	return SUCCESS;
}

int		check_different_case(char *p)
{
	if (!check_case_pipe(p))
		return FAIL;
	else if (!check_case_redi(p))
		return FAIL;
	else if (!check_case_other(p))
		return FAIL;
	else
		return TRUE;
}

int		check_quoto_closed(int flag_sq, int flag_dq)
{
	if (!flag_sq && !flag_dq)
		return SUCCESS;
	else
	{
		printf("There's unclose quote\n");
		return FAIL;
	}
}
