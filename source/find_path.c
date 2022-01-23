/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:11:13 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/23 18:00:11 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	final_find(t_lst *cmd, char **env)
{
	char	*temp;
	char	*addr;

	while (cmd)
	{
		if (cmd->field[0])
		{
			addr = cmd->field[0];
			if (*env)
				temp = ft_find_path(cmd->field[0], env);
			else
				temp = ft_strdup(cmd->field[0]);
			if (temp == NULL)
			{
				cmd = cmd->next;
				continue ;
			}
			cmd->field[0] = temp;
			free (addr);
			temp = NULL;
			cmd = cmd->next;
		}
	}
}