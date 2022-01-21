/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srtjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 10:57:32 by jtawanda          #+#    #+#             */
/*   Updated: 2021/04/25 18:55:29 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	i;

	if (!s1)
		return (0);
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (0);
	i = 0;
	while (*s1)
	{
		s[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		s[i] = *s2;
		i++;
		s2++;
	}
	s[i] = 0;
	return (s);
}
