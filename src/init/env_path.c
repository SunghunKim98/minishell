/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:13:48 by soahn             #+#    #+#             */
/*   Updated: 2022/05/18 15:19:32 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env_path(t_data *data, char **envp)
{
	while (*envp && ft_strncmp(*envp, "PATH", 4))
		++envp;
	if (!(*envp))
		return (FALSE);
	data->env_path = ft_split((*envp) + 5, ':');
	if (!(data->env_path))
		return (FALSE);
	return (TRUE);
}