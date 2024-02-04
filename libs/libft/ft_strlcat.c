/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:49:19 by nnabaeei          #+#    #+#             */
/*   Updated: 2022/11/08 20:18:20 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strnlen(const char *s, size_t max);

size_t	ft_strlcat(char *dst, const char *src, size_t maxlen)
{
	const size_t	srclen = ft_strlen(src);
	const size_t	dstlen = ft_strnlen(dst, maxlen);

	if (dstlen == maxlen)
		return (maxlen + srclen);
	if (srclen < maxlen - dstlen)
	{
		ft_memcpy(dst + dstlen, src, srclen + 1);
	}
	else
	{
		ft_memcpy(dst + dstlen, src, maxlen - dstlen -1);
		dst[maxlen - 1] = '\0';
	}
	return (dstlen + srclen);
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	i;	

	i = 0;
	while (i < maxlen)
	{
		if (!*s)
			break ;
		i++;
		s++;
	}			
	return (i);
}
