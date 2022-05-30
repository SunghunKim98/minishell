/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:08:46 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 19:03:56 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int   g_exit_code;

char	*make_buffer(void)
{
	char	*new_buffer;

	new_buffer = (char *)malloc(sizeof(char) * BUFF_SIZE);
	if (new_buffer == NULL)
		exit(-1);
	return (new_buffer);
}

char	select_quoto_type(char *buffer, int length)
{
	int	i;

	i = -1;
	while (++i < length)
		if (buffer[i] == '\"')
			return ('\'');
	return ('\"');
}

int		line_parsing(char *line, t_data *p_data)
{
	char	*processed_line;
	char	**line_by_command;

	processed_line = make_standard_line(line, p_data);
	set_command_count(processed_line, p_data);
	line_by_command = set_command_with_line(processed_line, p_data);
	free(processed_line);
	get_command_from_line(line_by_command, p_data);
	double_char_array_free(line_by_command);
	return (SUCCESS);
}

int		start_with_the_line(char *line, t_data *p_data)
{
	int		pipe_result;

	pipe_result = check_pipe_opened(&line);
	add_history(line);
	if (!pipe_result)
	{
		free(line);
		return (FAIL);
	}
	if (!line_error_check(line))
		return (FAIL);
	if (!line_parsing(line, p_data))
		return (FAIL);
	return (SUCCESS);
}

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;

	if (!argc || !argv)
		return (0);
	g_exit_code = 0;
	init_all(&data);
	setting_env_things(&data, envp);
	signal(SIGUSR1, execute_handler);
	while (1)
	{
		signal(SIGINT, main_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell$ ");
		if (!line)
			error_util1();
		else if (!*line)
			free(line);
		else
			if (!start_with_the_line(line, &data))
				continue;

		execute_command(&data);

		free_now_cmd(&data);
		free_all(&data);
		system("leaks minishell");
	}

	return (0);
}
