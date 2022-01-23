/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:31:58 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/23 14:34:29 by rdanica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lst	*new_cmd(char **massive, int i, int p, char **env)
{
	t_lst	*el;
	int		n;

	n = 0;
	el = (t_lst *)malloc(sizeof(t_lst));
	el->field = (char **)malloc(sizeof(char *) * p + 1);
	if (!el)
		return (NULL);
	el->next = NULL;
	el->back = NULL;
	el->redirs = NULL;
	el->field[n] = ft_find_path(massive[i], env);
	if (el->field[n] != 0)
	{
		n++;
		i++;
	}
	while (i != p)
		el->field[n++] = ft_strdup(massive[i++]);
	el->field[n] = NULL;
	return (el);
}

void	lst_add(t_lst **lst, t_lst *el)
{
	if (!el)
		return ;
	if (!(*lst))
	{
		*lst = el;
		return ;
	}
	el->back = *lst;
	(*lst)->next = el;
	*lst = el;
}

void	recording_to_lists(t_lst **cmd, char **massive, char **env)
{
	int	i;
	int	pipe;

	i = -1;
	pipe = 0;
	while (massive[++i])
	{
		if (massive[i][0] == '|' && massive[i][1] != '|')
		{
			lst_add(cmd, new_cmd(massive, pipe, i, env));
			pipe = i + 1;
		}
	}
	lst_add(cmd, new_cmd(massive, pipe, i, env));
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
}
