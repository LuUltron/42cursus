/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:42:31 by lultron           #+#    #+#             */
/*   Updated: 2020/09/07 13:22:47 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_spr_ray(t_sprite_ray *spr_ray)
{
	if (spr_ray->wall_z)
		free(spr_ray->wall_z);
	if (spr_ray->sprite_order)
		free(spr_ray->sprite_order);
	free(spr_ray);
}

void	free_map(t_map *map)
{
	if (map->maplines)
		ft_lstclear_2(&map->maplines);
	if (map->map)
	{
		while (map->size >= 0)
		{
			if (map->map[map->size])
				free(map->map[map->size]);
			map->size--;
		}
		free(map->map);
	}
	if (map->camera)
		free(map->camera);
	while (map->sprites_num-- > 0)
	{
		if (map->sprites)
			free(map->sprites[map->sprites_num]);
	}
	if (map->sprites)
		free(map->sprites);
	free(map);
}

void	free_params(t_params *params)
{
	if (params->path_no)
		free(params->path_no);
	if (params->path_so)
		free(params->path_so);
	if (params->path_ea)
		free(params->path_ea);
	if (params->path_we)
		free(params->path_we);
	if (params->path_s)
		free(params->path_s);
	free(params);
}

void	destroy_images(t_images *images, void *mlx)
{
	if (images->screen->img)
		mlx_destroy_image(mlx, images->screen->img);
	if (images->north->img)
		mlx_destroy_image(mlx, images->north->img);
	if (images->south->img)
		mlx_destroy_image(mlx, images->south->img);
	if (images->west->img)
		mlx_destroy_image(mlx, images->west->img);
	if (images->east->img)
		mlx_destroy_image(mlx, images->east->img);
	if (images->sprite->img)
		mlx_destroy_image(mlx, images->sprite->img);
}

void	free_images(t_images *images)
{
	if (images->screen)
		free(images->screen);
	if (images->north)
		free(images->north);
	if (images->south)
		free(images->south);
	if (images->west)
		free(images->west);
	if (images->east)
		free(images->east);
	if (images->sprite)
		free(images->sprite);
	free(images);
}
