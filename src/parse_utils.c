/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:57:34 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 20:00:12 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*parse_no(char *line)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	x = 0;
	str = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	while (line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		i += 2;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			i++;
		else
		{
			str[x] = line[i];
			i++;
			x++;
		}
	}
	return (str);
}

char	*parse_we(char *line)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	x = 0;
	str = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	while (line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == 'W' && line[i + 1] == 'E')
		i += 2;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			i++;
		else
		{
			str[x] = line[i];
			i++;
			x++;
		}
	}
	return (str);
}

char	*parse_so(char *line)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	x = 0;
	str = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	while (line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == 'S' && line[i + 1] == 'O')
		i += 2;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			i++;
		else
		{
			str[x] = line[i];
			i++;
			x++;
		}
	}
	return (str);
}

char	*parse_ea(char *line)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	x = 0;
	str = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	while (line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == 'E' && line[i + 1] == 'A')
		i += 2;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			i++;
		else
		{
			str[x] = line[i];
			i++;
			x++;
		}
	}
	return (str);
}

char	*parse_f(char *line)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	x = 0;
	str = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	while (line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == 'F')
		i += 1;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			i++;
		else
		{
			str[x] = line[i];
			i++;
			x++;
		}
	}
	return (str);
}
