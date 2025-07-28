/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:30:34 by ebella            #+#    #+#             */
/*   Updated: 2025/07/28 17:34:50 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d_bonus.h"

int	handle_focus_out(t_mlx *mlx)
{
	Display	*d;

	d = ((t_xvar *)mlx->mlx)->display;
	XUngrabPointer(d, CurrentTime);
	XFlush(d);
	return (0);
}

int	handle_focus_in(t_mlx *mlx)
{
	Display	*d;
	Window	w;

	w = ((t_win_list *)mlx->win)->window;
	d = ((t_xvar *)mlx->mlx)->display;
	XGrabPointer(d, w, True,
		ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync,
		GrabModeAsync, w, None, CurrentTime);
	mlx_mouse_hide(mlx->mlx, mlx->win);
	XFlush(d);
	return (0);
}
