/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:05:29 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/19 13:10:18 by rdanica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*new_env_elem(char *str)
{
	t_env	*el;
	int		n;
	int		i;

	n = 0;
	i = 0;
	el = (t_env *)malloc(sizeof(t_env));
	el->back_order = NULL;
	el->next_order = NULL;
	el->next = NULL;
	el->back = NULL;
	el->key = ft_get_key(str, &n);
	el->value = ft_get_value(str + (n + 1));
	return (el);
}

void	lst_add_env(t_env **lst, t_env *el)
{
	if (!el)
		return ;
	if (!(*lst))
	{
		*lst = el;
		return ;
	}
	el->back = *lst;
	(*lst)->next = el;
	*lst = el;
}

t_env	*ft_env_to_list(char **enviroment)
{
	t_env	*env;
	int		i;

	i = -1;
	env = NULL;
	while (enviroment[++i])
	{
		lst_add_env(&env, new_env_elem(enviroment[i]));
	}
	while (env->back)
		env = env->back;
	free_argv(enviroment);
	return (env);
}
