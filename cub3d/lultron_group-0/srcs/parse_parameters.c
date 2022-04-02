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

char	*skip_spaces(char *s)
{
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return (s);
}

void	get_resolution(t_params *params, char *s)
{
	int	res_x;
	int	res_y;

	s++;
	s = skip_spaces(s);
	res_x = 0;
	while (ft_isdigit(*s))
		res_x = (res_x * 10) + (*s++ - 48);
	s = skip_spaces(s);
	res_y = 0;
	while (ft_isdigit(*s))
		res_y = (res_y * 10) + (*s++ - 48);
	if (*(s = skip_spaces(s)) != '\0')
		exit_fail("Illegal information under resolution identifier");
	if (res_x < 1 || res_y < 1)
		exit_fail("Bad resolution parameters");
	if (res_x < params->resolution_x)
		params->resolution_x = res_x;
	if (res_y < params->resolution_y)
		params->resolution_y = res_y;
}

char	*get_path(char *s)
{
	char	*path;

	s++;
	path = ft_strtrim(s, " \t");
	if (path == NULL)
		exit_fail("ft_strtrim in get_path failed");
	if (*path == '\0')
		exit_fail("Bad texture path parameter");
	return (path);
}

int		get_color(char *s)
{
	int				color_hex;
	unsigned char	color;
	int				i;

	s++;
	s = skip_spaces(s);
	color = 0;
	i = 2;
	while (ft_isdigit(*s))
		color = (color * 10) + (*s++ - 48);
	color_hex = color;
	while (i-- && *s++ == ',')
	{
		color = 0;
		s = skip_spaces(s);
		while (ft_isdigit(*s))
			color = (color * 10) + (*s++ - 48);
		color_hex = (color_hex << 8) | color;
	}
	if (*(s = skip_spaces(s)) != '\0')
		exit_fail("Illegal information after ceiling/floor identifier");
	return (color_hex);
}

void	parse_parameters(t_params *params, char **line)
{
	char	*s;

	s = skip_spaces(*line);
	if (s[0] == 'R')
		get_resolution(params, s);
	else if (s[0] == 'N' && s[1] == 'O' && !params->path_no)
		params->path_no = get_path(++s);
	else if (s[0] == 'S' && s[1] == 'O' && !params->path_so)
		params->path_so = get_path(++s);
	else if (s[0] == 'W' && s[1] == 'E' && !params->path_we)
		params->path_we = get_path(++s);
	else if (s[0] == 'E' && s[1] == 'A' && !params->path_ea)
		params->path_ea = get_path(++s);
	else if (s[0] == 'S' && !params->path_s)
		params->path_s = get_path(s);
	else if (s[0] == 'F' && params->color_floor == -1)
		params->color_floor = get_color(s);
	else if (s[0] == 'C' && params->color_ceiling == -1)
		params->color_ceiling = get_color(s);
	else if (s[0] == '1')
		return ;
	else if (s[0] != '\0')
		exit_fail("Illegal information in file");
	free(*line);
}
