/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:27:55 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/23 19:44:57 by rdanica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_quote(char *str, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	if (str[i] == '\'')
		return (ft_trim(str, "\'"));
	else if (str[i] == '"')
	{
		if (str[++i] == '$')
		{
			tmp = ft_trim(str, "\"");
			tmp = ft_dollar(tmp, env);
		}
		else
			return (ft_trim(str, "\""));
	}
	return (tmp);
}

int	ft_quote_redir_or_pipe(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '"')
	{
		if (str[i + 1] == '|'
			&& (str[i + 2] == '"' || str[i + 2] == '\''))
			return (1);
		if ((str[i + 1] == '>' || str[i + 1] == '<')
			&& (str[i + 2] == '"' || str[i + 2] == '\''))
			return (1);
		if ((str[i + 1] == '>' || str[i + 1] == '<')
			&& (str[i + 2] == '>' || str[i + 2] == '<')
			&& (str[i + 3] == '"' || str[i + 3] == '\''))
			return (1);
	}
	return (0);
}

void	parser(char **mass, char **env)
{
	int		i;
	int		j;

	i = -1;
	while (mass[++i])
	{
		j = 0;
		if (mass[i][j] == '\'' || mass[i][j] == '"')
		{
			if (mass[i][j + 1] == '|' || mass[i][j + 1] == '<'
			|| mass[i][j + 1] == '>')
			{
				j = ft_quote_redir_or_pipe(mass[i]);
				if (j)
					continue ;
			}
			else
				mass[i] = ft_quote(mass[i], env);
		}
		else if (mass[i][j] == '$')
			mass[i] = ft_dollar(mass[i], env);
	}
}
