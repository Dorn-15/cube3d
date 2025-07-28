/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:00:01 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/28 17:32:05 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d_bonus.h"

int	main(int ac, char **av)
{
	t_mlx	*mlx;

	if (ac != 2)
		error_message("Wrong number of arguments", 1);
	mlx = get_mlx();
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL || set_weapon() == 0)
	{
		free_mlx();
		return (0);
	}
	parsing(av[1]);
	if (!init_mlx(mlx))
		close_win();
	mlx_hook(mlx->win, 2, 1, key_press, mlx);
	mlx_hook(mlx->win, 3, 2, key_release, mlx);
	mlx_hook(mlx->win, FocusOut, FocusChangeMask, handle_focus_out, mlx);
	mlx_hook(mlx->win, FocusIn, FocusChangeMask, handle_focus_in, mlx);
	mlx_hook(mlx->win, 4, 4, mouse_press, mlx);
	mlx_hook(mlx->win, 17, 0, close_win, NULL);
	mlx_loop_hook(mlx->mlx, handle_loop, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
