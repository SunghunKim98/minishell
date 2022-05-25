/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:04:28 by soahn             #+#    #+#             */
/*   Updated: 2022/05/19 06:45:12 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 리스트로 된 명령어 + 옵션을 배열로 저장 */

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
	struct stat file_stat; // from <sys/stat.h>

	if (ft_strncmp(cmd_path, "/", 1)) // /로 시작하지 않으면 return false
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
	return (TRUE); // 에러 없이 파일을 정상 조회한 경우 true 리턴
}

/* PATH 환경변수로 경로 가져오기, 이미 경로로 준 경우 바로 리턴 */
//stat 함수 이용
//인자로 들어온 cmd는 명령어 (ls, df 등)
char	*get_path(char **paths, char *cmd) // todo: data에 PATH 파싱해서 저장
{
	int		i;
	char	*cmd_path;
	struct stat file_stat; // from <sys/stat.h>

	if (is_path_cmd(cmd))
		return (cmd);
	cmd_path = NULL;
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd); //todo: paths저장할 때 맨 끝에 '/' 붙여서 저장 했는지 확인
		// printf("cmd_path: %s\n", cmd_path);
		if (!stat(cmd_path, &file_stat)) // 존재하는 파일이면 0 리턴
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	return (cmd_path);
}