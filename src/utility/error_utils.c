/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungkim <sungkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:18:04 by sungkim           #+#    #+#             */
/*   Updated: 2022/05/30 19:18:57 by sungkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*error_util0(void)
{
	printf("\033[1A");
	printf("\033[10C");
	printf(" exit\n");
	return (0);
}

void	error_util1(void)
{
	printf("\033[1A");
	printf("\033[10C");
	printf(" exit\n");
	exit(1);
}
