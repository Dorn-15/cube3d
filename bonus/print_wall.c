/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:25:57 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/28 15:20:15 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d_bonus.h"

static int	calc_fade(t_ray *ray, t_imgs *img, int i, int color)
{
	int		c[3];
	float	fade;
	t_mlx	*mlx;
	int		j;

	mlx = get_mlx();
	c[0] = (color >> 16) & 0xFF;
	c[1] = (color >> 8) & 0xFF;
	c[2] = color & 0xFF;
	if (i < ray->wall_top || i > ray->wall_bottom)
		fade = fabsf((float)(img->height / 2 - i) / (img->height / 2));
	else if (ray->wall_dis < 7)
		fade = (7 - ray->wall_dis) / 7;
	else
		fade = 0;
	c[0] *= fade * (mlx->fire + 1);
	c[1] *= fade * (mlx->fire * 0.5 + 1);
	c[2] *= fade * (mlx->fire * 0.2 + 1);
	j = 0;
	while (j < 3)
		if (c[j++] > 255)
			c[j - 1] = 255;
	color = (c[0] << 16) | (c[1] << 8) | c[2];
	return (color);
}

static int	print_texture(t_ray *ray, float y, t_imgs *img)
{
	const int	x = ray->wall_x * img->width;
	int			color;

	y = (y - ray->wall_top) / (ray->wall_bottom - ray->wall_top) * img->height;
	if (x < img->width && y < img->height)
		color = get_pixel(img, x, y);
	else
		color = 0x000000;
	return (color);
}

static void	print_wall(t_data *data, t_imgs *img, t_ray *ray, int side)
{
	int		i;
	int		color;

	i = -1;
	while (++i < img->height)
	{
		if (i < ray->wall_top)
			color = data->sky;
		else if (i > ray->wall_bottom)
			color = data->floor;
		else
		{
			if (side == 0 && ray->cos_angle < 0)
				color = print_texture(ray, i, data->tex[2]);
			else if (side == 0)
				color = print_texture(ray, i, data->tex[3]);
			else if (ray->sin_angle < 0)
				color = print_texture(ray, i, data->tex[0]);
			else
				color = print_texture(ray, i, data->tex[1]);
		}
		color = calc_fade(ray, img, i, color);
		set_pixel(img, ray->x, i, color);
	}
}

void	draw_wall(t_data *data, t_imgs *img, t_ray *ray, int side)
{
	int		wall_height;

	if (side == 0)
		ray->wall_dis = (ray->map_x - data->pos[0] + (1 - ray->step_x) / 2.0f)
			/ ray->cos_angle;
	else
		ray->wall_dis = (ray->map_y - data->pos[1] + (1 - ray->step_y) / 2.0f)
			/ ray->sin_angle;
	if (ray->wall_dis <= 0)
		ray->wall_dis = 1.0f;
	if (side == 0)
		ray->wall_x = data->pos[1] + ray->wall_dis * ray->sin_angle;
	else
		ray->wall_x = data->pos[0] + ray->wall_dis * ray->cos_angle;
	ray->wall_x -= floorf(ray->wall_x);
	wall_height = (int)(img->height / ray->wall_dis);
	ray->wall_top = (img->height / 2) - (wall_height / 2);
	ray->wall_bottom = (img->height / 2) + (wall_height / 2);
	print_wall(data, img, ray, side);
}
