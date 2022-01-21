/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:34:45 by jtawanda          #+#    #+#             */
/*   Updated: 2021/12/06 18:13:25 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc_error(char **strs)
{
	unsigned int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (0);
}

static unsigned int	ft_get_nb(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb;

	if (!s[0])
		return (0);
	i = 0;
	nb = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb++;
	return (nb);
}

static void	ft_get_next_str(char **next_str, unsigned int *next_len, char c)
{
	unsigned int	i;

	*next_str += *next_len;
	*next_len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			return ;
		(*next_len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char			**strs;
	char			*next_str;
	unsigned int	next_len;
	unsigned int	nb;
	unsigned int	i;

	if (!s)
		return (0);
	nb = ft_get_nb(s, c);
	strs = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!strs)
		return (0);
	i = 0;
	next_str = (char *)s;
	next_len = 0;
	while (i++ < nb)
	{
		ft_get_next_str(&next_str, &next_len, c);
		strs[i - 1] = (char *)malloc(sizeof(char) * (next_len + 1));
		if (!strs[i - 1])
			return (ft_malloc_error(strs));
		ft_strlcpy(strs[i - 1], next_str, next_len + 1);
	}
	strs[i - 1] = 0;
	return (strs);
}
