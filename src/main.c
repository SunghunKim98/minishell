/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:08:46 by soahn             #+#    #+#             */
/*   Updated: 2022/05/26 14:53:15 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int   g_exit_code;
/*
char *read_command_line()
{
	char *line;

	line = readline("minishell$ ");
	if (!line)
	{
		printf("\033[1A"); // 커서를 위로 한 줄 올린다.
		printf("\033[10C"); // 커서를 10만큼 앞으로 전진시킨다.
		printf("exit\n");
		exit(-1);
	}
}

void read_line(t_data *data)
{
	char *line;

	line = read_command_line();
	printf("[%s]\n", line);
}
*/
/*
void signalHandler(int sig)
{
	if (sig==SIGINT)
	{
		printf("this program will stop in 3 seconds...\n");
		sleep(3);
		exit(0);
	}
	if (sig==SIGQUIT)
	{
		printf("signal SIGQUIT\n");
	}
}
*/

void	error_util1()
{
	printf("\033[1A");
	printf("\033[10C");
	printf(" exit\n");
	exit(-1);
}

/*
    make_line.c - start
*/

char	*find_pointer_for_separation(char *start)
{
	char	*p;
	int		flag_sq;
	int		flag_dq;

	p = start;
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
		if (*p == ' ' || *p == '|' || *p == '>' || *p == '<')
			if (!flag_sq && !flag_dq)
				break;
		p++;
	}
	return (p);
}

char	*strdup_with_pointer(char *start, char *end)
{
	char	*p;
	char	*tmp;

	if (*start == '|' || *start == '<' || *start == '>')
	{
		p = (char*)malloc(sizeof(char) * (2));
		tmp = p;
		*(tmp++) = *start;
		*tmp = 0;
		return (p);
	}
	p = (char*)malloc(sizeof(char) * (end - start + 3));
	tmp = p;
	*(tmp++) = '\"';
	while (start < end)
		*(tmp++) = *(start++);
	*(tmp++) = '\"';
	*tmp = 0;
	return (p);
}

char	*make_standard_line(char *line)
{
	char	*p;
	char	*tmp;
	char	*standard_line;

	p = line;
	standard_line = 0;
	while (1)
	{
		while (*p == ' ')
			p++;
		tmp = p;
		p = find_pointer_for_separation(tmp);
		standard_line = ft_strjoin(standard_line, strdup_with_pointer(tmp, p)); // strjoin안에서 free하겠지?
		if (*p == 0)
			break;
		else
			p++;
	}
	free(line);
	return (standard_line);
}

/*
    make_line.c - end
*/


void	if_pipe_opened(char **line)
{
	(void)line;
	// 사실 void가 int로 return해서 처리를 해야 할 듯
	return ;
}


void	set_command_count(char *line, t_data *p_data)
{
	char	*p;
	int		count;

	p = line;
	count = 0;
	while (*p)
		if (*(p++) == '|')
			count++;
	p_data->n_cmd = count + 1;
}

