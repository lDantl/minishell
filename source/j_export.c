/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 21:17:05 by jtawanda          #+#    #+#             */
/*   Updated: 2022/01/20 14:33:20 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envp_count(t_env **env)
{
	t_env	*temp;
	int		count;

	temp = *env;
	count = 0;
	while (temp)
	{
		if (temp->value)
			count++;
		temp = temp->next;
	}
	return (count);
}

void	ft_print_error_export(char *arg)
{
	ft_putstr_fd("Minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

static int	ft_is_valid_env(const char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[i]) == 1 || env[i] == '=')
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0 && env[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_get_env(char *arg, t_msh *msh)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = 0;
	value = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_strndup(arg, i);
	if (!key)
		ft_error_exit("ft_get_env", "malloc error", 0, msh);
	if (arg[i] && arg[i] == '=')
	{
		value = ft_strtrim(arg + i + 1, "\"");
		if (!value)
			ft_error_exit("ft_get_env", "malloc error", 0, msh);
	}
	if (ft_change_env(key, value, msh))
		ft_add_env(key, value, msh);
	free(key);
	free(value);
}

int	ft_export(t_lst *cmd, t_msh *msh)
{
	int	i;

	i = 1;
	if (!cmd->field[i])
	{
		ft_print_sorted_env(msh);
		return (0);
	}
	else
	{
		while (cmd->field[i])
		{
			if (!ft_is_valid_env(cmd->field[i]))
				ft_print_error_export(cmd->field[i]);
			else
				ft_get_env(cmd->field[i], msh);
			i++;
		}
	}
	return (0);
}
