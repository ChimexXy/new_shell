/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:28:38 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/14 21:04:07 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_double_pointer_tk(char **arr, int p)
{
	if (!arr)
		return;
	while (p >= 0)
	{
		free(arr[p]);
		p--;
	}
	free(arr);
}

int	check_tokenizer(char c)
{
	if (c == ' ' || c == '\t' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	skip_quotes(char *cmd, int i)
{
	char	quote;

	quote = cmd[i];
	i++;
	while (cmd[i] && cmd[i] != quote)
		i++;
	if (cmd[i] == quote)
		i++;
	return (i);
}

int	count_word_tk(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		while (cmd[i] && check_tokenizer(cmd[i]))
			i++;
		if (cmd[i])
		{
			count++;
			while (cmd[i] && !check_tokenizer(cmd[i]))
			{
				if (cmd[i] == '\'' || cmd[i] == '\"')
					i = skip_quotes(cmd, i);
				else
					i++;
			}
		}
	}
	return (count);
}

char	*get_word(char *cmd)
{
	int		i;
	int		start;
	char	*word;

	i = 0;
	while (cmd[i] && check_tokenizer(cmd[i]))
		i++;
	start = i;
	while (cmd[i] && !check_tokenizer(cmd[i]))
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			i = skip_quotes(cmd, i);
		else
			i++;
	}
	word = ft_substr(cmd, start, i - start);
	return (word);
}

char	**tokenizer(char *cmd)
{
	int		word_count;
	char	**ret;
	int		i;
	int		x;

	if (!cmd)
		return (NULL);
	word_count = count_word_tk(cmd);
	ret = malloc(sizeof(char *) * (word_count + 1));
	if (!ret)
		return (NULL);
	i = 0;
	x = 0;
	while (x < word_count)
	{
		ret[x] = get_word(cmd);
		if (!ret[x])
		{
			free_double_pointer_tk(ret, x);
			return (NULL);
		}
		x++;
	}
	ret[x] = NULL;
	return (ret);
}

