/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:52:48 by nnabaeei          #+#    #+#             */
/*   Updated: 2023/02/18 12:10:42 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	const char		*src_1;
	char			*dst_1;

	if (!dst && !src)
		return (NULL);
	if (n == 0)
		return (dst);
	dst_1 = (char *) dst;
	src_1 = (const char *) src;
	i = 0;
	while (i < n)
	{
		dst_1[i] = src_1[i];
		i++;
	}	
	return (dst);
}
