/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 21:27:59 by jtawanda          #+#    #+#             */
/*   Updated: 2022/01/20 14:34:58 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rewrite_envp(t_msh *msh)
{
	ft_free_strs(msh->envp, ft_strs_count(msh->envp));
	msh->envp = ft_my_envp(msh);
}

static void	ft_del_elem(t_env *temp, t_msh *msh)
{
	if (!temp->back)
	{
		msh->env = temp->next;
		if (temp->next)
			temp->next->back = NULL;
	}
	else
	{
		temp->back->next = temp->next;
		if (temp->next)
			temp->next->back = temp->back;
	}
	if (temp->key)
		free(temp->key);
	if (temp->value)
		free(temp->value);
}

static void	ft_del_env(char *key, t_msh *msh)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = msh->env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			ft_del_elem(temp, msh);
			free(temp);
			ft_rewrite_envp(msh);
			return ;
		}
		temp = temp->next;
	}
}

static int	ft_is_valid_env_name(const char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_isalnum(env[i]) == 0 && env[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(t_lst *cmd, t_msh *msh)
{
	int	i;

	i = 1;
	if (!cmd->field[i])
		return ;
	while (cmd->field[i])
	{
		if (!ft_is_valid_env_name(cmd->field[i]))
			ft_print_error_export(cmd->field[i]);
		ft_del_env(cmd->field[i], msh);
		i++;
	}
}
