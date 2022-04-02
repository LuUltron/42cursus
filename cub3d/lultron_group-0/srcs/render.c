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

void	init_rendering_values(t_cub *cub)
{
	cub->key->a = 0;
	cub->key->w = 0;
	cub->key->s = 0;
	cub->key->d = 0;
	cub->key->left = 0;
	cub->key->right = 0;
	cub->key->esc = 0;
	cub->mov_speed = 0.05;
	cub->rotate_speed = 0.02;
	ft_bzero(cub->spr_ray->sprite_order, cub->map->sprites_num);
	ft_bzero(cub->spr_ray->wall_z, cub->params->resolution_x);
}

int		key_pressed(int keycode, t_key *key)
{
	if (keycode == A_KEY)
		key->a = 1;
	if (keycode == W_KEY)
		key->w = 1;
	if (keycode == S_KEY)
		key->s = 1;
	if (keycode == D_KEY)
		key->d = 1;
	if (keycode == LEFT_KEY)
		key->left = 1;
	if (keycode == RIGHT_KEY)
		key->right = 1;
	if (keycode == ESC_KEY)
		key->esc = 1;
	return (1);
}

int		key_released(int keycode, t_key *key)
{
	if (keycode == A_KEY)
		key->a = 0;
	if (keycode == W_KEY)
		key->w = 0;
	if (keycode == S_KEY)
		key->s = 0;
	if (keycode == D_KEY)
		key->d = 0;
	if (keycode == LEFT_KEY)
		key->left = 0;
	if (keycode == RIGHT_KEY)
		key->right = 0;
	if (keycode == ESC_KEY)
		key->esc = 0;
	return (1);
}

void	print_column(int x, t_ray *ray, t_params *params,
		t_images *images)
{
	int		y;
	double	texture_y;
	double	step;
	double	texture_pos;

	y = -1;
	while (++y < ray->draw_start)
		images->screen->addr[y * params->resolution_x + x] =
														params->color_ceiling;
	step = 1.0 * ray->texture->height / ray->wall_height;
	texture_pos = (ray->draw_start - params->resolution_y / 2 +
			ray->wall_height / 2) * step;
	while (y < ray->draw_end - 1)
	{
		texture_y = (int)texture_pos & (ray->texture->height - 1);
		texture_pos += step;
		images->screen->addr[y * params->resolution_x + x] =
			ray->texture->addr[(int)(texture_y * ray->texture->width
					+ ray->texture_x)];
		y++;
	}
	while (y < (params->resolution_y - 1))
		images->screen->addr[y++ * params->resolution_x + x] =
														params->color_floor;
}

void	render(t_cub *cub, t_ray *ray, t_images *images,
		t_sprite_ray *s_ray)
{
	int	x;

	x = -1;
	while (++x < cub->params->resolution_x)
	{
		get_side_dist(x, (double)cub->params->resolution_x, ray,
				cub->map->camera);
		get_hit(ray, cub->map->map, cub->map->size);
		get_wall(ray, cub->map->camera, images);
		get_wall_dist(ray, cub->map->camera, s_ray, x);
		get_wall_height(ray, cub->params);
		ray->texture_x = (int)(ray->wall_hit_x * (double)(ray->texture->width));
		if (ray->texture_x < 0)
			ray->texture_x = ray->texture->width - ray->texture_x - 1;
		print_column(x, ray, cub->params, images);
	}
}
