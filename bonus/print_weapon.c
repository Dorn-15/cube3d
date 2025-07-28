/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_weapon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:00:31 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/28 15:20:23 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d_bonus.h"

int	set_weapon(void)
{
	t_mlx		*mlx;
	static char	*str[2] = {"./bonus/gun2.xpm", "./bonus/gunf2.xpm"};
	int			i;

	mlx = get_mlx();
	mlx->weapon[0] = get_img();
	mlx->weapon[1] = get_img();
	if (!mlx->weapon[0] || !mlx->weapon[1])
		error_message("weapon memory not allow", 0);
	i = 0;
	while (i < 2)
	{
		mlx->weapon[i]->img = mlx_xpm_file_to_image(mlx->mlx, str[i],
				&mlx->weapon[i]->width, &mlx->weapon[i]->height);
		if (!mlx->weapon[i]->img)
			error_message("weapon file", 0);
		mlx->weapon[i]->addr = mlx_get_data_addr(mlx->weapon[i]->img,
				&mlx->weapon[i]->pixel_bits, &mlx->weapon[i]->line_l,
				&mlx->weapon[i]->endian);
		if (!mlx->weapon[i]->addr)
			error_message("weapon data", 0);
		i++;
	}
	return (1);
}

void	free_weapon(void)
{
	t_mlx	*mlx;
	int		i;

	mlx = get_mlx();
	i = 0;
	while (i < 2)
	{
		if (mlx->weapon[i])
		{
			if (mlx->weapon[i]->img && mlx->mlx)
				mlx_destroy_image(mlx->mlx, mlx->weapon[i]->img);
			free(mlx->weapon[i]);
		}
		i++;
	}
}

static void	print_cursor(t_imgs *img)
{
	int	i;
	int	x;
	int	y;

	i = 2;
	x = img->width / 2;
	y = img->height / 2;
	while (i < 8)
	{
		set_pixel(img, x + i, y, 0xFF0000);
		set_pixel(img, x - i, y, 0xFF0000);
		set_pixel(img, x, y + i, 0xFF0000);
		set_pixel(img, x, y - i, 0xFF0000);
		i++;
	}
}

static int	animation(void)
{
	static float	pos[2] = {0, 0};
	static int		x[8] = {0, 2, 5, 2, 0, -2, -5, -2};
	static int		n = 0;
	static int		t = 0;
	t_data			*data;

	data = get_data();
	if (pos[0] != data->pos[0] || pos[1] != data->pos[1])
	{
		pos[0] = data->pos[0];
		pos[1] = data->pos[1];
		t++;
		if (t % 15 == 0)
			n = (n + 1) % 7;
	}
	return (x[n]);
}

void	draw_weapon(t_imgs *img, t_imgs *weapon)
{
	int			x;
	int			y;
	int			color;
	const int	w = (img->width / 2) - (weapon->width / 2)
		- get_mlx()->mv_weapon[1] + animation();
	const int	h = img->height - (weapon->height * 0.8)
		- get_mlx()->mv_weapon[0];

	y = 0;
	while (y < weapon->height && y + h < img->height)
	{
		x = 0;
		while (x < weapon->width)
		{
			color = get_pixel(weapon, x, y);
			if (color != 0xFFFFFF)
				set_pixel(img, x + w, y + h, color);
			x++;
		}
		y++;
	}
	print_cursor(img);
}
