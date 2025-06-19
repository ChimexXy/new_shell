/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:34:56 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/19 10:34:08 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int select_struct1(t_bash *bash, char *cmd)
{
	bash->num_cmd = count_pipes(cmd);
	bash->commands = ft_strdup(cmd);
	bash->args_pip = ft_split(cmd, '|');
	free(cmd);
	return (1);
}

int select_struct2(t_bash *bash)
{
	int i;
	t_cmd *node;
	i = 0;
	while (i < bash->num_cmd)
	{
		node = lst_new_add(bash->args_pip[i]);
		if (!node)
			return (0);
		lst_add_back(&bash->s_cmd, node);
		i++;
	}
	if (!red_parse(bash))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int select_struct3(t_bash *bash)
{
	t_cmd *tmp = bash->s_cmd;

	while (tmp)
	{
		if (!tmp->command)
			return (0);
		tmp->arguments = tokenizer(tmp->command);
		tmp = tmp->next;
	}
	return (1);
}

void select_struct(t_bash *bash, char *cmd)
{
	bash->commands = NULL;
	bash->args_pip = NULL;
	bash->num_cmd = 0;
	bash->s_cmd = NULL;
	if (!select_struct1(bash, cmd))
		return ;
	if (!select_struct2(bash))
		return ;
	if (!select_struct3(bash))
		return ;
	check_red_env(bash);
	parse_redirection(bash);
	parse_envirement(bash);
}

void print_dou(char **env)
{
	int j = 0;
	while (env[j])
	{
		printf("%s\n", env[j]);
		j++;
	}
}

int main(int ac, char **av, char **env)
{
	t_bash *bash;
	char *cmd;

	bash = malloc(sizeof(t_bash));
	if (!bash)
		return (1);
	(void)ac;
	(void)av;

	while (1)
	{
		cmd = readline("minishell$ ");
		add_history(cmd);
		if (!cmd || !check_cmd(cmd))
		{
			printf("exit\n");
			free(cmd);
			break ;
		}
		select_struct(bash, cmd);

		t_cmd *tmp = bash->s_cmd;
		while (tmp)
		{
			int i = 0;
			// t_env *tmp_env = tmp->s_env;
			while (tmp->arguments[i])
			{
			    printf("arg: %s\n",tmp->arguments[i]);
			    // printf("env value: %s\n", tmp_env->value);
			    i++;
			}
			tmp = tmp->next;
		}

		free_bash(bash);
	}
	return (0);
}