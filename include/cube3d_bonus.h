/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:00:54 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/28 17:32:49 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_BONUS_H
# define CUBE3D_BONUS_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include "../libft/include/libft.h"
# include "mlx_int.h"

typedef struct s_map
{
	char			*str;
	struct s_map	*prev;
	struct s_map	*next;
}	t_map;

typedef struct s_imgs
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		pixel_bits;
	int		line_l;
	int		endian;
}	t_imgs;

typedef struct s_data
{
	char			**map;
	t_imgs			*tex[4];
	int				sky;
	int				floor;
	float			pos[2];
	float			r;
}	t_data;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_imgs		*img;
	t_imgs		*weapon[2];
	int			fire;
	int			fire_animation;
	int			mv_weapon[2];
	t_data		*data;
	int			keys[6];
}	t_mlx;

typedef struct s_ray
{
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
	int		x;
	int		side;
	float	wall_x;
	int		wall_top;
	int		wall_bottom;
	float	wall_dis;
}	t_ray;

void	error_message(char *str, int i);

int		init_map_str(t_data *data, t_map *map, int i);
void	free_map(t_map *map);
t_map	*new_mapline(char *str, t_map *prev);
int		pars_img(char *tmp, t_data *data);
int		pars_rgb(char *tmp, t_data *data);
void	parsing(char *str);

t_imgs	*get_img(void);
int		get_pixel(t_imgs *img, int x, int y);
void	set_pixel(t_imgs *img, int x, int y, int color);
int		close_win(void);
void	make_img(void);
int		init_mlx(t_mlx *mlx);

int		key_press(int keycode, t_mlx *mlx);
int		key_release(int keycode, t_mlx *mlx);
int		handle_loop(t_mlx *mlx);
int		mouse_press(int button, int x, int y, t_mlx *mlx);

int		get_key_index(int keycode);
void	mv_cara(t_data *data);
void	mv_cam(t_data *data);
void	trigger_fire(t_mlx *mlx);

long	get_current_time(void);
int		render_loop(void *param);

void	draw_wall(t_data *data, t_imgs *img, t_ray *ray, int side);
void	draw_recast(t_data *data, t_imgs *img);
void	draw_map(t_data *data, t_imgs *img);
void	draw_weapon(t_imgs *img, t_imgs *weapon);


t_data	*get_data(void);
void	free_data(void);
void	reset_data(void);
void	free_weapon(void);
int		set_weapon(void);
t_mlx	*get_mlx(void);
void	free_mlx(void);
void	reset_mlx(void);

int	handle_focus_out(t_mlx *mlx);
int	handle_focus_in(t_mlx *mlx);

#endif
