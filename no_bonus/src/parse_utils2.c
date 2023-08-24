/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:57:40 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 20:00:20 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*parse_c(char *line)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	x = 0;
	str = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	while (line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == 'C')
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

t_map_data	do_no(char *line, t_map_data map_data)
{
	map_data.no = parse_no(line);
	return (map_data);
}

t_map_data	do_so(char *line, t_map_data map_data)
{
	map_data.so = parse_so(line);
	return (map_data);
}

t_map_data	do_ea(char *line, t_map_data map_data)
{
	map_data.ea = parse_ea(line);
	return (map_data);
}

t_map_data	do_we(char *line, t_map_data map_data)
{
	map_data.we = parse_we(line);
	return (map_data);
}
