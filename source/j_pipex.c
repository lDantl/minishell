/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:58:02 by jtawanda          #+#    #+#             */
/*   Updated: 2022/01/23 18:15:30 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_fds(int **fds)
{
	int	i;

	i = 0;
	if (fds)
	{
		while (fds[i])
		{
			ft_close(fds[i][0]);
			ft_close(fds[i][1]);
			free(fds[i]);
			i++;
		}
	}
	free(fds);
}

int	**ft_create_pipe(int count, t_msh *msh)
{
	int	**fd;
	int	i;

	i = 0;
	fd = (int **)malloc(sizeof(int *) * (count + 1));
	if (!fd)
		ft_error_exit("ft_create_pipe", "malloc error", 0, msh);
	fd[count] = NULL;
	while (i < count)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
			ft_error_exit("ft_create_pipe", "malloc error", 0, msh);
		if (pipe(fd[i]) == -1)
			ft_error_exit("ft_create_pipe", 0, errno, msh);
		i++;
	}
	return (fd);
}

static void	ft_child_process(t_lst *temp, t_msh *msh, int i)
{
	if (!temp->back)
	{
		if (dup2(msh->pipefd[i][1], 1) == -1)
			ft_error_exit("ft_child_process", 0, errno, msh);
	}
	else if (!temp->next)
	{
		if (dup2(msh->pipefd[i - 1][0], 0) == -1)
			ft_error_exit("ft_child_process", 0, errno, msh);
	}
	else
	{
		ft_close(msh->pipefd[i][0]);
		if (dup2(msh->pipefd[i - 1][0], 0) == -1 ||
			dup2(msh->pipefd[i][1], 1) == -1)
			ft_error_exit("ft_child_process", 0, errno, msh);
	}
	ft_redirs(temp, msh, i);
	exit(0);
}

static void	ft_parent_process(t_lst *temp, t_msh *msh, int i)
{
	waitpid(msh->pid, 0, 0);
	ft_inc_herdocnum(temp, msh);
	if (!temp->back)
		ft_close(msh->pipefd[i][1]);
	else if (!temp->next)
		ft_close(msh->pipefd[i - 1][0]);
	else
	{
		ft_close(msh->pipefd[i - 1][0]);
		ft_close(msh->pipefd[i][1]);
	}
}

void	ft_pipex(int count, t_msh *msh)
{
	t_lst	*temp;
	int		i;

	msh->pipefd = ft_create_pipe(count - 1, msh);
	temp = msh->cmd;
	i = 0;
	while (temp && !msh->ret)
	{
		msh->pid = fork();
		if (msh->pid == -1)
			ft_error_exit("ft_pipex", 0, errno, msh);
		else if (!msh->pid)
			ft_child_process(temp, msh, i);
		else
			ft_parent_process(temp, msh, i);
		temp = temp->next;
		i++;
	}
	ft_free_fds(msh->pipefd);
}
