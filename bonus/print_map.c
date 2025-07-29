/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:05:12 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/29 17:14:52 by adoireau         ###   ########.fr       */
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

static void	draw_d(int x, int y, int size, t_data *data)
{
	static int	color = 0xFFFF00;
	t_imgs		*img;
	int			w;

	img = get_mlx()->img;
	x *= size;
	y *= size;
	w = 1;
	if (data->map[(y / size) - 1][x / size] == '1')
	{
		x += size-- / 2;
		while (w <= size)
			set_pixel(img, x, y + w++, color);
	}
	else
	{
		y += size-- / 2;
		while (w <= size)
			set_pixel(img, x + w++, y, color);
	}
}

static void	draw_cube(int x, int y, int size, t_data *data)
{
	static int	color = 0xFF0000;
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

static void	draw_cara(float x, float y, int size)
{
	static int	color = 0x00FF00;
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
			set_pixel(img, x + i - size / 8, y + j++ - size / 8, color);
		i++;
	}
}

void	draw_map(t_data *data, t_imgs *img)
{
	static int	size = 0;
	int			x;
	int			y;

	y = 1;
	if (size == 0)
		size = define_size(data, img);
	while (data->map[y + 1])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '0')
				draw_cube(x, y, size, data);
			else if (data->map[y][x] == 'D')
			{
				draw_cube(x, y, size, data);
				draw_d(x, y, size, data);
			}
			x++;
		}
		y++;
	}
	draw_cara(data->pos[0], data->pos[1], size);
}
