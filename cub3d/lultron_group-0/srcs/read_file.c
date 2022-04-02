/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:42:31 by lultron           #+#    #+#             */
/*   Updated: 2020/09/07 13:22:47 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_parameters_values(t_cub *cub)
{
	cub->map->maplines = NULL;
	cub->map->size = 0;
	cub->map->camera = NULL;
	cub->map->sprites_num = 0;
	mlx_get_screen_size(cub->mlx, &cub->params->resolution_x,
										&cub->params->resolution_y);
	cub->params->path_no = NULL;
	cub->params->path_so = NULL;
	cub->params->path_ea = NULL;
	cub->params->path_we = NULL;
	cub->params->path_s = NULL;
	cub->params->color_floor = -1;
	cub->params->color_ceiling = -1;
}

void	validate_map(t_map *map, int y, int x)
{
	if (y == 0 || y == (map->size - 1) || x == 1 || x == map->map[y][0] ||
		map->map[y + 1][x] == 4 || map->map[y - 1][x] == 4 ||
		map->map[y][x + 1] == 4 || map->map[y][x - 1] == 4 ||
		map->map[y + 1][0] < x || map->map[y - 1][0] < x)
		exit_fail("Invalid map, badly isolated");
	map->map[y][x] = 3;
	if (y != (map->size - 1))
		if (map->map[y + 1][x] == 0 || map->map[y + 1][x] == 2)
			validate_map(map, y + 1, x);
	if (y != 0)
		if (map->map[y - 1][x] == 0 || map->map[y - 1][x] == 2)
			validate_map(map, y - 1, x);
	if (x != map->map[y][0])
		if (map->map[y][x + 1] == 0 || map->map[y][x + 1] == 2)
			validate_map(map, y, x + 1);
	if (x != 1)
		if (map->map[y][x - 1] == 0 || map->map[y][x - 1] == 2)
			validate_map(map, y, x - 1);
}

void	fill_map_array(char *line, int len, int y, t_map *map)
{
	int	x;

	x = 0;
	map->map[y][x] = len;
	while (line[x] != '\0')
	{
		if (ft_isdigit(line[x]))
		{
			map->map[y][x + 1] = line[x] - '0';
			if (map->map[y][x + 1] == 2)
			{
				map->sprites_num--;
				if (!(map->sprites[map->sprites_num] =
										(t_sprite*)malloc(sizeof(t_sprite))))
					exit_fail("Allocation memory for sprite item failed");
				map->sprites[map->sprites_num]->pos_x = (double)x + 1.5;
				map->sprites[map->sprites_num]->pos_y = (double)y + 0.5;
			}
		}
		else
			map->map[y][x + 1] = 4;
		x++;
	}
}

void	parse_map(t_map *map)
{
	int		y;
	int		tmp;

	tmp = map->sprites_num;
	if (!(map->sprites = (t_sprite**)malloc(map->sprites_num *
														sizeof(t_sprite*))))
		exit_fail("Allocation memory for sprites array failed");
	if (!(map->map = (int**)malloc((map->size + 1) * sizeof(int*))))
		exit_fail("Allocation memory for map row array failed");
	y = -1;
	while (++y < map->size)
	{
		if (!(map->map[y] = (int*)malloc((map->maplines->index + 1) *
														sizeof(int))))
			exit_fail("Allocation memory for map array elements failed");
		fill_map_array(map->maplines->content, map->maplines->index, y, map);
		if (map->maplines->next)
			map->maplines = map->maplines->next;
	}
	map->sprites_num = tmp;
	ft_lstclear_2(&map->maplines);
	validate_map(map, (int)map->camera->pos_y, (int)map->camera->pos_x);
}

void	read_file(t_cub *cub, int fd)
{
	char	*line;
	int		len;

	init_parameters_values(cub);
	line = NULL;
	while ((len = get_next_line(fd, &line)) > 0 &&
						(*line != '1' && *line != ' '))
		parse_parameters(cub->params, &line);
	if (len < 0)
		exit_fail("Reading file failed, get_next_line error");
	if (!cub->params->resolution_x || !cub->params->resolution_y
	|| !cub->params->path_no || !cub->params->path_so
	|| !cub->params->path_ea || !cub->params->path_we
	|| !cub->params->path_s || cub->params->color_floor < 0
	|| cub->params->color_ceiling < 0)
		exit_fail("Missing parameters");
	if (*line == '1' || *line == ' ')
	{
		read_map(fd, line, len, cub->map);
		parse_map(cub->map);
		close(fd);
	}
	else
		exit_fail("Missing map");
}
