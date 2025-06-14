/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:28:32 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/14 20:38:55 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int check_redirection(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}


int check_envirment(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void check_red_env(t_bash *bash)
{
	t_cmd *tmp = bash->s_cmd;

	while(tmp)
	{
		tmp->check_env = check_envirment(tmp->command);
		tmp->check_red = check_redirection(tmp->command);
		tmp = tmp->next;
	}
}


int	check_cmd4_1(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while(str[i])
	{
		x = 0;
		if (str[i] == '>')
		{
			while(str[i] && str[i] == '>')
			{
				i++;
				x++;
			}
			if (x > 2 || str[i] == '<')
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int	check_cmd4_2(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while(str[i])
	{
		x = 0;
		if (str[i] == '<')
		{
			while (str[i] && str[i] == '<')
			{
				i++;
				x++;
			}
			if (x > 2 || (x == 2 && str[i] == '>') )
				return (0);
		}
		else
			i++;
	}
	return (1);
}
