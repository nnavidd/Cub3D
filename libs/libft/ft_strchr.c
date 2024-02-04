/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:12:49 by nnabaeei          #+#    #+#             */
/*   Updated: 2022/11/11 15:49:56 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	strl;
	size_t	i;

	strl = ft_strlen(s);
	i = 0;
	if (strl == 0 && *s != 0)
		return (NULL);
	if (*s == 0 && strl != 0)
		return ((char *)s);
	if (!c)
		return ((char *)&s[strl]);
	while (i <= strl)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
		i++;
	}
	return (NULL);
}
