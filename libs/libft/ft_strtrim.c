/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:09:34 by nnabaeei          #+#    #+#             */
/*   Updated: 2022/11/11 15:51:39 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*copyall(char const *s1, size_t start, size_t len)
{
	char	*ptr;

	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1 + start, len);
	ptr[len] = '\0';
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	size_t		len;

	if (!s1)
		return (NULL);
	if (!set)
		return (copyall(s1, 0, ft_strlen(s1)));
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[end]) && end > start)
		end--;
	if (start == ft_strlen(s1))
		return (copyall(s1, 0, 0));
	len = end - start + 1;
	return (copyall(s1, start, len));
}
