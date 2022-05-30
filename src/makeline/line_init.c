#include "../../include/minishell.h"

void	init_utils(int *start, int *divider, int *flag)
{
	*start = 0;
	*divider = 0;
	*flag = 0;
}

void	init_variables(int *i, int *j, int *flag_sq, int *flag_dq)
{
	*i = 0;
	*j = 0;
	*flag_sq = 0;
	*flag_dq = 0;
}

t_args	*init_cmd_node(char *command)
{
	t_args	*p;

	p = (t_args*)malloc(sizeof(t_args));
	p->next = 0;
	p->str = ft_strdup(command);

	return (p);
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

t_cmd	*init_cmd_lst(t_data *p_data)
{
	int		i;
	t_cmd	*p;

	p = (t_cmd*)malloc(sizeof(t_cmd) * (p_data->n_cmd));
	if (!p)
		exit(-1);
	i = -1;
	while (++i < p_data->n_cmd)
	{
		p[i].redi = 0;
		p[i].args = 0;
	}
	return (p);
}
