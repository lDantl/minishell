/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:09:40 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/23 14:51:53 by rdanica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**argvdup(char **ar)
{
	int		i;
	char	**new_argv;

	new_argv = (char **)malloc(sizeof(char *) * (len_tab(ar) + 1));
	i = -1;
	while (ar[++i])
		new_argv[i] = ft_strdup(ar[i]);
	new_argv[i] = NULL;
	return (new_argv);
}

char	*ft_get_value(char *str)
{
	if (!str || !*str)
		return (ft_strdup(""));
	return (ft_strdup(str));
}

char	*ft_get_key(char *str, int *n)
{
	if (!str || !*str)
		return (NULL);
	while (str[*n] && str[*n] != '=')
		(*n)++;
	str[*n] = '\0';
	return (ft_strdup(str));
}
