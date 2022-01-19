/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:16:47 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/19 12:41:41 by rdanica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_str(char *string_free)
{
	if (string_free)
		free(string_free);
}

void	free_argv(char **argv)
{
	int	i;

	i = -1;
	if (argv && *argv != '\0')
	{
		if (*argv)
			while (argv[++i])
				free_str(argv[i]);
	}
	if (argv)
		free(argv);
}

void	ft_free_lst(t_lst **cmd)
{
	t_lst	*temp;

	while (cmd && *cmd && (*cmd)->back)
		*cmd = (*cmd)->back;
	while (*cmd)
	{
		temp = *cmd;
		*cmd = (*cmd)->next;
		free_argv(temp->field);
		free_argv(temp->redirs);
		free(temp);
	}
}
