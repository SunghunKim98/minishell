/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungkim <sungkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:19:29 by sungkim           #+#    #+#             */
/*   Updated: 2022/05/30 19:19:38 by sungkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**malloc_double_char(int size)
{
	char	**p;
	int		i;

	p = (char **)malloc(sizeof(char *) * (size + 1));
	if (p == NULL)
	{
		printf("Malloc Error\n");
		exit(1);
	}
	i = -1;
	while (++i < size + 1)
		p[i] = 0;
	return (p);
}

char	*malloc_single_char(int size)
{
	char	*p;
	int		i;

	p = (char *)malloc(sizeof(char) * (size + 1));
	if (p == NULL)
	{
		printf("Malloc Error\n");
		exit(1);
	}
	i = -1;
	while (++i < size + 1)
		p[i] = 0;
	return (p);
}
