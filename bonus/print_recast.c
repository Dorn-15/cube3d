/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_recast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:01:49 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/28 15:20:03 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d_bonus.h"

static void	dda(t_data *data, t_imgs *img, t_ray *ray, int screen_x)
{
	int	side;
	int	i;

	i = 0;
	while (data->map[ray->map_y] && data->map[ray->map_y][ray->map_x]
			&& data->map[ray->map_y][ray->map_x] == '0' && i++ < 13)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->dist_x;
			ray->map_x += ray->step_x;
			side = 0;
		}
		else
		{
			ray->side_dist_y += ray->dist_y;
			ray->map_y += ray->step_y;
			side = 1;
		}
	}
	draw_wall(data, img, ray, side);
}

static void	def_step(float x, float y, t_ray *ray)
{
	if (ray->cos_angle < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (x - (int)x) * ray->dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = ((int)x + 1 - x) * ray->dist_x;
	}
	if (ray->sin_angle < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (y - (int)y) * ray->dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = ((int)y + 1 - y) * ray->dist_y;
	}
}

//define ray direction
void	draw_recast(t_data *data, t_imgs *img)
{
	int			i;
	t_ray		ray;
	const float	fov = 1.05f;
	const float	step = fov / img->width;

	i = 0;
	ray.angle = data->r - (fov / 2) - step;
	while (i < img->width)
	{
		ray.x = i;
		ray.map_x = (int)(data->pos[0]);
		ray.map_y = (int)(data->pos[1]);
		ray.angle += step;
		ray.cos_angle = cosf(ray.angle);
		ray.sin_angle = sinf(ray.angle);
		ray.dist_x = fabsf(1 / ray.cos_angle);
		ray.dist_y = fabsf(1 / ray.sin_angle);
		def_step(data->pos[0], data->pos[1], &ray);
		dda(data, img, &ray, i);
		i ++;
	}
}
