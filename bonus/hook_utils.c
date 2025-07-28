/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:51:48 by ebella            #+#    #+#             */
/*   Updated: 2025/07/28 17:35:18 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d_bonus.h"

int	mouse_press(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (mlx->img->img == NULL)
		return (0);
	if (button == 1)
		trigger_fire(mlx);
	return (1);
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
	else if (keycode == 32)
		trigger_fire(mlx);
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
	if (mlx->fire_animation > 0)
	{
		mlx->fire_animation--;
		if (mlx->fire_animation <= 0)
		{
			mlx->fire = 0;
			mlx->mv_weapon[0] = 0;
		}
		movement = 1;
	}
	if (movement)
		make_img();
	return (0);
}
