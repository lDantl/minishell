/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 08:30:48 by jtawanda          #+#    #+#             */
/*   Updated: 2021/04/25 16:43:12 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	if (!p1 && !p2)
		return (0);
	if (p2 < p1)
	{
		while (len-- > 0)
		{
			p1[len] = p2[len];
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			p1[i] = p2[i];
			i++;
		}
	}
	return (dst);
}
