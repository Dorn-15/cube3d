/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:39:41 by adoireau          #+#    #+#             */
/*   Updated: 2025/08/11 20:01:24 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	get_key_index(int keycode)
{
	if (keycode == 119)
		return (0);
	else if (keycode == 97)
		return (1);
	else if (keycode == 115)
		return (2);
	else if (keycode == 100)
		return (3);
	else if (keycode == 65361)
		return (4);
	else if (keycode == 65363)
		return (5);
	return (-1);
}

int	key_release(int keycode, t_mlx *mlx)
{
	int	index;

	index = get_key_index(keycode);
	if (index != -1)
		mlx->keys[index] = 0;
	return (1);
}

int	key_press(int keycode, t_mlx *mlx)
{
	int	index;

	if (mlx->img->img == NULL)
		return (0);
	if (keycode == 65307)
		close_win();
	else
	{
		index = get_key_index(keycode);
		if (index != -1)
			mlx->keys[index] = 1;
	}
	return (1);
}

int	handle_loop(t_mlx *mlx)
{
	int	movement;

	movement = 0;
	if (mlx->img->img == NULL)
		return (0);
	if (mlx->keys[0] || mlx->keys[1] || mlx->keys[2] || mlx->keys[3])
	{
		mv_cara(mlx->data);
		movement = 1;
	}
	if (mlx->keys[4] || mlx->keys[5])
	{
		mv_cam(mlx->data);
		movement = 1;
	}
	if (movement)
		make_img();
	return (0);
}
