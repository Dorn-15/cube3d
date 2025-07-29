/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:00:54 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/29 15:25:49 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "../libft/include/libft.h"

typedef struct s_map
{
	char			*str;
	struct s_map	*prev;
	struct s_map	*next;
}	t_map;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		pixel_bits;
	int		line_l;
	int		endian;
}	t_img;

typedef struct s_data
{
	char			**map;
	t_img			*tex[4];
	int				sky;
	int				floor;
	float			pos[2];
	float			r;
}	t_data;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_data		*data;
}	t_mlx;

typedef struct s_ray
{
	int		x;
	int		map_x;
	int		map_y;
	float	angle;
	float	cos_angle;
	float	sin_angle;
	float	dist_x;
	float	dist_y;
	int		step_x;
	int		step_y;
	float	side_dist_x;
	float	side_dist_y;
	int		side;
	float	wall_x;
	int		wall_height;
	int		wall_top;
	int		wall_bottom;
}	t_ray;

void	error_message(char *str, int i);

int		init_map_str(t_data *data, t_map *map, int i);
void	free_map(t_map *map);
t_map	*new_mapline(char *str, t_map *prev);
int		pars_img(char *tmp, t_data *data);
int		pars_rgb(char *tmp, t_data *data);
void	parsing(char *str);

int		get_pixel(t_img *img, int x, int y);
void	set_pixel(t_img *img, int x, int y, int color);
int		close_win(void);
void	make_img(void);
int		init_mlx(t_mlx *mlx);

int		key_press(int keycode, t_mlx *mlx);

void	draw_wall(t_data *data, t_img *img, t_ray *ray, int side);
void	draw_recast(t_data *data, t_img *img);

t_data	*get_data(void);
void	free_data(void);
void	reset_data(void);
t_mlx	*get_mlx(void);
void	free_mlx(void);
void	reset_mlx(void);

#endif
