/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:13:28 by nnabaeei          #+#    #+#             */
/*   Updated: 2022/11/11 15:46:56 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int c, size_t len)
{
	unsigned long int				i;
	unsigned char					*str;

	i = 0;
	str = (unsigned char *) p;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (p);
}
