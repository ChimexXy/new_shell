/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:57:02 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/14 20:40:43 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int red_parse(t_bash *bash)
{
	int		j;
	t_cmd	*tmp;

	tmp = bash->s_cmd;
	while (tmp)
	{
		j = ft_strlen(tmp->command) - 1;
		while (j >= 0 && (tmp->command[j] == ' ' || tmp->command[j] == '\t'))
			j--;
		if (j >= 0 && (tmp->command[j] == '>' || tmp->command[j] == '<'))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int check_sin_dou(char *cmd)
{
	int		i;
	char	c;
	int		state;

	i = 0;
	state = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
		{
			c = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != c)
				i++;
			if (!cmd[i])
				return (0);
		}
		i++;
	}
	return (1);
}


// int	check_sin_dou(char *cmd)
// {
// 	int		i;
// 	int		num;
// 	char	c;

// 	i = 0;
// 	num = 0;
// 	if (!cmd)
// 		return (0);
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == 34 || cmd[i] == 39)
// 		{
// 			num++;
// 			c = cmd[i];
// 			i++;
// 			while (cmd[i] != c && cmd[i])
// 				i++;
// 			if (cmd[i] == c)
// 				num++;
// 			if (num % 2 != 0)
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

