/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:39:41 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/31 16:15:14 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d_bonus.h"

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
	else if (keycode == 101)
		return (6);
	return (-1);
}

void	trigger_fire(t_mlx *mlx)
{
	if (mlx->fire_animation <= 0)
	{
		mlx->fire = 1;
		mlx->fire_animation = 5;
		mlx->mv_weapon[0] = 10;
		mlx->mv_weapon[1] = 0;
	}
}
