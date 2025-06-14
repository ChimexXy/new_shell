/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:48:47 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/14 20:30:15 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd *lst_new_add(char *arg)
{
	t_cmd *new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->command = ft_strdup(arg);
	new->arguments = NULL;
	new->check_red = 0;
	new->check_env = 0;
	new->s_red = NULL;
	new->s_env = NULL;
	new->next = NULL;
	return (new);
}
