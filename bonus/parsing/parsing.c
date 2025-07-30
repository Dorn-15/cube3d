/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:09:10 by adoireau          #+#    #+#             */
/*   Updated: 2025/07/30 17:20:35 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d_bonus.h"

static int	pars_map(int fd, t_data *data, char **str)
{
	t_map	*map;
	t_map	*last;
	t_map	*new;
	int		i;

	i = 0;
	last = NULL;
	map = NULL;
	while (*str)
	{
		new = new_mapline(*str, last);
		if (!new)
			return (free_map(map), 0);
		if (last)
			last->next = new;
		else
			map = new;
		last = new;
		free(*str);
		*str = ft_get_next_line(fd);
		i++;
	}
	if (!init_map_str(data, map, i))
		return (free_map(map), 0);
	return (free_map(map), 1);
}

static int	pars_element(int fd, t_data *data, char **str)
{
	char		*tmp;
	int			elem;

	elem = 0;
	while ((*str))
	{
		tmp = ft_strtrim(*str, "\n \t");
		if (!tmp)
			continue ;
		if (!tmp[0])
			free(tmp);
		else if ((pars_img(tmp, data) || pars_rgb(tmp, data)) && ++elem <= 7)
			free(tmp);
		else
		{
			free(tmp);
			break ;
		}
		free(*str);
		*str = ft_get_next_line(fd);
	}
	return (elem);
}

static void	pars_file(int fd)
{
	char	*str;
	t_data	*data;

	data = get_data();
	str = ft_get_next_line(fd);
	if (pars_element(fd, data, &str) != 7)
	{
		free(str);
		close(fd);
		error_message("Wrong element", 2);
	}
	if (!str)
	{
		close(fd);
		error_message("Map is empty", 3);
	}
	if (!pars_map(fd, data, &str))
	{
		free(str);
		close(fd);
		error_message("Invalid map", 3);
	}
	close(fd);
}

static char	*test_name(char *str)
{
	char	*tmp;
	int		i;

	tmp = ft_strtrim(str, " \t\n");
	if (!tmp)
		return (NULL);
	i = ft_strlen(tmp);
	if (i <= 4 || ft_strcmp((tmp + i - 4), ".cub"))
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

void	parsing(char *str)
{
	char	*tmp;
	int		fd;

	if (!str || !str[0])
		error_message("Arg is empty", 1);
	tmp = test_name(str);
	if (!tmp)
		error_message("Path isn't path.cub'", 1);
	fd = open(tmp, O_RDONLY);
	if (fd == -1)
	{
		perror(tmp);
		free(tmp);
		exit (1);
	}
	free(tmp);
	pars_file(fd);
	ft_get_next_line(-2);
}
