/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:42:31 by lultron           #+#    #+#             */
/*   Updated: 2020/09/07 13:22:47 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		bubble_sort(int *list, double *content, int elements)
{
	int		i;
	int		add;
	int		list_copy;
	double	content_copy;

	i = 0;
	while (i < elements)
	{
		add = i;
		while (++add < elements)
		{
			if (content[i] < content[add])
			{
				list_copy = list[i];
				list[i] = list[add];
				list[add] = list_copy;
				content_copy = content[i];
				content[i] = content[add];
				content[add] = content_copy;
			}
		}
		i++;
	}
}

void		order_sprites(int *sprite_order, t_map *map)
{
	double	sprite_distance[map->sprites_num];
	int		i;

	i = 0;
	while (i < map->sprites_num)
	{
		sprite_order[i] = i;
		sprite_distance[i] = (map->camera->pos_x - map->sprites[i]->pos_x) *
			(map->camera->pos_x - map->sprites[i]->pos_x) +
			(map->camera->pos_y - map->sprites[i]->pos_y) *
			(map->camera->pos_y - map->sprites[i]->pos_y);
		i++;
	}
	bubble_sort(sprite_order, sprite_distance, map->sprites_num);
}

static void	print_stripe(t_sprite_ray *ray, t_images *images, t_params *params)
{
	int	y;
	int	d;
	int	color;

	ray->tex_x = (int)(256 * (ray->stripe - (-ray->sprite_height / 2
					+ ray->sprite_screen_x)) *
			images->sprite->width / ray->sprite_height) / 256;
	if (ray->transform_y < 0 || ray->transform_y > ray->wall_z[ray->stripe])
		return ;
	y = ray->draw_start_y;
	while (y < ray->draw_end_y)
	{
		d = y * 256 - params->resolution_y *
			128 + ray->sprite_height * 128;
		ray->tex_y = ((d * images->sprite->height) /
				ray->sprite_height) / 256;
		color = images->sprite->addr[images->sprite->width *
			ray->tex_y + ray->tex_x];
		if (color != 0)
			images->screen->addr[y * params->resolution_x +
				ray->stripe] = color;
		y++;
	}
}

static void	calculate_params(t_camera *player, t_sprite_ray *ray,
									t_params *params)
{
	ray->transform_x = ray->inv_det * (player->dir_y * ray->sprite_x -
			player->dir_x * ray->sprite_y);
	ray->transform_y = ray->inv_det * (-player->plane_y * ray->sprite_x +
			player->plane_x * ray->sprite_y);
	ray->sprite_screen_x = (int)((params->resolution_x / 2) *
			(1 + ray->transform_x / ray->transform_y));
	ray->sprite_height = abs((int)(params->resolution_y /
				ray->transform_y));
	ray->draw_start_y = params->resolution_y / 2 - ray->sprite_height / 2;
	ray->draw_start_y = (ray->draw_start_y < 0) ? 0 : ray->draw_start_y;
	ray->draw_end_y = params->resolution_y / 2 + ray->sprite_height / 2;
	ray->draw_end_y = (ray->draw_end_y >= params->resolution_y) ?
		params->resolution_y - 1 : ray->draw_end_y;
	ray->draw_start_x = ray->sprite_screen_x - ray->sprite_height / 2;
	ray->draw_start_x = (ray->draw_start_x < 0) ? 0 : ray->draw_start_x;
	ray->draw_end_x = ray->sprite_screen_x + ray->sprite_height / 2;
	ray->draw_end_x = (ray->draw_end_x >= params->resolution_x) ?
		params->resolution_x - 1 : ray->draw_end_x;
}

void		render_sprites(t_cub *cub)
{
	int		i;

	cub->spr_ray->inv_det = 1.0 / (cub->map->camera->plane_x *
			cub->map->camera->dir_y -
			cub->map->camera->plane_y *
			cub->map->camera->dir_x);
	i = -1;
	while (++i < cub->map->sprites_num)
	{
		cub->spr_ray->sprite_x =
				cub->map->sprites[cub->spr_ray->sprite_order[i]]->pos_x -
						cub->map->camera->pos_x;
		cub->spr_ray->sprite_y =
				cub->map->sprites[cub->spr_ray->sprite_order[i]]->pos_y -
						cub->map->camera->pos_y;
		calculate_params(cub->map->camera, cub->spr_ray,
				cub->params);
		cub->spr_ray->stripe = cub->spr_ray->draw_start_x - 1;
		while (++cub->spr_ray->stripe < cub->spr_ray->draw_end_x)
			print_stripe(cub->spr_ray, cub->images,
					cub->params);
	}
}
