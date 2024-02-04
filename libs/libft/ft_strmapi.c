/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 22:04:05 by nnabaeei          #+#    #+#             */
/*   Updated: 2022/11/08 13:37:47 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		len;
	unsigned int		i;
	char				*rettro;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	rettro = malloc(sizeof(char) * (len + 1));
	if (!rettro)
		return (NULL);
	i = 0;
	while (s[i])
	{
		rettro[i] = f(i, s[i]);
		i++;
	}
	rettro[i] = '\0';
	return (rettro);
}
