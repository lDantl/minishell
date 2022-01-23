/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:47:58 by jtawanda          #+#    #+#             */
/*   Updated: 2022/01/23 18:16:16 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

int	ft_is_red(char *s)
{
	if (!ft_strcmp(s, ">") || !ft_strcmp(s, "<")
		|| !ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"))
		return (1);
	return (0);
}

static void	ft_one_cmd(t_msh *msh)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_print_error("ft_minishell", 0, errno);
	else if (!pid)
	{
		if (!msh->cmd->field || !msh->cmd->field[0])
			ft_redirs(msh->cmd, msh, -1);
		else if (built_in(msh->cmd->field[0]))
			ft_redirs(msh->cmd, msh, -1);
		exit(0);
	}
	else
	{
		waitpid(pid, 0, 0);
		if (msh->cmd->field && msh->cmd->field[0]
			&& !built_in(msh->cmd->field[0]))
			ft_redirs(msh->cmd, msh, -1);
	}
}

static int	ft_count_cmd(t_msh *msh)
{
	int		i;
	t_lst	*temp;

	i = 0;
	temp = msh->cmd;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	ft_minishell(t_msh *msh)
{
	int	count;

	count = ft_count_cmd(msh);
	ft_herdocs_input(msh);
	if (count == 1)
		ft_one_cmd(msh);
	else if (count > 1)
		ft_pipex(count, msh);
	ft_free_fds(msh->herdocfd);
	dup2(msh->in, 0);
	dup2(msh->out, 1);
	ft_close(msh->fdin);
	ft_close(msh->fdout);
}