char	**malloc_double_char(int size)
{
	char	**p;
	int		i;

	p = (char**)malloc(sizeof(char*) * (size + 1));
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

	p = (char*)malloc(sizeof(char) * (size + 1));
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

char	**set_command_with_line(char *line, t_data *p_data)
{
	char	**command;
	char	*p;
	char	*tmp;
	int		i;
	int		j;

	p = line;
	command = malloc_double_char(p_data->n_cmd);
	i = -1;
	tmp = p;
	while (1)
	{
		if (*p == '|' || *p == 0)
		{
			j = -1;
			command[++i] = malloc_single_char(p - tmp);
			while (++j < p - tmp)
				command[i][j] = *(tmp + j);
			if (*p == 0)
				break ;
			else
				tmp = p + 1;
		}
		p++;
	}
	return (command);
}

char	*make_str_by_pointer(char *start, char *end)
{
	char	*result;
	int		i;

	if (start == end)
		return (0);
	result = (char*)malloc(sizeof(char) * (end - start + 1));
	i = -1;
	while (++i < end - start)
		result[i] = *(start + i);
	result[i] = 0;
	return result;
}

void	deal_with_redirection(char **command, int idx, char **p)
{
	char	*start;
	int		count;

	printf("here here\n");

	start = *p;
	count = 0;
	while (count < 2)
		if (*((*p)++) == '\"')
			count++;
	command[idx] = make_str_by_pointer(start, *p - 1);
}

char	**convert_line_to_command(char *line)
{
	char	**command;
	char	*p;
	char	*tmp;
	int		count;

	p = line;
	count = 0;
	while (*p)
		if (*(p++) == '\"')
			count++;

	command = (char**)malloc(sizeof(char*) * (count / 2 + 1));
	p = line;
	tmp = line;
	count = 0;
	while (*p)
	{
		if (*p == '\"')
		{
			tmp = ++p;
			while (*p != '\"')
				p++;
			command[count++] = make_str_by_pointer(tmp, p++);
		}
		if (*p == '>' || *p == '<')
			deal_with_redirection(command, count++, &p);
	}
	command[count] = 0;
	return (command);
}


t_args	*init_cmd_node(char *command)
{
	t_args	*p;

	p = (t_args*)malloc(sizeof(t_args));
	p->next = 0;
	p->str = ft_strdup(command);

	return (p);
}

void	set_cmd_redi_flag(char *arr, t_redi *p)
{
	if (ft_strlen(arr) == 1)
	{
		if (arr[0] == '>')
			p->flag = 1;
		else
			p->flag = 3;
	}
	else if (ft_strlen(arr) == 2)
	{
		if (ft_strncmp(">>", arr, 2) == 0)
			p->flag = 2;
		else if (ft_strncmp("<<", arr, 2) == 0)
			p->flag = 4;
		else
			exit(-1); // error ex. >< <>
	}
	else
		exit(-1);
}

void	free_split_one(char **arr)
{
	int	i;

	i = -1;
	while (++i)
		free(arr[i]);
	free(arr);
}

t_redi	*init_cmd_redi(char *command)
{
	t_redi	*p;
	char	**arr;

	p = (t_redi*)malloc(sizeof(t_redi));
	p->next = 0;
	arr = ft_split(command, '\"');

	set_cmd_redi_flag(arr[0], p);
	p->file_name = ft_strdup(arr[1]);
	
	free_split_one(arr);

	return (p);
}

void	set_t_args(t_args *new_node, t_args **node)
{
	t_args	*p;

	if (*node == 0)
		*node = new_node;
	else
	{
		p = *node;
		while (p->next)
			p = (p)->next;
		p->next = new_node;
	}
}

void	set_t_redi(t_redi *new_node, t_redi **node)
{
	t_redi	*p;

	if (*node == 0)
		*node = new_node;
	else
	{
		p = *node;
		while (p->next)
			p = (p)->next;
		p->next = new_node;
	}
	
}

void	set_command_data(char *command, t_cmd *cmd)
{
	if (command[0] == '>' || command[0] == '<')
		set_t_redi(init_cmd_redi(command), &((*cmd).redi));
	else
		set_t_args(init_cmd_node(command), &((*cmd).args));

}

t_cmd	*init_cmd_lst(t_data *p_data)
{
	int		i;
	t_cmd	*p;

	p = (t_cmd*)malloc(sizeof(t_cmd) * (p_data->n_cmd));
	i = -1;
	while (++i < p_data->n_cmd)
	{
		p[i].redi = 0;
		p[i].args = 0;
	}
	return (p);
}

void	get_command_from_line(char **command_arr, t_data *p_data)
{
	int		i;
	char	**one_command;
	int		j;

	p_data->cmd_lst = init_cmd_lst(p_data);
	i = -1;
	while (++i < p_data->n_cmd)
	{
		one_command = convert_line_to_command(command_arr[i]);

		// int	k = -1;
		// while (one_command[++k])
		// 	printf("{%s}\n", one_command[k]);
		
		j = -1;
		while (one_command[++j])
			set_command_data(one_command[j], &(p_data->cmd_lst[i]));
		
	}
	// double_array_free(one_command);
}

int		line_parsing(char *line, t_data *p_data)
{
	char	*processed_line;
	char	**line_by_command;

	processed_line = make_standard_line(line);

	// printf("processed_line: %s\n", processed_line);/

	set_command_count(processed_line, p_data);
	line_by_command = set_command_with_line(processed_line, p_data);


	// for (int i = 0; i < p_data->n_cmd; i++)
	// {
	// 	printf("%s\n", line_by_command[i]);
	// }
	

	// 여기서부터 다시 봐야 함.
	get_command_from_line(line_by_command, p_data);

	return (0);
}

void	start_with_the_line(char *line, t_data *p_data)
{
	if_pipe_opened(&line); 	// pipe가 열려있는 경우 예외처리 (즉, readline을 한번 더 하는 과정)

	add_history(line);

	if (line_parsing(line, p_data))
		return ;
	

	// t_args *p;
	// t_redi *q;
	// int	i = -1;
	// while (++i < p_data->n_cmd)
	// {
	// 	printf("******%d*****\n", p_data->n_cmd);
	// 	printf("---------------\n");
	// 	q = (p_data->cmd_lst[i]).redi;
	// 	while (q)
	// 	{
	// 		printf("flag: %d\n", q->flag);
	// 		printf("filename: %s\n", q->file_name);
	// 		q = q->next;
	// 	}
	// 	printf("***************\n");
	// 	p = (p_data->cmd_lst[i]).args;
	// 	while (p)
	// 	{
	// 		printf("%s\n", p->str);
	// 		p = p->next;
	// 		// printf("null ?");
	// 	}
	// }

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
		signal(SIGQUIT, SIG_IGN); // sigquit 무시
		line = readline("minishell$ ");
		// line = ft_strdup("pwd");
		if (!line)
			error_util1();
		else if (!*line)
			free(line);
		else
			start_with_the_line(line, &data);

		execute_command(&data);
	}


	return (0);
}