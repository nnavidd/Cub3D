/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:30:43 by nnabaeei          #+#    #+#             */
/*   Updated: 2022/11/07 17:37:41 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*src_1;
	char		*dst_1;

	if (!dst && !src)
		return (NULL);
	dst_1 = (char *) dst;
	src_1 = (char *) src;
	if (dst_1 < src_1)
	{
		while (len--)
			*dst_1++ = *src_1++;
	}
	else
	{
		src_1 = src + (len - 1);
		dst_1 = dst + (len - 1);
		while (len --)
			*dst_1-- = *src_1--;
	}
	return (dst);
}
