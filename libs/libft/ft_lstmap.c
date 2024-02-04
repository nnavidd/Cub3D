/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:45:54 by nnabaeei          #+#    #+#             */
/*   Updated: 2022/11/15 21:18:12 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlsth;
	t_list	*newlst;

	if (!lst)
		return (NULL);
	newlsth = ft_lstnew(f(lst->content));
	if (!newlsth)
		return (NULL);
	lst = lst->next;
	while (lst && lst->content)
	{
		newlst = ft_lstnew(f(lst->content));
		if (!newlst)
		{
			ft_lstclear(&newlsth, del);
			return (NULL);
		}
		ft_lstadd_back(&newlsth, newlst);
		lst = lst->next;
	}
	return (newlsth);
}
