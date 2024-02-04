/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:50:04 by nnabaeei          #+#    #+#             */
/*   Updated: 2023/03/12 20:21:52 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**freealloc(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
		free(arr[j++]);
	free(arr);
	return (NULL);
}

static	char	**get_wrd(char **arr, char *s, char c)
{
	size_t		last;
	size_t		len;
	size_t		i;

	i = 0;
	len = 0;
	last = 0;
	while (s[last + len])
	{
		while (s[last + len] && s[last + len] != c)
			len++;
		arr[i] = ft_calloc((len + 1), sizeof(char));
		if (arr[i] == NULL)
			return (freealloc(arr));
		ft_memcpy(arr[i], s + last, len);
		arr[i][len] = '\0';
		while (s[last + len] && s[last + len] == c)
			len++;
		last += len;
		len = 0;
		i++;
	}
	return (arr);
}

static	size_t	catch_wrd(char *s, char c)
{
	size_t		wds;
	size_t		i;

	wds = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
		wds++;
	}
	return (wds);
}

char	**ft_split(const char *s, char c)
{
	char	*st;
	size_t	wds;
	char	**arr;
	char	buf[2];

	if (!s)
		return (NULL);
	buf[0] = c;
	buf[1] = '\0';
	st = ft_strtrim(s, buf);
	if (!st)
		return (NULL);
	wds = catch_wrd(st, c);
	arr = malloc((wds + 1) * sizeof(char *));
	if (arr && get_wrd(arr, st, c))
	{
		arr[wds] = NULL;
		free(st);
		return (arr);
	}
	free(st);
	return (NULL);
}
