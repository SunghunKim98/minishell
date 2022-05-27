#include "../../include/minishell.h"

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
