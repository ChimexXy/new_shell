/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:28:19 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/15 17:57:36 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_env(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
	{
		printf("minishell: export: `=': not a valid identifier\n");
		return (0);
	}
	while (str[i])
	{
		if(str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

t_env	*alloc_env_node(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

void	add_env_node(t_cmd *cmd, t_env *new)
{
	t_env	*last;

	if (!cmd->s_env)
		cmd->s_env = new;
	else
	{
		last = cmd->s_env;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	parse_env_key_value(t_env *env, char *arg)
{
	int	m;
	int	len;

	m = 0;
	len = ft_strlen(arg);
	while(arg[m] && arg[m] != '=')
		m++;
	env->key = ft_substr(arg, 0, m);
	m++;
	if (m >= len)
		env->value = ft_strdup("");
	else
		env->value = ft_substr(arg, m, len - m);
}

void	parse_env_file_key(t_cmd *cmd)
{
	int		j;
	t_env	*new;

	j = 0;
	while (cmd->arguments[j])
	{
		if (check_env(cmd->arguments[j]))
		{	
			new = alloc_env_node();
			if (!new)
				return ;
			parse_env_key_value(new, cmd->arguments[j]);
			add_env_node(cmd, new);
		}
		j++;
	}
}

int	parse_envirement(t_bash *bash)
{
	t_cmd	*tmp;

	tmp = bash->s_cmd;
	while (tmp)
	{
		if (tmp->check_env == 1)
			parse_env_file_key(tmp);
		tmp = tmp->next;
	}
	return (1);
}

