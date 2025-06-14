/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:28:35 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/14 21:20:25 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_rd(char c)
{
	if (!c)
		return (0);
	if (c == '>' || c == '<' 
		|| c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	check_rd1(char c)
{
	if (!c)
		return (0);
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_sp(char c)
{
	if (!c)
		return (0);
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	count_redirection(char *cmd)
{
	int	i;
	int	red;

	i = 0;
	red = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			if (cmd[i + 1] == '>' || cmd[i + 1] == '<')
				i += 2;
			else
				i++;
			red++;
		}
		else
			i++;
	}
	return (red);
}


t_red	*alloc_s_red_node(void)
{
	t_red	*new;

	new = malloc(sizeof(t_red));
	if (!new)
		return (NULL);
	new->file = NULL;
	new->type = 0;
	new->check_flag = 0;
	new->next = NULL;
	return (new);
}


void	redirection_types(t_cmd *cmd)
{
	int		j;
	t_red	*tmp;

	j = 0;
	tmp = cmd->s_red;
	while (cmd->command[j] && tmp)
	{
		if (cmd->command[j] == '>')
		{
			if (cmd->command[j + 1] == '>')
			{
				tmp->type = APPEND;
				j += 2;
			}
			else
			{
				tmp->type = OUTPUT;
				j++;
			}
			tmp = tmp->next;
		}
		else if (cmd->command[j] == '<')
			j++; // pass '<', we'll handle it in redirection_types1
		else
			j++;
	}
}


void	redirection_types1(t_cmd *cmd)
{
	int		j;
	t_red	*tmp;

	j = 0;
	tmp = cmd->s_red;
	while (cmd->command[j] && tmp)
	{
		if (cmd->command[j] == '<')
		{
			if (cmd->command[j + 1] == '<')
			{
				tmp->type = HERE_DOC;
				j += 2;
			}
			else
			{
				tmp->type = INPUT;
				j++;
			}
			tmp = tmp->next;
		}
		else
			j++;
	}
}


void	redirection_files(t_cmd *cmd)
{
	int		j;
	int		start;
	t_red	*tmp;

	j = 0;
	tmp = cmd->s_red;
	while (cmd->command[j] && tmp)
	{
		if (check_rd1(cmd->command[j]))
		{
			if (check_rd1(cmd->command[j + 1]))
				j += 2;
			else
				j++;
			while (check_sp(cmd->command[j]))
				j++;
			start = j;
			while (cmd->command[j] && !check_rd(cmd->command[j]))
				j++;
			if (start < j)
				tmp->file = ft_substr(cmd->command, start, j - start);
			tmp = tmp->next;
		}
		else
			j++;
	}
}

void	add_redirection_node(t_cmd *cmd)
{
	t_red	*new;
	t_red	*last;

	new = alloc_s_red_node();
	if (!new)
		return ;
	if (!cmd->s_red)
		cmd->s_red = new;
	else
	{
		last = cmd->s_red;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

int	alloc_redirection_list(t_cmd *cmd)
{
	int	n_red;
	int	x;

	n_red = count_redirection(cmd->command);
	x = 0;
	while (x < n_red)
	{
		add_redirection_node(cmd);
		x++;
	}
	return (1);
}

int	parse_redirection(t_bash *bash)
{
	t_cmd	*tmp;

	tmp = bash->s_cmd;
	while (tmp)
	{
		if (tmp->check_red == 1)
		{
			if (!alloc_redirection_list(tmp))
				return (0);
			redirection_types(tmp);
			redirection_types1(tmp);
			redirection_files(tmp);
		}
		tmp = tmp->next;
	}
	return (1);
}


