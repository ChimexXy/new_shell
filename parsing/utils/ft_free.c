/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:15:28 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/14 21:15:53 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_redirections(t_bash *bash)
{
	t_red *tmp;
	t_red *current;

	current = bash->s_cmd->s_red;
	while (current)
	{
		tmp = current->next;
		free(current->file);
		free(current);
		current = tmp;
	}
	bash->s_cmd->s_red = NULL;
}

void	free_envs(t_bash *bash)
{
	t_env *tmp;
	t_env *current;

	current = bash->s_cmd->s_env;
	while (current)
	{
		tmp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = tmp;
	}
	bash->s_cmd->s_env = NULL;
}

void	free_cmds(t_bash *bash)
{
	t_cmd *tmp;
	t_cmd *current;
	int j;

	current = bash->s_cmd;
	while (current)
	{
		tmp = current->next;
		free(current->command);
		if (current->arguments)
		{
			j = 0;
			while (current->arguments[j])
			{
				free(current->arguments[j]);
				j++;
			}
			free(current->arguments);
		}
		free_redirections(bash);
		free_envs(bash);
		free(current);
		current = tmp;
	}
	bash->s_cmd = NULL;
}

void	free_bash(t_bash *bash)
{
	int i;

	if (!bash)
		return ;

	if (bash->commands)
		free(bash->commands);

	if (bash->args_pip)
	{
		i = 0;
		while (bash->args_pip[i])
		{
			free(bash->args_pip[i]);
			i++;
		}
		free(bash->args_pip);
	}

	free_cmds(bash);
}
