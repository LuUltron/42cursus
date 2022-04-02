/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:42:31 by lultron           #+#    #+#             */
/*   Updated: 2020/09/07 13:22:47 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	vertical_movement(t_map *map, double movement_speed,
		double dir_x, double dir_y)
{
	if (map->map[(int)map->camera->pos_y]
			[(int)(map->camera->pos_x + dir_x * 1)] == 3)
		map->camera->pos_x += dir_x * movement_speed;
	if (map->map[(int)(map->camera->pos_y + dir_y * 1)]
			[(int)map->camera->pos_x] == 3)
		map->camera->pos_y += dir_y * movement_speed;
}

void	horizontal_movement(t_map *map, double movement_speed,
		double plane_x, double plane_y)
{
	if (map->map[(int)map->camera->pos_y]
			[(int)(map->camera->pos_x + plane_x * 1)] == 3)
		map->camera->pos_x += plane_x * movement_speed;
	if (map->map[(int)(map->camera->pos_y + plane_y * 1)]
			[(int)map->camera->pos_x] == 3)
		map->camera->pos_y += plane_y * movement_speed;
}

void	rotation(t_camera *camera, double rotation_speed)
{
	double dir_y_copy;
	double plane_y_copy;

	dir_y_copy = camera->dir_y;
	camera->dir_y = camera->dir_y * cos(rotation_speed)
		- camera->dir_x * sin(rotation_speed);
	camera->dir_x = dir_y_copy * sin(rotation_speed) + camera->dir_x *
		cos(rotation_speed);
	plane_y_copy = camera->plane_y;
	camera->plane_y = camera->plane_y * cos(rotation_speed) -
		camera->plane_x * sin(rotation_speed);
	camera->plane_x = plane_y_copy * sin(rotation_speed) +
		camera->plane_x * cos(rotation_speed);
}

void	trigger_events(t_cub *cub)
{
	if (cub->key->w == 1)
		vertical_movement(cub->map, cub->mov_speed,
				cub->map->camera->dir_x,
				cub->map->camera->dir_y);
	if (cub->key->s == 1)
		vertical_movement(cub->map, cub->mov_speed,
				-cub->map->camera->dir_x,
				-cub->map->camera->dir_y);
	if (cub->key->a == 1)
		horizontal_movement(cub->map, cub->mov_speed,
				-cub->map->camera->plane_x,
				-cub->map->camera->plane_y);
	if (cub->key->d == 1)
		horizontal_movement(cub->map, cub->mov_speed,
				cub->map->camera->plane_x,
				cub->map->camera->plane_y);
	if (cub->key->left == 1)
		rotation(cub->map->camera, cub->rotate_speed);
	if (cub->key->right == 1)
		rotation(cub->map->camera, -cub->rotate_speed);
	if (cub->key->esc == 1)
		exit_success(cub);
}

int		actualize(t_cub *cub)
{
	trigger_events(cub);
	render(cub, cub->ray, cub->images, cub->spr_ray);
	order_sprites(cub->spr_ray->sprite_order, cub->map);
	render_sprites(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->images->screen->img, 0, 0);
	return (1);
}
