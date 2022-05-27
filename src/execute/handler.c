/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:11:26 by soahn             #+#    #+#             */
/*   Updated: 2022/05/25 05:05:15 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

void	newline_handler(int signo)
{
	(void)signo;
}

void	execute_handler(int signo)
{
	if (signo == SIGUSR1)
	{
		signal(SIGINT, newline_handler);
		signal(SIGQUIT, newline_handler);
	}
}

void	main_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		g_exit_code = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_exit_code = 1;
		exit(1);
	}
}