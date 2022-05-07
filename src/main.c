/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:08:46 by soahn             #+#    #+#             */
/*   Updated: 2022/05/08 00:59:39 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	minishell(char *line, t_data *data)
{
	if (parsing(line, &data) == ERROR)
		ft_putendl_fd("syntax error near unexpected token", STDERR_FILENO);
}

int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_data	data;

	init_all(argc, argv, envp, &data);
	while (TRUE)
	{
		line = readline("minishell$ ");
		minishell(line, &data);
			
	}
	return (0);
}