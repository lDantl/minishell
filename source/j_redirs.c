/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_redirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:48:09 by jtawanda          #+#    #+#             */
/*   Updated: 2022/01/20 15:23:41 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execve(t_lst	*cmd, t_msh *msh)
{
	if (!cmd || !cmd->field || !*cmd->field)
		return ;
	if (ft_strcmp(cmd->field[0], "echo") == 0)
		ft_echo(cmd, msh);
	else if (ft_strcmp(cmd->field[0], "env") == 0)
		ft_env(cmd, msh);
	else if (ft_strcmp(cmd->field[0], "pwd") == 0)
		ft_pwd(msh);
	else if (ft_strcmp(cmd->field[0], "cd") == 0)
		ft_cd(cmd, msh);
	else if (ft_strcmp(cmd->field[0], "exit") == 0)
		ft_exit(cmd, msh);
	else if (ft_strcmp(cmd->field[0], "export") == 0)
		ft_export(cmd, msh);
	else if (ft_strcmp(cmd->field[0], "unset") == 0)
		ft_unset(cmd, msh);
	else
	{
		execve(cmd->field[0], cmd->field, msh->envp);
		ft_print_error(cmd->field[0], ": command not found", 0);
	}
}

static void	ft_input(t_msh *msh, char *file_name)
{
	ft_close(msh->fdin);
	msh->fdin = open(file_name, O_RDONLY, S_IRWXU);
	if (msh->fdin == -1)
	{
		ft_print_error(file_name, 0, errno);
		msh->ret = 1;
		return ;
	}
	if (dup2(msh->fdin, 0) == -1)
		ft_error_exit("ft_input", 0, errno, msh);
}

static void	ft_herdoc(char **redirs, t_msh *msh)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		ft_error_exit("ft_herdoc", 0, errno, msh);
	if (dup2(msh->in, 1) == -1)
		ft_error_exit("ft_herdoc", 0, errno, msh);
	line = NULL;
	while (1)
	{
		line = readline("\033[0;32m> \033[0;29m");
		if (!ft_strcmp(redirs[1], line))
			break ;
		ft_putendl_fd(line, fd[1]);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	free(line);
}

static void	ft_redirect(t_msh	*msh, char *type, char *file_name)
{
	ft_close(msh->fdout);
	if (!ft_strcmp(type, ">"))
		msh->fdout = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		msh->fdout = open(file_name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (msh->fdout == -1)
	{
		ft_print_error(file_name, 0, errno);
		msh->ret = 1;
		return ;
	}
	dup2(msh->fdout, 1);
}

void	ft_redirs(t_lst *temp, t_msh *msh)
{
	int	i;

	i = 0;
	while (temp->redirs && temp->redirs[i])
	{
		if (!ft_strcmp(temp->redirs[i], "<"))
			ft_input(msh, temp->redirs[i + 1]);
		else if (!ft_strcmp(temp->redirs[i], "<<"))
			ft_herdoc(&temp->redirs[i], msh);
		else
			ft_redirect(msh, temp->redirs[i], temp->redirs[i + 1]);
		i += 2;
	}
	if (!msh->ret)
		ft_execve(temp, msh);
}