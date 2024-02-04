/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:02:06 by nnabaeei          #+#    #+#             */
/*   Updated: 2022/11/07 17:51:10 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	const char	*ptr;

	ptr = malloc(ft_strlen(s1)+1);
	if (!ptr)
		return (NULL);
	ft_memcpy((char *)ptr, (char *)s1, (ft_strlen(s1)) + 1);
	return ((char *)ptr);
}
