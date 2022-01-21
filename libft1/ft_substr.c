/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 10:28:20 by jtawanda          #+#    #+#             */
/*   Updated: 2021/04/25 12:26:13 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;
	size_t	len2;

	if (!s || len <= 0 || start >= ft_strlen(s))
		return (ft_strdup(""));
	len2 = ft_strlen(&s[start]);
	if (len > len2)
		len = len2;
	subs = (char *)malloc(sizeof(char) * (len + 1));
	if (!subs)
		return (0);
	i = 0;
	while (i < len)
	{
		subs[i] = s[i + start];
		i++;
	}
	subs[i] = 0;
	return (subs);
}
