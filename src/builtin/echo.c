/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 08:58:09 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 20:32:10 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_word(char **words)
{
	int	i;

	i = -1;
	while (words[++i])
		;
	return (i);
}

static int	is_n_option(char *op)
{
	int	i;

	if (ft_strncmp(op, "-n", 2))
		return (FALSE);
	i = -1;
	while (op[++i])
		if (op[i] != 'n')
			return (FALSE);
	return (TRUE);
}

static void	echo_n(char **words, int word_cnt, int *fd)
{
	int	i;

	i = 1;
	while (is_n_option(words[++i]))
		;
	while (words[++i])
	{
		ft_putstr_fd(words[i], fd[WRITE]);
		if (i < (word_cnt - 1))
			ft_putstr_fd(" ", fd[WRITE]);
	}
}

int	echo(char **words, int *fd)
{
	int	word_cnt;
	int	i;

	word_cnt = count_word(words);
	if (word_cnt == 1)
	{
		ft_putendl_fd("", fd[WRITE]);
		return (0);
	}
	if (is_n_option(words[1]))
		echo_n(words, word_cnt, fd);
	else
	{
		i = 0;
		while (words[++i])
		{
			ft_putstr_fd(words[i], fd[WRITE]);
			if (i < (word_cnt - 1))
				ft_putstr_fd(" ", fd[WRITE]);
		}
		ft_putstr_fd("\n", fd[WRITE]);
	}
	return (0);
}
