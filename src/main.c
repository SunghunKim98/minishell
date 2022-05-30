/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:08:46 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 10:50:38 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int   g_exit_code;


void	error_util1()
{
	printf("\033[1A");
	printf("\033[10C");
	printf(" exit\n");
	exit(-1);
}


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

	// printf("processed_line: %s\n", processed_line);/

	set_command_count(processed_line, p_data);
	line_by_command = set_command_with_line(processed_line, p_data);


	// for (int i = 0; i < p_data->n_cmd; i++)
	// {
	// 	printf("%s\n", line_by_command[i]);
	// }


	get_command_from_line(line_by_command, p_data);

	return (SUCCESS);
}


int		start_with_the_line(char *line, t_data *p_data)
{
	if_pipe_opened(&line); 	// pipe가 열려있는 경우 예외처리 (즉, readline을 한번 더 하는 과정)
	add_history(line);

	if (!line_error_check(line))
		return FAIL;

	if (!line_parsing(line, p_data))
		return FAIL;


	t_args *p;
	t_redi *q;
	int	i = -1;
	while (++i < p_data->n_cmd)
	{
		printf("---------------\n");
		q = (p_data->cmd_lst[i]).redi;
		while (q)
		{
			printf("flag: %d\n", q->flag);
			printf("filename: %s\n", q->file_name);
			q = q->next;
		}
		printf("***************\n");
		p = (p_data->cmd_lst[i]).args;
		while (p)
		{
			printf("%s\n", p->str);
			p = p->next;
		}
	}
	return SUCCESS;
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

	// 여기서 환경변수좀 출력해보자.


	char **p;
	int	i = -1;

	p = (data.env);
	while (p[++i])
		printf("env: %s\n", p[i]);

	i = -1;

	p = (data.env_path);
	while (p[++i])
		printf("env_path: %s\n", p[i]);

	signal(SIGUSR1, execute_handler);
	while (1)
	{
		signal(SIGINT, main_handler);
		signal(SIGQUIT, SIG_IGN); // sigquit 무시
		line = readline("minishell$ ");
		// line = ft_strdup("cat << limit");
		if (!line)
			error_util1();
		else if (!*line)
			free(line);
		else
		{
			if (!start_with_the_line(line, &data))
				continue;
		}
		printf(PURPLE);
		printf("==============parsing end==============\n");
		ft_putstr_fd(WHITE, 1);
		execute_command(&data);
		// free_all(&data);
		system("leaks minishell");
	}


	return (0);
}
