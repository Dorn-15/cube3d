/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:05:12 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/28 15:19:53 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d_bonus.h"

static int	define_size(t_data *data, t_imgs *img)
{
	static int	size = 0;
	int			len;
	int			i;

	if (size == 0)
	{
		i = 0;
		while (data->map[i])
		{
			len = ft_strlen(data->map[i]);
			if (len > size)
				size = len;
			i++;
		}
		if (i > size)
			size = img->height / i / 3;
		else
			size = img->width / size / 3;
	}
	return (size);
}

static void	draw_cube(int x, int y, int color, t_data *data)
{
	const int	size = define_size(NULL, NULL);
	t_imgs		*img;
	int			w;

	img = get_mlx()->img;
	x *= size;
	y *= size;
	w = 0;
	if (data->map[(y / size) - 1][x / size] == '1')
		while (w <= size)
			set_pixel(img, x + w++, y, color);
	w = 0;
	if (data->map[(y / size) + 1][x / size] == '1')
		while (w <= size)
			set_pixel(img, x + w++, y + size, color);
	w = 1;
	if (data->map[y / size][(x / size) - 1] == '1')
		while (w <= size)
			set_pixel(img, x, y + w++, color);
	w = 1;
	if (data->map[y / size][(x / size) + 1] == '1')
		while (w <= size)
			set_pixel(img, x + size, y + w++, color);
}

static void	draw_cara(float x, float y, int color)
{
	const int	size = define_size(NULL, NULL);
	t_imgs		*img;
	int			i;
	int			j;

	x *= size;
	y *= size;
	img = get_mlx()->img;
	i = 0;
	while (i < size / 4)
	{
		j = 0;
		while (j < size / 4)
		{
			if (i * i + j * j <= size * size / 16)
				set_pixel(img, x + i - size / 8, y + j - size / 8, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data, t_imgs *img)
{
	const int	size = define_size(data, img);
	int			x;
	int			y;

	y = 1;
	while (data->map[y + 1])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '0')
				draw_cube(x, y, 0xFF0000, data);
			x++;
		}
		y++;
	}
	draw_cara(data->pos[0], data->pos[1], 0x00FF00);
}
