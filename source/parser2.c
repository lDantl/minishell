/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:13:25 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/23 19:48:12 by rdanica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

int	check_env(char **env, char *str, int k)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[k][j++] == str[i])
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

char	*ft_dollar2(int *in, char **tmps, char **env, char *str)
{
	char	*tmp3;

	if (tmps[1] != NULL)
	{
		tmps[1] = ft_substr(env[in[3]], in[2] + 1,
				ft_strlen(env[in[3]]) - in[2]);
		tmps[0] = ft_substr(str, 0, in[1] - (ft_strlen(tmps[0]) + 1));
		tmp3 = ft_substr(str, in[1], (ft_strlen(str) - in[1]));
		tmps[0] = ft_strjoin(tmps[0], tmps[1]);
		tmps[0] = ft_strjoin(tmps[0], tmp3);
	}
	else
	{
		free (tmps[0]);
		tmps[0] = ft_substr(str, 0, in[0]);
		tmps[1] = ft_strjoin(tmps[0], "\"\" ");
		tmp3 = ft_substr(str, in[1] + 1, (ft_strlen(str) - in[1]));
		tmps[0] = ft_strjoin(tmps[1], tmp3);
	}
	free (str);
	return (tmps[0]);
}

char	*ft_dollar(char *str, char **env)
{
	int		in[4];
	char	*tmps[2];

	ft_bzero(in, 16);
	ft_bzero(tmps, 2);
	in[3] = -1;
	while (str[++in[1]])
		if (!ifkey(str[in[1]]))
			break ;
	if (in[1] == in[0] + 1)
		return (str);
	tmps[0] = ft_substr(str, in[0] + 1, in[1] - in[0] - 1);
	while (env[++in[3]])
	{
		if (check_env(env, tmps[0], in[3]))
		{
			in[2] = 0;
			while (env[in[3]][in[2]] && env[in[3]][in[2]] != '=')
				in[2]++;
			tmps[1] = ft_substr(env[in[3]], 0, in[2]);
			if (ft_strcmp(tmps[0], tmps[1]) == 0)
				break ;
		}
	}
	return (ft_dollar2(in, tmps, env, str));
}
