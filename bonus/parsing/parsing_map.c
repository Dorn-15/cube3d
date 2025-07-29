/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:28:59 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/29 17:11:48 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d_bonus.h"

void	free_map(t_map *map)
{
	if (!map)
		return ;
	while (map && map->prev)
		map = map->prev;
	while (map && map->next)
	{
		map = map->next;
		if (map->prev)
		{
			if (map->prev->str)
				free(map->prev->str);
			free(map->prev);
			map->prev = NULL;
		}
	}
	if (map && map->str)
		free(map->str);
	if (map)
		free(map);
	map = NULL;
}

static int	check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' '
			|| str[i] == '1' || str[i] == '0'
			|| str[i] == 'N' || str[i] == 'S'
			|| str[i] == 'E' || str[i] == 'W'
			|| str[i] == 'D'))
		i++;
	if (str[i] && str[i] != '\n')
		return (0);
	if (str[i] && str[i] == '\n')
		str[i] = '\0';
	return (1);
}

t_map	*new_mapline(char *str, t_map *prev)
{
	t_map	*map;

	if (!str || !check_line(str))
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->str = ft_strdup(str);
	if (!map->str)
		return (free(map), NULL);
	map->prev = prev;
	if (prev)
		prev->next = map;
	map->next = NULL;
	return (map);
}
