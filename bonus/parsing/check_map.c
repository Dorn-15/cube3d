/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:00:54 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/29 16:11:54 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d_bonus.h"

static int	init_spawn(char **map, int y, int x)
{
	const float	pi = 3.14159265358979323846;
	static int	spawn = 0;
	t_data		*data;

	if (spawn)
		return (0);
	spawn = 1;
	data = get_data();
	if (!data)
		return (0);
	data->pos[0] = x + 0.5;
	data->pos[1] = y + 0.5;
	if (map[y][x] == 'E')
		data->r = 0;
	else if (map[y][x] == 'W')
		data->r = pi;
	else if (map[y][x] == 'S')
		data->r = pi / 2;
	else if (map[y][x] == 'N')
		data->r = (3 * pi) / 2;
	map[y][x] = '0';
	return (1);
}

int	check_door_walls(char **map, int y, int x)
{
	if ((map[y + 1][x] == '1' && map[y - 1][x] == '1' && map[y][x + 1] == '0'
			&& map[y][x - 1] == '0') || (map[y + 1][x] == '0' && map[y
			- 1][x] == '0' && map[y][x + 1] == '1' && map[y][x - 1] == '1'))
		return (1);
	return (0);
}

static int	check_close_map(char **map, int y, int x, int len)
{
	if ((map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
			|| map[y][x] == 'W') && !init_spawn(map, y, x))
		return (0);
	if (map[y][x] == 'D' && !check_door_walls(map, y, x))
		return (0);
	if (!map[y][x - 1] || map[y][x - 1] == ' ')
		return (0);
	if (!map[y][x + 1] || map[y][x + 1] == ' ')
		return (0);
	if (ft_strlen(map[y - 1]) < x || !map[y - 1][x] || map[y - 1][x] == ' ')
		return (0);
	if (ft_strlen(map[y + 1]) < x || !map[y + 1][x] || map[y + 1][x] == ' ')
		return (0);
	return (1);
}

static int	check_first_last(char *map)
{
	int	x;

	x = 0;
	if (!map)
		return (0);
	while (map[x])
	{
		if (map[x] != ' ' && map[x] != '1')
			return (0);
		x++;
	}
	return (1);
}

static int	check_map(char **map)
{
	int	x;
	int	y;
	int	len;

	if (!map)
		return (0);
	if (!check_first_last(map[0]))
		return (0);
	y = 0;
	while (map[y] && map[y + 1])
	{
		x = 0;
		len = ft_strlen(map[y]);
		while (map[y][x])
		{
			if (map[y][x] != ' ' && map[y][x] != '1' && (x == 0 || x == len - 1
					|| !check_close_map(map, y, x, len)))
				return (0);
			x++;
		}
		y++;
	}
	if ((map[y] && !check_first_last(map[y])) || get_data()->pos[0] == 0)
		return (0);
	return (1);
}

int	init_map_str(t_data *data, t_map *map, int nbr)
{
	int	i;

	i = 0;
	data->map = malloc(sizeof(char *) * (nbr + 1));
	if (!data->map)
		return (0);
	while (map)
	{
		data->map[i] = ft_strdup(map->str);
		if (!data->map[i])
		{
			free_split(data->map);
			return (0);
		}
		map = map->next;
		i++;
	}
	data->map[i] = NULL;
	if (!check_map(data->map))
		return (0);
	return (1);
}
