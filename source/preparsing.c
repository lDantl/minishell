/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:19:59 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/23 16:50:27 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_space_delited2(char	*str, int *i)
{
	int		space;
	char	*temp;

	space = *i;
	while (str[space++] == ' ')
		;
	str[*i + 1] = '\0';
	temp = str;
	str = ft_strjoin(str, str + space - 1);
	free(temp);
	return (str);
}

char	*ft_space_delited(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] && str[i] != '\'')
				;
			if (!str[i++])
				return (str);
		}
		if (str[i] == '\"')
		{
			while (str[++i] && str[i] != '\"')
				;
			if (!str[i++])
				return (str);
		}
		if (str[i] == ' ' && str[i + 1] == ' ')
			str = ft_space_delited2(str, &i);
	}
	return (str);
}

int	preparser(char *str)
{
	int	i;
	int	q;
	int	q2;

	i = -1;
	q = 0;
	q2 = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			q2++;
		if (str[i] == '\'')
			q++;
	}
	if ((q % 2) != 0 || (q2 % 2) != 0)
		return (0);
	return (1);
}
