/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 20:22:24 by nnabaeei          #+#    #+#             */
/*   Updated: 2022/11/11 20:49:35 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*pre;
	char	*suf;
	size_t	len;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	else if (s2[0] == 0)
		return (ft_strdup(s1));
	else if (!s1)
		return (ft_strdup(s2));
	pre = (char *) s1;
	suf = (char *) s2;
	len = ft_strlen(pre) + ft_strlen(suf) + 1;
	str = ft_calloc(len, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcat(str, pre, ft_strlen(str) + ft_strlen(pre) + 1);
	ft_strlcat(str, suf, ft_strlen(str) + ft_strlen(suf) + 1);
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}
