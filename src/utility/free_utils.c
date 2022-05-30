#include "../../include/minishell.h"

void	free_split_one(char **arr)
{
	int	i;

	i = -1;
	while (++i)
		free(arr[i]);
	free(arr);
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

void	clear_cmd_args(t_args *args)
{
	t_args	*cur;
	t_args	*del;

	cur = args;
	while (cur != NULL)
	{
		if (cur->str)
			free(cur->str);
		del = cur;
		cur = cur->next;
		free(del);
	}
}

void	clear_cmd_redi(t_redi *redi)
{
	t_redi	*cur;
	t_redi	*del;

	cur = redi;
	while (cur != NULL)
	{
		if (cur->file_name)
			free(cur->file_name);
		del = cur;
		cur = cur->next;
		free(del);
	}
}
