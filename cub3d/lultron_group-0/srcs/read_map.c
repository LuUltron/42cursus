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

static t_camera	*set_dir_plane(double dir_x, double dir_y,
							double plane_x, double plane_y)
{
	t_camera	*camera;

	if (!(camera = (t_camera*)malloc(sizeof(t_camera))))
		exit_fail("Allocation memory for camera struct failed");
	camera->dir_x = dir_x;
	camera->dir_y = dir_y;
	camera->plane_x = plane_x;
	camera->plane_y = plane_y;
	return (camera);
}

void			validline_setcamera(t_camera **camera, char ptr,
													int pos_x, int pos_y)
{
	if (!ft_strchr("012 NSEW", ptr))
		exit_fail("Illegal chars in the map");
	if (ft_isalpha(ptr))
	{
		if (*camera != NULL)
			exit_fail("More than one player");
		if (ptr == 'N')
			*camera = set_dir_plane(0, -1, 0.66, 0);
		else if (ptr == 'S')
			*camera = set_dir_plane(0, 1, -0.66, 0);
		else if (ptr == 'E')
			*camera = set_dir_plane(1, 0, 0, 0.66);
		else if (ptr == 'W')
			*camera = set_dir_plane(-1, 0, 0, -0.66);
		(*camera)->pos_x = pos_x + 1.5;
		(*camera)->pos_y = pos_y + 0.5;
	}
}

t_list2			*addlst_mapline(t_map *map, char *line, int i, t_list2 *tail)
{
	t_list2		*new;

	i = (!ft_strrchr(line, '1')) ? i :
		i + 1 - ft_strlen(ft_strrchr(line, '1'));
	if (!(new = ft_lstnew_2(line, i)))
		exit_fail("Allocation memory for new maplines list element failed");
	new->prev = tail;
	tail = new;
	if (tail->prev)
		tail->prev->next = new;
	if (!map->maplines)
		map->maplines = new;
	map->size++;
	return (tail);
}

void			read_map(int fd, char *line, int i, t_map *map)
{
	t_list2		*tail;

	tail = NULL;
	while (i > 0)
	{
		i = 0;
		while (line[i] != '\0')
		{
			validline_setcamera(&map->camera, line[i], i, map->size);
			map->sprites_num += (line[i] == '2') ? 1 : 0;
			i++;
		}
		if (line[0] != '\0')
			tail = addlst_mapline(map, line, i, tail);
		else
			exit_fail("Empty line while reading map");
		free(line);
		i = get_next_line(fd, &line);
	}
	free(line);
	if (i < 0)
		exit_fail("Reading file failed, get_next_line error while read map");
	if (!map->camera)
		exit_fail("No any player");
}
