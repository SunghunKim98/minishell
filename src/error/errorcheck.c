/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungkim <sungkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:00:17 by sungkim           #+#    #+#             */
/*   Updated: 2022/05/30 19:02:16 by sungkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	line_error_check(char *line)
{
	if (!check_error_case_0(line))
		return (FAIL);
	if (!check_error_case_1(line))
		return (FAIL);
	return (SUCCESS);
}

int	check_error_case_0(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (FAIL);
	else
		return (SUCCESS);
}

int	check_error_case_1(char *line)
{
	char	*p;
	int		flag_sq;
	int		flag_dq;

	p = line;
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
		else if (!flag_sq && !flag_dq)
			if (!check_different_case(p))
				return (FAIL);
		p++;
	}
	return (check_quoto_closed(flag_sq, flag_dq));
}

int	deal_error(int i)
{
	printf("There's something Error_%d\n", i);
	return (FAIL);
}
