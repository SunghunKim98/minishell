/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungkim <sungkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:19:08 by sungkim           #+#    #+#             */
/*   Updated: 2022/05/30 19:19:09 by sungkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_split_one(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
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
	arr = NULL;
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
