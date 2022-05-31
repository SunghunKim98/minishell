/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:04:28 by soahn             #+#    #+#             */
/*   Updated: 2022/05/31 19:56:40 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**to_arr(t_args *cmd)
{
	t_args	*tmp;
	int		cnt;
	int		i;
	char	**cmd_arr;

	tmp = cmd;
	cnt = 0;
	while (tmp)
	{
		tmp = tmp->next;
		cnt++;
	}
	cmd_arr = (char **)malloc(sizeof(char *) * (cnt + 1));
	malloc_error(cmd_arr);
	i = -1;
	tmp = cmd;
	while (++i < cnt)
	{
		cmd_arr[i] = ft_strdup(tmp->str);
		malloc_error(cmd_arr[i]);
		tmp = tmp->next;
	}
	cmd_arr[i] = NULL;
	return (cmd_arr);
}

int	is_path_cmd(char *cmd_path)
{
	struct stat	file_stat;

	if (ft_strncmp(cmd_path, "/", 1))
		return (FALSE);
	if (stat(cmd_path, &file_stat) == ERROR)
	{
		error_message(cmd_path, strerror(errno));
		exit(_NO_COMMAND);
	}
	if (S_ISDIR(file_stat.st_mode))
	{
		error_message(cmd_path, strerror(errno));
		exit(_CANT_EXEC);
	}
	return (TRUE);
}

/* PATH 환경변수로 경로 가져오기, 이미 경로로 준 경우 바로 리턴 */
char	*get_path(char **paths, char *cmd)
{
	int			i;
	char		*cmd_path;
	struct stat	file_stat;

	if (is_path_cmd(cmd))
		return (cmd);
	cmd_path = NULL;
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!stat(cmd_path, &file_stat))
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	return (cmd_path);
}
