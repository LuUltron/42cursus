/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:42:31 by lultron           #+#    #+#             */
/*   Updated: 2020/09/07 13:22:47 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*create_texture(void *mlx, char *path)
{
	t_img		*texture;

	if (!(texture = (t_img*)malloc(sizeof(t_img))))
		exit_fail("Allocation memory for texture struct failed");
	if (!(texture->img = mlx_xpm_file_to_image(mlx, path,
					&texture->width, &texture->height)))
		exit_fail("Creation texture img failed, invalid path");
	texture->addr = (int*)mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	return (texture);
}

static t_images	*create_images(void *mlx, t_params *params)
{
	t_images	*images;

	if (!(images = (t_images*)malloc(sizeof(t_images))))
		exit_fail("Allocation memory for images struct failed");
	if (!(images->screen = (t_img*)malloc(sizeof(t_img))))
		exit_fail("Allocation memory for screen image failed");
	if (!(images->screen->img = mlx_new_image(mlx, params->resolution_x,
					params->resolution_y)))
		exit_fail("Creation new image failed");
	images->screen->addr = (int*)mlx_get_data_addr(images->screen->img,
			&images->screen->bpp, &images->screen->size_line,
			&images->screen->endian);
	ft_bzero(images->screen->addr,
			(params->resolution_x * params->resolution_y));
	images->north = create_texture(mlx, params->path_no);
	images->south = create_texture(mlx, params->path_so);
	images->east = create_texture(mlx, params->path_ea);
	images->west = create_texture(mlx, params->path_we);
	images->sprite = create_texture(mlx, params->path_s);
	return (images);
}

void			init(char *file_name, t_cub *cub)
{
	int			fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		exit_fail("Invalid file");
	if (!(cub->params = (t_params*)malloc(sizeof(t_params))))
		exit_fail("Allocation memory for t_params struct failed");
	if (!(cub->map = (t_map*)malloc(sizeof(t_map))))
		exit_fail("Allocation memory for t_map struct failed");
	cub->map->file_name = file_name;
	read_file(cub, fd);
	if (!(cub->mlx = mlx_init()))
		exit_fail("mlx_init failed");
	if (!(cub->ray = (t_ray*)malloc(sizeof(t_ray))))
		exit_fail("Allocation memory for ray struct failed");
	if (!(cub->spr_ray = (t_sprite_ray*)malloc(sizeof(t_sprite_ray))))
		exit_fail("Allocation memory for sprite_ray struct failed");
	cub->spr_ray->sprite_order = (int*)malloc(cub->map->sprites_num *
															sizeof(int));
	cub->spr_ray->wall_z = (double*)malloc(cub->params->resolution_x *
															sizeof(double));
	if (!(cub->spr_ray->sprite_order && cub->spr_ray->wall_z))
		exit_fail("Couldn't allocate memory for sprite arrays");
	cub->images = create_images(cub->mlx, cub->params);
	if (!(cub->key = (t_key*)malloc(sizeof(t_key))))
		exit_fail("Allocation memory for t_key struct failed");
}

int				main(int argc, char **argv)
{
	static t_cub	cub;

	if (argc != 2 && argc != 3)
		exit_fail("Invalid arguments");
	init(argv[1], &cub);
	if (argc == 2)
	{
		cub.win = mlx_new_window(cub.mlx, cub.params->resolution_x,
										cub.params->resolution_y, "Cub3D");
		if (cub.win == NULL)
			exit_fail("Window open failed");
		init_rendering_values(&cub);
		mlx_hook(cub.win, X_BTN, 1L << 17, &exit_success, &cub);
		mlx_hook(cub.win, 2, 1L << 0, &key_pressed, cub.key);
		mlx_hook(cub.win, 3, 1L << 1, &key_released, cub.key);
		mlx_loop_hook(cub.mlx, &actualize, &cub);
		mlx_loop(cub.mlx);
	}
	else if (argc == 3 && (ft_strncmp(argv[2], "--save", 7)) == 0)
	{
		render(&cub, cub.ray, cub.images, cub.spr_ray);
		order_sprites(cub.spr_ray->sprite_order, cub.map);
		render_sprites(&cub);
		create_bmp(cub.params, cub.images->screen->addr);
	}
}
