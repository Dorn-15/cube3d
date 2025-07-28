/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:20:45 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/28 15:20:32 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d_bonus.h"

t_imgs	*get_img(void)
{
	t_imgs	*img;

	img = malloc(sizeof(t_imgs));
	if (!img)
		return (NULL);
	img->img = NULL;
	img->addr = NULL;
	return (img);
}

t_data	*get_data(void)
{
	static int		i = 0;
	static t_data	*data = NULL;

	if (!data)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (NULL);
		data->map = NULL;
		data->pos[0] = 0;
		while (i < 4)
		{
			data->tex[i] = get_img();
			if (!data->tex[i])
			{
				while (--i >= 0)
					free(data->tex[i]);
				free(data);
				data = NULL;
				return (NULL);
			}
			i++;
		}
	}
	return (data);
}

void	free_data(void)
{
	int		i;
	t_data	*data;
	t_mlx	*mlx;

	data = get_data();
	mlx = get_mlx();
	if (data)
	{
		i = 0;
		while (i < 4)
		{
			if (data->tex[i])
			{
				if (data->tex[i]->img && mlx && mlx->mlx)
					mlx_destroy_image(mlx->mlx, data->tex[i]->img);
				free(data->tex[i]);
			}
			i++;
		}
		if (data->map)
			free_split(data->map);
		free(data);
	}
}

t_mlx	*get_mlx(void)
{
	static t_mlx	*mlx = NULL;
	int				index;

	if (!mlx)
	{
		index = 0;
		mlx = malloc(sizeof(t_mlx));
		if (!mlx)
			return (NULL);
		mlx->mlx = NULL;
		mlx->win = NULL;
		mlx->img = get_img();
		mlx->data = get_data();
		if (mlx->img == NULL || mlx->data == NULL)
			return (free_mlx(), NULL);
		while (index < 6)
			mlx->keys[index++] = 0;
		mlx->fire = 0;
		mlx->fire_animation = 0;
		mlx->mv_weapon[0] = 0;
		mlx->mv_weapon[1] = 0;
	}
	return (mlx);
}

void	free_mlx(void)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	if (mlx)
	{
		if (mlx->data)
			free_data();
		if (mlx->img)
		{
			if (mlx->img->img && mlx->mlx)
				mlx_destroy_image(mlx->mlx, mlx->img->img);
			free(mlx->img);
		}
		free_weapon();
		if (mlx->win && mlx->mlx)
			mlx_destroy_window(mlx->mlx, mlx->win);
		if (mlx->mlx)
		{
			mlx_destroy_display(mlx->mlx);
			free(mlx->mlx);
		}
		free(mlx);
	}
}
