/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:43:55 by soahn             #+#    #+#             */
/*   Updated: 2022/05/23 22:15:11 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int		get_env_size(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		;
	return (i);
}

void	sort_env_str(char **str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	while (str[i])
	{
		j = i;
		while (str[j] && (ft_strcmp(str[j - 1], str[j]) > 0))
		{
			tmp = str[j];
			str[j] = str[j - 1];
			str[j - 1] = tmp;
			j--;
			if (j <= 0)
				break ;
		}
		i++;
	}
}

void	print_export(t_data *data, int *fd) //환경변수 목록 정렬해서 출력 (웩...정렬;;)
{
	int		i;
	char	**sorted_env;
	int		len;

	len = get_env_size(data->env);
	sorted_env = (char **)malloc(sizeof(char *) * (len + 1));
	malloc_error(sorted_env);
	sorted_env[len] = NULL;
	sort_env_str(sorted_env);
	i = -1;
	while (sorted_env[++i])
		ft_putendl_fd(sorted_env[i], fd[WRITE]);
	i = -1;
	while (sorted_env[++i])
		free(sorted_env[i]);
	free(sorted_env);
}
