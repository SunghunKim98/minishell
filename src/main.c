/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:08:46 by soahn             #+#    #+#             */
/*   Updated: 2022/05/19 03:45:14 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


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
	else if ((*start == '\"' && *(end - 1) == '\"') || (*start == '\'' && *(end - 1) == '\''))
	{
		if ((start++) == (end--) - 1)
			return (0);
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

void	init_utils(int *start, int *divider, int *flag)
{
	*start = 0;
	*divider = 0;
	*flag = 0;
}

char	*advanced_strdup(char *line)
{
	char	*new_line;

	new_line = ft_strdup(line);
	if (!new_line)
		exit(-1);
	free(line);
	return (new_line);
}

char	*advanced_strdup_no_free(char *line)
{
	char	*new_line;

	new_line = ft_strdup(line);
	if (!new_line)
		exit(-1);
	return (new_line);
}

int		check_if_sep(char ch)
{
	if (!ch)
		return (1);
	if (ch == ' ' || ch == '|' || ch == '>' || ch == '<')
		return (1);
	return (0);
}

char	*advanced_strlcpy(char *line, int start)
{
	char	*new_line;

	new_line = (char *)malloc(sizeof(char) * (start + 1));
	if (new_line == NULL)
		exit(-1);
	ft_strlcpy(new_line, line, start + 1);
	return (new_line);
}

char	*trim_space_line(char *line, int start)
{
	int		i;
	char	*line_0;
	char	*line_1;
	char	*new_line;

	if (line[start] != ' ')
		return (line);
	i = start;
	if (line[i] == ' ')
		i++;
	line_0 = advanced_strlcpy(line, start);
	line_1 = advanced_strdup_no_free(line + i);

	new_line = ft_strjoin(line_0, line_1);
	// 여기서 line_0, line_1 free를 join에서 하는가? => 아닌 것 같다.
	free(line);
	free(line_0);
	free(line_1);
	return (new_line);
}

char	*make_line_without_space(char *line, int *start)
{
	char	*new_line;

	new_line = advanced_strdup(line);

	while (check_if_sep(new_line[*start]))
	{
		new_line = trim_space_line(new_line, *start);
		while (check_if_sep(new_line[*start]))
		{
			if (new_line[*start] == ' ' || !new_line[*start])
				break;
			(*start)++;
		}
		if (!new_line[*start])
			break;
	}
	return (new_line);
}

void	set_divider(char *line, int start, int *divider)
{
	int		flag_sq;
	int		flag_dq;
	int		p;

	flag_sq = 0;
	flag_dq = 0;
	while (line[start])
	{
		p = line[start];
		if (p == '\'' && flag_dq == 0 && flag_sq)
            flag_sq = 0;
        else if ((p == '\'' && flag_dq == 0 && !flag_sq))
            flag_sq = 1;
        else if (p == '\"' && flag_sq == 0 && flag_dq)
            flag_dq = 0;
        else if (p == '\"' && flag_sq == 0 && !flag_dq)
            flag_dq = 1;
		if (p == ' ' || p == '|' || p == '>' || p == '<')
			if (!flag_sq && !flag_dq)
				break;
		start++;
	}
	*divider = start;
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

char	**separate_by_div(char *line, int start, int divider)
{
	char	**list;

	list = malloc_double_char(3);
	list[0] = malloc_single_char(start);
	list[1] = malloc_single_char(divider - start);
	list[2] = malloc_single_char(ft_strlen(line) - divider);
	ft_strlcpy(list[0], line, start + 1);
	ft_strlcpy(list[1], line + start, divider - start + 1);
	ft_strlcpy(list[2], line + divider, ft_strlen(line) - divider + 1);
	free(line);
	return (list);
}

void	init_variables(int *i, int *j, int *flag_sq, int *flag_dq)
{
	*i = 0;
	*j = 0;
	*flag_sq = 0;
	*flag_dq = 0;
}

char	*make_buffer(void)
{
	char	*new_buffer;

	new_buffer = (char *)malloc(sizeof(char) * BUFF_SIZE);
	if (new_buffer == NULL)
		exit(-1);
	return (new_buffer);
}

char	*advanced_itoa(int n)
{
	char	*new_line;

	new_line = ft_itoa(n);
	if (!new_line)
		exit(-1);
	return (new_line);
}

int		check_char_special(char ch)
{
	if (ch == '\"' || ch == '\'' || ch == ' ' || ch == '|' 
		|| ch == '\0' || ch == '>' || ch == '<')
		return (1);
	else
		return (0);
}

t_env	*check_env_list(char *key, t_data *p_data)
{
	t_env	*p;

	p = p_data->env_deq->head;
	while (p)
	{
		if (!ft_strncmp(key, p->key, ft_strlen(key) + 1))
			return (p);
		p = p->next;
	}
	return (0);
}

char	*get_env_by_key(char *key, t_data *p_data)
{
	t_env	*p;
	char	*env_value;

	p = check_env_list(key, p_data);
	if (!p)
		return (0);
	env_value = advanced_strdup_no_free(p->value);
	return (env_value);
}

char	*parse_env_after_dollar(char **line, int *i, t_data *p_data)
{
	char	*k_env;
	char	*v_env;
	int		idx;

	idx = *i;
	while (!check_char_special((*line)[*i]))
		(*i)++;
	k_env = advanced_strlcpy((*line + idx), (*i - idx));
	v_env = get_env_by_key(k_env, p_data);
	free(k_env);
	return (v_env);
}

// extern t_exit	g_exit;

void	set_env(char **line, int *i, t_data *p_data)
{
	char	*line_0;
	char	*line_1;
	char	*env;
	char	*tmp;

	line_0 = advanced_strlcpy(*line, *i);
	*i += 1;
	if ((*line)[*i] == '?')
	{
		(*i)++;
		env = advanced_itoa(10);
		// env = advanced_itoa(g_exit.code); // exit_code ??
	}
	else
		env = parse_env_after_dollar(line, i, p_data);
	line_1 = advanced_strdup_no_free(*line + *i);
	*i = ft_strlen(line_0);
	tmp = ft_strjoin(line_0, env);
	free(*line);
	*line = ft_strjoin(tmp, line_1);
	free(line_0);
	free(line_1);
	free(env);
	free(tmp);
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

char	*return_new_line(char *buffer, int length)
{
	char	*line;
	char	quote;

	if (length >= BUFF_SIZE - 1)
	{
		free(buffer);
		return (0);
	}
	line = (char *)malloc(sizeof(char) * (length + 3));
	if (!line)
		exit(-1);
	quote = select_quoto_type(buffer, length);
	line[0] = quote;
	ft_strlcpy(line + 1, buffer, length + 1);
	line[length + 1] = quote;
	line[length + 2] = '\0';
	free(buffer);
	return (line);
}

void	set_quoto_flag(char ch, int *flag_sq, int *flag_dq)
{
	if (ch == '\'')
		*flag_sq ^= 1;
	else
		*flag_dq ^= 1;
}

char	*fillin_buf(char *origin, t_data *p_data)
{
	int		i;
	int		j;
	char	*new_line;
	int		flag_sq;
	int		flag_dq;
	char	*buffer;

	init_variables(&i, &j, &flag_sq, &flag_dq);
	new_line = advanced_strdup_no_free(origin);

	buffer = make_buffer();
	while (new_line[i] && (j < BUFF_SIZE - 1))
	{
		if (new_line[i] == '\'' && !flag_dq)
			set_quoto_flag(new_line[i++], &flag_sq, &flag_dq);
		else if (new_line[i] == '\"' && !flag_sq)
			set_quoto_flag(new_line[i++], &flag_sq, &flag_dq);
		else if (!flag_sq && new_line[i] == '$')
			set_env(&new_line, &i, p_data);
		else
			buffer[j++] = new_line[i++];
	}

	printf("[buff, j]: %s, %d\n", buffer, j);

	free(new_line);
	return (return_new_line(buffer, j)); // -> 여기까지 완료...!
}

char	*join_strings(char *line, char **separator, int *start)
{
	char	*tmp;
	char	*new_line;

	tmp = ft_strjoin(separator[0], line);
	if (!tmp)
		exit(-1);
	free(line);
	*start = ft_strlen(tmp);
	new_line = ft_strjoin(tmp, separator[2]);
	if (!new_line)
		exit(-1);
	free(tmp);
	return (new_line);
}

void	double_char_array_free(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

char	*trim_line(int *start, int divider, char *line, t_data *p_data)
{
	char	**result;
	char	*new_line;

	result = separate_by_div(line, *start, divider);

	printf("[result: %s]\n", result[1]);

	new_line = fillin_buf(result[1], p_data);
	if (!new_line)
		exit(-1);
	
	printf("[new_line: %s]\n", new_line);

	new_line = join_strings(new_line, result, start); // 여기서 문제
	double_char_array_free(result);
	return (new_line);
}

char	*make_standard_line(char *line, t_data *p_data)
{
	int		start;
	int		divider;
	int		flag;
	char	*new_line;

	init_utils(&start, &divider, &flag);
	new_line = advanced_strdup(line);
	while (1)
	{
		new_line = make_line_without_space(new_line, &start);
		set_divider(new_line, start, &divider);

		printf("divider: %d\n", divider);

		if (!new_line[divider])
			flag = 1;
		new_line = trim_line(&start, divider, new_line, p_data);

		printf("<new_line: %s>\n", new_line);

		if (!new_line)
			return (0);
		if (flag)
			break ;

	}
	return (new_line);
}

/*
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

		printf("[$$ %c %c]\n", *tmp, *p);

		standard_line = ft_strjoin(standard_line, strdup_with_pointer(tmp, p)); // strjoin안에서 free하겠지?
		if (*p == 0)
			break;
		else
			p++;
	}
	free(line);
	return (standard_line);
}
*/

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

		int	k = -1;
		while (one_command[++k])
			printf("{%s}\n", one_command[k]);
		
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

	printf("1\n");

	processed_line = make_standard_line(line, p_data);

	printf("processed_line: %s\n", processed_line);


	set_command_count(processed_line, p_data);
	line_by_command = set_command_with_line(processed_line, p_data);


	for (int i = 0; i < p_data->n_cmd; i++)
	{
		printf("cmd_%d: %s\n", i, line_by_command[i]);
	}
	

	get_command_from_line(line_by_command, p_data);

	return (SUCCESS);
}

int		check_quoto_closed(int flag_sq, int flag_dq)
{
	if (!flag_sq && !flag_dq)
		return SUCCESS;
	else
	{
		printf("There's unclose quote\n");
		return FAIL;
	}
}


int		deal_error(int i)
{
	printf("There's something Error_%d\n", i);
	return FAIL;
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
	
	setting_env_things(&data, envp);
	
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			error_util1();
		else if (!*line)
			free(line);
		else
		{
			if (!start_with_the_line(line, &data))
				continue;
		}
		// execute_command(&data);
	}


	return (0);
}