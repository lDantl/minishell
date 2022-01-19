/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:24:50 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/19 12:42:11 by rdanica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	validator(t_lst *cmd)
{
	int	i;

	while (cmd)
	{
		i = -1;
		while (cmd->field[++i])
		{
			if ((!ft_strcmp(cmd->field[i], ">>")
					|| !ft_strcmp(cmd->field[i], ">")
					|| !ft_strcmp(cmd->field[i], "<")
					|| !ft_strcmp(cmd->field[i], "<<"))
				&& !cmd->field[i + 1])
			{
				printf("syntax error near unexpected token\n");
				return (0);
			}
		}
		cmd = cmd->next;
	}
	return (1);
}

int	validator_for_pipe_and_redir2(char **mass, int *i)
{
	if (!mass[*i + 1])
	{
		printf("syntax error near unexpected token \'newline\'\n");
		return (0);
	}
	if (*mass[*i + 1] == '>' || *mass[*i + 1] == '<')
	{
		printf("syntax error near unexpected token \"%s\"\n", mass[*i]);
		return (0);
	}
	return (1);
}

int	validator_for_pipe_and_redir(char **mass)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	while (mass[++i])
	{
		if ((*mass[i] == '|' && !mass[i + 1]) || **mass == '|'
			|| (*mass[i] == '|' && (*mass[i + 1] == '|' || mass[i][j] == '|')))
		{
			printf("syntax error near unexpected token '|\'\n");
			return (0);
		}
		if (*mass[i] == '>' || *mass[i] == '<')
		{
			if (validator_for_pipe_and_redir2(mass, &i))
				continue ;
			return (0);
		}
	}
	return (1);
}
