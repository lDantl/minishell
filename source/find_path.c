/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:11:13 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/23 13:41:25 by rdanica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	qwerty(t_lst *cmd, char **env)
{
	char	*temp;
	char	*addr;

	while (cmd)
	{
		if (cmd->field[0])
		{
			addr = cmd->field[0];
			temp = ft_find_path(cmd->field[0], env);
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