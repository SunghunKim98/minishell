/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 03:42:54 by soahn             #+#    #+#             */
/*   Updated: 2022/05/30 19:18:59 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_code;

int	is_arg_digit(char *arg)
{
	int	i;
	int	end;

	i = 0;
	end = 0;
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == ' ')
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i + end] && ft_isdigit(arg[i + end]))
		end++;
	if (arg[i + end] == '\0' && end <= 19)
		return (TRUE);
	return (FALSE);
}

int	get_unsigned_char_code(char *arg, unsigned char *code)
{
	long				sign;
	unsigned long long	result;
	size_t				i;

	sign = 1;
	result = 0;
	i = 0;
	while (arg[i] != '\0' && ft_isspace(arg[i]) == 1)
		i++;
	if (arg[i] == '-')
		sign = -1;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i] != '\0' && arg[i] >= '0' && arg[i] <= '9')
	{
		result = result * 10 + (arg[i] - '0');
		i++;
	}
	if (result > 9223372036854775807)
		return (FALSE);
	*code = (unsigned char)(sign * result);
	return (TRUE);
}

long long	atolonglong(const char *str)
{
	long				sign;
	unsigned long long	result;
	size_t				i;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] != '\0' && ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	go_exit(t_data *data, char **cmd)
{
	unsigned char	code;

	if (data->n_cmd == 1)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (!cmd[1])
		exit(0);
	if (is_arg_digit(cmd[1]) && get_unsigned_char_code(cmd[1], &code))
	{
		if (!cmd[2])
		{
			g_exit_code = (int)code;
			exit(g_exit_code);
		}
		error_message("exit", "too many arguments");
		return (g_exit_code);
	}
	error_message_arg("exit", cmd[1], "numeric argument required");
	exit(255);
}
