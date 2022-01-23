/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_start.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:47:01 by jtawanda          #+#    #+#             */
/*   Updated: 2022/01/23 18:16:46 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (env)
	{
		temp = env;
		env = env->next;
		if (temp->key)
			free(temp->key);
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

void	ft_free_msh(t_msh *msh)
{
	if (!msh)
		return ;
	if (msh->env)
		ft_free_env(msh->env);
	if (msh->cmd)
		ft_free_lst(&msh->cmd);
	if (msh->pipefd)
		ft_free_fds(msh->pipefd);
	if (msh->herdocfd)
		ft_free_fds(msh->herdocfd);
	if (msh->envp)
		ft_free_strs(msh->envp, ft_strs_count(msh->envp));
	free(msh);
}

void	ft_print_error(char *name, char *error, int num)
{
	ft_putstr_fd("Minishell: ", 2);
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error)
		ft_putendl_fd(error, 2);
	else
		ft_putendl_fd(strerror(num), 2);
}

void	ft_error_exit(char *name, char *error, int num, t_msh *msh)
{
	if (name && error)
		ft_print_error(name, error, 0);
	else
		ft_print_error(name, 0, num);
	ft_free_msh(msh);
	if (num)
		exit(num);
	exit (1);
}

void	ft_inc_shlvl(t_msh *msh)
{
	t_env	*temp;
	int		shlvl;

	shlvl = 1;
	if (!msh || !msh->env)
		return ;
	temp = msh->env;
	while (temp && temp->key && ft_strcmp(temp->key, "SHLVL"))
		temp = temp->next;
	if (!temp)
		ft_add_env("SHLVL", "1", msh);
	else if (temp->key)
	{
		if (temp->value)
		{
			shlvl = ft_atoi(temp->value) + 1;
			free(temp->value);
		}
		temp->value = ft_itoa(shlvl);
		if (!temp->value)
			ft_error_exit("ft_inc_shlvl", "malloc error", 0, msh);
		ft_rewrite_envp(msh);
	}
}
