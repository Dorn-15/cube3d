/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:03:57 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/29 15:47:15 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d_bonus.h"

static void	check_mv(float x, float y, t_data *data)
{
	if (data->map[(int) data->pos[1]][(int) x] == '0')
		data->pos[0] = x;
	if (data->map[(int) y][(int) data->pos[0]] == '0')
		data->pos[1] = y;
}

static void	mv_calc(float *x, float *y, float r, float speed)
{
	*x += cos(r) * speed;
	*y += sin(r) * speed;
}

void	mv_cara(t_data *data)
{
	const float	pi = 3.14159265358979323846;
	float		pos[2];
	t_mlx		*mlx;

	mlx = get_mlx();
	pos[0] = data->pos[0];
	pos[1] = data->pos[1];
	if (mlx->keys[0] && mlx->keys[1] && !mlx->keys[2] && !mlx->keys[3])
		mv_calc(&pos[0], &pos[1], data->r - pi / 4, 0.04);
	else if (mlx->keys[0] && mlx->keys[3] && !mlx->keys[1] && !mlx->keys[2])
		mv_calc(&pos[0], &pos[1], data->r + pi / 4, 0.04);
	else if (mlx->keys[2] && mlx->keys[3] && !mlx->keys[0] && !mlx->keys[1])
		mv_calc(&pos[0], &pos[1], data->r + pi - pi / 4, 0.03);
	else if (mlx->keys[2] && mlx->keys[1] && !mlx->keys[0] && !mlx->keys[3])
		mv_calc(&pos[0], &pos[1], data->r + pi + pi / 4, 0.03);
	else if (mlx->keys[0] && !mlx->keys[2])
		mv_calc(&pos[0], &pos[1], data->r, 0.05);
	else if (mlx->keys[2] && !mlx->keys[0])
		mv_calc(&pos[0], &pos[1], data->r + pi, 0.04);
	else if (mlx->keys[1] && !mlx->keys[3])
		mv_calc(&pos[0], &pos[1], data->r - pi / 2, 0.03);
	else if (mlx->keys[3] && !mlx->keys[1])
		mv_calc(&pos[0], &pos[1], data->r + pi / 2, 0.03);
	check_mv(pos[0], pos[1], data);
}

void	mv_cam(t_data *data)
{
	const float	pi = 3.14159265358979323846;
	t_mlx		*mlx;

	mlx = get_mlx();
	if (!mlx)
		return ;
	if (mlx->keys[4])
	{
		data->r -= 0.04;
		if (data->r < 0)
			data->r = data->r + (2 * pi);
	}
	if (mlx->keys[5])
	{
		data->r += 0.04;
		if (data->r > (2 * pi))
			data->r = data->r - (2 * pi);
	}
}
