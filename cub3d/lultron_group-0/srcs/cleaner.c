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

void	free_all(t_cub *cub)
{
	if (cub->spr_ray)
		free_spr_ray(cub->spr_ray);
	if (cub->ray)
		free(cub->ray);
	if (cub->params)
		free_params(cub->params);
	if (cub->map)
		free_map(cub->map);
	if (cub->key)
		free(cub->key);
	if (cub->images)
	{
		destroy_images(cub->images, cub->mlx);
		free_images(cub->images);
	}
	if (cub->win)
	{
		mlx_clear_window(cub->mlx, cub->win);
		mlx_destroy_window(cub->mlx, cub->win);
	}
}

void	exit_fail(char *error)
{
	static t_cub cub;

	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("  (╯°□°）╯︵ ┻━┻  \n", 2);
	free_all(&cub);
	exit(EXIT_FAILURE);
}

int		exit_success(t_cub *cub)
{
	ft_putstr_fd("\n ฅ^•ﻌ•^ฅ \n Goodbye! \n\n", 1);
	free_all(cub);
	exit(EXIT_SUCCESS);
	return (1);
}
