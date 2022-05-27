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
