/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_herdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 20:21:07 by jtawanda          #+#    #+#             */
/*   Updated: 2022/01/21 21:07:06 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_herdoc_count(t_msh *msh)
{
	t_lst	*temp_cmd;
	int		i;
	int		count;

	temp_cmd = msh->cmd;
	count = 0;
	while (temp_cmd)
	{
		if (temp_cmd->redirs)
		{
			i = 0;
			while (temp_cmd->redirs[i])
			{
				if (!ft_strcmp(temp_cmd->redirs[i], "<<"))
					count++;
				i += 2;
			}
		}
		temp_cmd = temp_cmd->next;
	}
	return (count);
}

static void	ft_herdoc_input(t_lst *temp_cmd, t_msh *msh, int *rednum)
{
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	while (temp_cmd->redirs[i])
	{
		if (!ft_strcmp(temp_cmd->redirs[i], "<<"))
		{
			while (1)
			{
				line = readline("\033[0;32m> \033[0;29m");
				if (!ft_strcmp(temp_cmd->redirs[1], line))
				{
					free(line);
					break ;
				}
				ft_putendl_fd(line, msh->herdocfd[*rednum][1]);
				free(line);
			}
			close(msh->herdocfd[*rednum][1]);
			(*rednum)++;
		}
		i += 2;
	}
}

void	ft_herdocs_input(t_msh *msh)
{
	t_lst	*temp_cmd;
	int		count;
	int		rednum;

	count = ft_herdoc_count(msh);
	temp_cmd = msh->cmd;
	rednum = 0;
	if (!count)
		return ;
	msh->herdocnum = 0;
	msh->herdocfd = ft_create_pipe(count, msh);
	while (temp_cmd)
	{
		if (temp_cmd->redirs)
			ft_herdoc_input(temp_cmd, msh, &rednum);
		temp_cmd = temp_cmd->next;
	}
}

void	ft_inc_herdocnum(t_lst *temp, t_msh *msh)
{
	int	i;

	if (!temp->redirs)
		return ;
	i = 0;
	while (temp->redirs[i])
	{
		if (!ft_strcmp(temp->redirs[i], "<<"))
			msh->herdocnum++;
		i += 2;
	}
}

void	ft_herdoc(char **redirs, t_msh *msh, t_lst *temp, int num_pipe)
{
	if (msh->herdocnum > 0)
		ft_close(msh->herdocfd[msh->herdocnum - 1][0]);
	if (dup2(msh->herdocfd[msh->herdocnum][0], 0) == -1)
		ft_error_exit("ft_herdoc", 0, errno, msh);
	msh->herdocnum++;
}
