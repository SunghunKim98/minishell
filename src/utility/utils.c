/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungkim <sungkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 08:46:58 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 19:24:34 by sungkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return ((-1) * s2[0]);
	if (!s2)
		return (s1[0]);
	while (s1[i] && s2[i])
	{
		if (s1[i] - s2[i] != 0)
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'\
	|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

void	ft_print_double_str(char **str)
{
	int	i;

	ft_putendl_fd("#########print double string###########", 1);
	i = -1;
	while (str[++i])
		ft_putendl_fd(str[i], 1);
	ft_putendl_fd("#######################################", 1);
}

int	get_double_string_len(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}
