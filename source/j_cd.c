/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:18:44 by jtawanda          #+#    #+#             */
/*   Updated: 2022/01/20 15:47:26 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_error_cd(char **args, int num)
{
	ft_putstr_fd("Minishell: cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(num), 2);
}

static char	*ft_get_path(char *key, t_env *env, t_msh *msh)
{
	t_env	*temp;
	char	*ret;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			ret = ft_strdup(temp->value);
			if (!ret)
				ft_error_exit("ft_get_path", "malloc error", 0, msh);
			return (ret);
		}
		temp = temp->next;
	}
	return (NULL);
}

static int	ft_update_pwd(char *key, t_msh *msh)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_error_exit("ft_update_pwd", "getcwd error", 0, msh);
	if (ft_change_env(key, pwd, msh))
		if (ft_add_env(key, pwd, msh))
			return (1);
	free(pwd);
	return (0);
}

static char	*ft_cd_home_oldpwd(int i, t_msh *msh)
{
	char	*path;

	if (i == 0)
	{
		ft_update_pwd("OLDPWD", msh);
		path = ft_get_path("HOME", msh->env, msh);
		if (!path)
		{
			ft_print_error("cd", "HOME not set", 0);
			return (0);
		}
	}
	else
	{
		path = ft_get_path("OLDPWD", msh->env, msh);
		if (!path)
		{
			ft_print_error("cd", "OLDPWD not set", 0);
			return (0);
		}
		ft_putendl_fd(path, 1);
		ft_update_pwd("OLDPWD", msh);
	}
	return (path);
}

void	ft_cd(t_lst *cmd, t_msh *msh)
{
	char	*path;
	int		ret;

	path = 0;
	if (!cmd->field[1])
		path = ft_cd_home_oldpwd(0, msh);
	else if (cmd->field[1][0] == '-' && cmd->field[1][1] == 0)
		path = ft_cd_home_oldpwd(1, msh);
	else
	{
		ft_update_pwd("OLDPWD", msh);
		path = ft_strdup(cmd->field[1]);
		if (!path)
			ft_error_exit("cd", "malloc error", 0, msh);
	}
	if (!path)
	{
		msh->ret = 1;
		return ;
	}
	ret = chdir(path);
	free(path);
	if (ret != 0)
		ft_print_error_cd(cmd->field, errno);
	ft_update_pwd("PWD", msh);
}
