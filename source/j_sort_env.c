/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_sort_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 21:20:57 by jtawanda          #+#    #+#             */
/*   Updated: 2022/01/20 14:52:33 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_count(t_env **env)
{
	t_env	*temp;
	int		count;

	temp = *env;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

static char	**ft_env_to_strs(t_env **env, int len, t_msh *msh)
{
	char	**strs;
	t_env	*temp;
	int		i;

	strs = (char **)malloc(sizeof(char *) * (len + 1));
	if (!strs)
		ft_error_exit("ft_env_to_strs", "malloc error", 0, msh);
	temp = *env;
	i = 0;
	while (temp)
	{
		strs[i] = ft_strdup(temp->key);
		if (!strs[i])
		{
			ft_free_strs(strs, len);
			ft_error_exit("ft_env_to_strs", "malloc error", 0, msh);
		}
		i++;
		temp = temp->next;
	}
	strs[i] = 0;
	return (strs);
}

static void	ft_sort_strs(char **strs, int len)
{
	int		i;
	int		j;
	char	*temp;

	j = 0;
	while (strs[j])
	{
		i = 0;
		while (i < len - j - 1)
		{
			if (ft_strcmp(strs[i], strs[i + 1]) > 0)
			{
				temp = strs[i];
				strs[i] = strs[i + 1];
				strs[i + 1] = temp;
			}
			i++;
		}
		j++;
	}
}

static void	ft_print_sorted_strs(char **strs, t_msh *msh)
{
	t_env	*temp_env;

	while (*strs)
	{
		temp_env = msh->env;
		while (temp_env)
		{
			if (ft_strcmp(*strs, temp_env->key) == 0)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(temp_env->key, 1);
				if (temp_env->value)
				{
					ft_putstr_fd("=\"", 1);
					ft_putstr_fd(temp_env->value, 1);
					ft_putstr_fd("\"", 1);
				}
				ft_putstr_fd("\n", 1);
			}
			temp_env = temp_env->next;
		}
		strs++;
	}
}

int	ft_print_sorted_env(t_msh *msh)
{
	char	**strs;
	int		len;

	len = ft_env_count(&msh->env);
	strs = ft_env_to_strs(&msh->env, len, msh);
	if (!strs)
		ft_error_exit("ft_print_sorted_env", "malloc error", 0, msh);
	ft_sort_strs(strs, len);
	ft_print_sorted_strs(strs, msh);
	ft_free_strs(strs, len);
	return (0);
}
