/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lultron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 11:48:34 by lultron           #+#    #+#             */
/*   Updated: 2020/09/07 11:51:30 by lultron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx_opengl/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

typedef struct		s_params
{
	int				resolution_x;
	int				resolution_y;
	char			*path_no;
	char			*path_so;
	char			*path_ea;
	char			*path_we;
	char			*path_s;
	int				color_floor;
	int				color_ceiling;
}					t_params;

typedef struct		s_camera
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_camera;

typedef struct		s_sprite
{
	double			pos_x;
	double			pos_y;
}					t_sprite;

typedef struct		s_map
{
	const char		*file_name;
	t_list2			*maplines;
	int				size;
	t_camera		*camera;
	int				sprites_num;
	t_sprite		**sprites;
	int				**map;
}					t_map;

typedef struct		s_img
{
	void			*img;
	int				width;
	int				height;
	int				*addr;
	int				endian;
	int				bpp;
	int				size_line;
}					t_img;

typedef struct		s_images
{
	t_img			*screen;
	t_img			*north;
	t_img			*south;
	t_img			*east;
	t_img			*west;
	t_img			*sprite;
}					t_images;

# define A_KEY		0
# define W_KEY		13
# define S_KEY		1
# define D_KEY		2
# define LEFT_KEY	123
# define RIGHT_KEY	124
# define ESC_KEY	53
# define X_BTN		17

typedef struct		s_key
{
	unsigned char	a;
	unsigned char	w;
	unsigned char	s;
	unsigned char	d;
	unsigned char	left;
	unsigned char	right;
	unsigned char	esc;
}					t_key;

typedef struct		s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	short			hit;
	short			side;
	double			perp_wall_dist;
	double			wall_hit_x;
	t_img			*texture;
	int				texture_x;
	double			wall_height;
	double			draw_start;
	double			draw_end;
}					t_ray;

typedef struct		s_sprite_ray
{
	double			inv_det;
	int				*sprite_order;
	double			sprite_x;
	double			sprite_y;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				draw_start_x;
	int				draw_start_y;
	int				draw_end_x;
	int				draw_end_y;
	int				stripe;
	double			*wall_z;
	int				tex_x;
	int				tex_y;
}					t_sprite_ray;

typedef struct		s_cub
{
	void			*mlx;
	void			*win;
	t_params		*params;
	t_map			*map;
	t_images		*images;
	t_key			*key;
	double			mov_speed;
	double			rotate_speed;
	t_ray			*ray;
	t_sprite_ray	*spr_ray;
}					t_cub;

void				free_spr_ray(t_sprite_ray *spr_ray);
void				free_map(t_map *map);
void				free_params(t_params *params);
void				destroy_images(t_images *images, void *mlx);
void				free_images(t_images *images);
void				free_all(t_cub *cub);
void				exit_fail(char *error);
int					exit_success(t_cub *cub);

void				validate_map(t_map *map, int y, int x);
void				fill_map_array(char *line, int len, int y, t_map *map);
void				parse_map(t_map *map);

static t_camera		*set_dir_plane(double dir_x, double dir_y,
								double plane_x, double plane_y);
void				validline_setcamera(t_camera **camera, char ptr,
								int pos_x, int pos_y);
t_list2				*addlst_mapline(t_map *map, char *line, int i,
								t_list2 *tail);
void				read_map(int fd, char *line, int i, t_map *map);

char				*skip_spaces(char *s);
void				get_resolution(t_params *params, char *s);
char				*get_path(char *s);
int					get_color(char *s);
void				parse_parameters(t_params *params, char **line);

void				init_parameters_values(t_cub *cub);
void				read_file(t_cub *cub, int fd);

static t_img		*create_texture(void *mlx, char *path);
static t_images		*create_images(void *mlx, t_params *params);

void				bubble_sort(int *list, double *content, int elements);
void				order_sprites(int *sprite_order, t_map *map);
static void			print_stripe(t_sprite_ray *ray, t_images *images,
								t_params *params);
static void			calculate_params(t_camera *player, t_sprite_ray *ray,
								t_params *params);
void				render_sprites(t_cub *cub);

int					key_pressed(int keycode, t_key *key);
int					key_released(int keycode, t_key *key);
void				init_rendering_values(t_cub *cub);
void				vertical_movement(t_map *map, double movement_speed,
								double dir_x, double dir_y);
void				horizontal_movement(t_map *map, double movement_speed,
								double plane_x, double plane_y);
void				rotation(t_camera *camera, double rotation_speed);
void				get_side_dist(int x, double resolution_x, t_ray *ray,
								t_camera *camera);
void				get_hit(t_ray *ray, int **map, int map_max_y);
void				get_wall(t_ray *ray, t_camera *camera, t_images *images);
void				get_wall_dist(t_ray *ray, t_camera *camera,
								t_sprite_ray *s_ray, int x);
void				get_wall_height(t_ray *ray, t_params *parameters);
void				print_column(int x, t_ray *ray, t_params *params,
								t_images *images);
void				render(t_cub *cub, t_ray *ray, t_images *images,
								t_sprite_ray *s_ray);

void				trigger_events(t_cub *cub);
int					actualize(t_cub *cub);

void				write_headers(unsigned char *file_header,
								unsigned char *info_header,
								int file_size, t_params *params);
void				create_headers(int fd, int padding, t_params *params);
void				write_bmp(int fd, int padding, int *screen,
								t_params *params);
void				create_bmp(t_params *params, int *screen);

void				init(char *file_name, t_cub *cub);

#endif
