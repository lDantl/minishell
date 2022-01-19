/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:34:39 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/19 13:23:42 by rdanica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin_slash(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s1))
		str[i] = s1[i];
	str[i] = '/';
	i++;
	j = -1;
	while (++j < ft_strlen(s2))
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}

void	ft_error(char *str)
{
	write (2, str, ft_strlen(str));
	exit (EXIT_FAILURE);
}

int	built_in(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd"))
		return (0);
	else if (!ft_strcmp(cmd, "export"))
		return (0);
	else if (!ft_strcmp(cmd, "unset"))
		return (0);
	else if (!ft_strcmp(cmd, "cd"))
		return (0);
	else if (!ft_strcmp(cmd, "echo"))
		return (0);
	else if (!ft_strcmp(cmd, "env"))
		return (0);
	else if (!ft_strcmp(cmd, "exit"))
		return (0);
	return (1);
}

char	*ft_find_path(char *cmd, char **env)
{
	char	**path_split;
	char	*path;
	int		i;

	i = 0;
	if (!cmd || !*cmd || !built_in(cmd) || cmd[i] == '/' || cmd[i] == '.')
		return (0);
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (!env[i])
		ft_error(strerror(errno));
	path_split = ft_split(env[i] + 5, ':');
	i = -1;
	while (path_split[++i])
	{
		path = ft_strjoin_slash(path_split[i], cmd);
		if (access(path, F_OK) == 0)
		{
			ft_split_free(path_split);
			return (path);
		}
		free(path);
	}
	ft_split_free(path_split);
	return (0);
}
