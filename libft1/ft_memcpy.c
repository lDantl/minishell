/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 07:57:26 by jtawanda          #+#    #+#             */
/*   Updated: 2021/04/25 16:42:04 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	if (!p1 && !p2)
		return (0);
	while (n > 0)
	{
		*p1 = *p2;
		n--;
		p1++;
		p2++;
	}
	return (dst);
}
