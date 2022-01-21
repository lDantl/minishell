/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 07:45:32 by jtawanda          #+#    #+#             */
/*   Updated: 2021/04/25 14:02:29 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len++;
	while (nb != 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

static char	*ft_malloc_str(int n, int *size)
{
	char	*str;

	if (n < 0)
	{
		(*size)++;
		str = (char *)malloc(sizeof(char) * (*size + 1));
		if (!str)
			return (0);
		str[0] = '-';
	}
	else if (n > 0)
	{
		str = (char *)malloc(sizeof(char) * (*size + 1));
		if (!str)
			return (0);
	}
	else
	{
		str = (char *)malloc(sizeof(char) * (*size + 1));
		if (!str)
			return (0);
		str[0] = '0';
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	int				size;

	if (n < 0)
		nb = n * -1;
	else
		nb = n;
	size = ft_get_size(nb);
	str = ft_malloc_str(n, &size);
	if (!str)
		return (0);
	str[size] = 0;
	while (--size >= 0 && nb != 0)
	{
		str[size] = nb % 10 + 48;
		nb /= 10;
	}
	return (str);
}
