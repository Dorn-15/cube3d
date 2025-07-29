/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:25:57 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/29 15:24:25 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	print_texture(t_ray *ray, float y, t_img *img)
{
	const int	x = ray->wall_x * img->width;
	int			color;

	y = (y - ray->wall_top) / ray->wall_height * img->height;
	return (get_pixel(img, x, y));
}

static void	print_wall(t_data *data, t_img *img, t_ray *ray, int side)
{
	int		i;
	int		color;
	t_img	*tex;

	if (side == 0 && ray->cos_angle < 0)
		tex = data->tex[2];
	else if (side == 0)
		tex = data->tex[3];
	else if (ray->sin_angle < 0)
		tex = data->tex[0];
	else
		tex = data->tex[1];
	i = 0;
	while(i < img->height && i < ray->wall_top)
		set_pixel(img, ray->x, i++, data->sky);
	while(i < img->height && i < ray->wall_bottom)
	{
		set_pixel(img, ray->x, i, print_texture(ray, i, tex));
		i++;
	}
	while(i < img->height)
		set_pixel(img, ray->x, i++, data->floor);
}

void	draw_wall(t_data *data, t_img *img, t_ray *ray, int side)
{
	float	wall_dis;

	if (side == 0)
		wall_dis = (ray->map_x - data->pos[0] + (1 - ray->step_x) / 2.0f)
			/ ray->cos_angle;
	else
		wall_dis = (ray->map_y - data->pos[1] + (1 - ray->step_y) / 2.0f)
			/ ray->sin_angle;
	if (wall_dis <= 0)
		wall_dis = 0.1f;
	if (side == 0)
		ray->wall_x = data->pos[1] + wall_dis * ray->sin_angle;
	else
		ray->wall_x = data->pos[0] + wall_dis * ray->cos_angle;
	ray->wall_x -= floorf(ray->wall_x);
	ray->wall_height = (int)(img->height / wall_dis);
	ray->wall_top = (img->height / 2) - (ray->wall_height / 2);
	ray->wall_bottom = (img->height / 2) + (ray->wall_height / 2);
	print_wall(data, img, ray, side);
}
