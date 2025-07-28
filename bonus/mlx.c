/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:05:18 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/28 15:19:44 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d_bonus.h"

int	get_pixel(t_imgs *img, int x, int y)
{
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0);
	return (*(int *)(img->addr
		+ (y * img->line_l)
		+ (x * (img->pixel_bits / 8))));
}

void	set_pixel(t_imgs *img, int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	*(int *)(img->addr
			+ (y * img->line_l)
			+ (x * (img->pixel_bits / 8)))
		= color;
}

int	close_win(void)
{
	free_mlx();
	exit(0);
}

void	make_img(void)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	draw_recast(mlx->data, mlx->img);
	draw_map(mlx->data, mlx->img);
	draw_weapon(mlx->img, mlx->weapon[mlx->fire]);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
}

int	init_mlx(t_mlx *mlx)
{
	const int	size = 800;

	mlx->win = mlx_new_window(mlx->mlx, size, size, "Cube3D");
	if (mlx->win == NULL)
		return (0);
	mlx->img->img = mlx_new_image(mlx->mlx, size, size);
	if (mlx->img->img == NULL)
		return (0);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, &mlx->img->pixel_bits,
			&mlx->img->line_l, &mlx->img->endian);
	if (mlx->img->addr == NULL)
		return (0);
	mlx->img->width = size;
	mlx->img->height = size;
	make_img();
	return (1);
}
