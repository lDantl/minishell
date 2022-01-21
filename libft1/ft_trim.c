/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 23:25:32 by jtawanda          #+#    #+#             */
/*   Updated: 2022/01/21 23:25:32 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_search_for_matches(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_start_end(char *str)
{
	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_trim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	n;
	char	*str;

	start = 0;
	str = NULL;
	n = 0;
	if (!s1)
		return (NULL);
	end = ft_strlen(s1);
	while (ft_search_for_matches(s1[start], (char *)set))
		start++;
	if (start == end)
		return (ft_start_end(str));
	while (ft_search_for_matches(s1[end - 1], (char *)set))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	while (start < end)
		str[n++] = s1[start++];
	str[n] = '\0';
	free((char *)s1);
	return (str);
}
