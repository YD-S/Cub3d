/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:41:51 by ysingh            #+#    #+#             */
/*   Updated: 2023/05/10 00:18:40 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		length;
	char	*copy;
	int		i;

	i = 0;
	length = (int)ft_strlen(s);
	copy = (char *)ft_calloc(sizeof(char), (length + 1));
	if (!copy)
		return (NULL);
	while (i < length)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
