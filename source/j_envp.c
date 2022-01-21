/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_envp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 21:30:38 by jtawanda          #+#    #+#             */
/*   Updated: 2022/01/20 14:45:44 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_envp_write(char **envp, t_msh *msh)
{
	t_env	*temp;
	char	*temp_str;
	int		i;

	temp = msh->env;
	i = 0;
	while (temp)
	{
		if (temp->value)
		{
			temp_str = ft_strjoin(temp->key, "=");
			if (!temp_str)
				ft_error_exit("ft_envp_write", "malloc error", 0, msh);
			envp[i] = ft_strjoin(temp_str, temp->value);
			if (!envp[i])
				ft_error_exit("ft_envp_write", "malloc error", 0, msh);
			free(temp_str);
			i++;
		}
		temp = temp->next;
	}
}

char	**ft_my_envp(t_msh *msh)
{
	char	**envp;
	int		len;

	len = ft_envp_count(&msh->env);
	envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!envp)
		ft_error_exit("ft_my_envp", "malloc error", 0, msh);
	envp[len] = 0;
	ft_envp_write(envp, msh);
	return (envp);
}

int	ft_change_env(char *key, char *value, t_msh *msh)
{
	t_env	*temp;

	temp = msh->env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (value)
			{
				if (temp->value)
					free(temp->value);
				temp->value = ft_strdup(value);
			}
			ft_rewrite_envp(msh);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

static t_env	*ft_get_new_env(char *key, char *value, t_msh *msh)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		ft_error_exit("ft_add_env", "malloc error", 0, msh);
	new_env->back_order = NULL;
	new_env->next_order = NULL;
	new_env->next = NULL;
	new_env->back = NULL;
	new_env->key = ft_strdup(key);
	if (!new_env->key)
		ft_error_exit("ft_add_env", "malloc error", 0, msh);
	if (value)
	{
		new_env->value = ft_strdup(value);
		if (!new_env->value)
			ft_error_exit("ft_add_env", "malloc error", 0, msh);
	}
	else
		new_env->value = NULL;
	return (new_env);
}

int	ft_add_env(char *key, char *value, t_msh *msh)
{
	t_env	*new_env;
	t_env	*temp;

	new_env = ft_get_new_env(key, value, msh);
	if (!msh->env)
	{
		msh->env = new_env;
		ft_rewrite_envp(msh);
		return (0);
	}
	temp = msh->env;
	while (temp->next)
		temp = temp->next;
	temp->next = new_env;
	new_env->back = temp;
	ft_rewrite_envp(msh);
	return (0);
}
