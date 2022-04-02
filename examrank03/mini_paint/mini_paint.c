#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct	s_background
{
	int			width;
	int			height;
	char		symbol;
}				t_background;

typedef struct	s_fig
{
	char		type;
	float		center_x;
	float		center_y;
	float		radius;
	char		symbol;
}				t_figure;

int		curve(int x, int y, t_figure *fig)
{
	float	dist;
	int		type;

	type = 0;
	dist = sqrtf(powf(((float)x - fig->center_x), 2) + powf(((float)y - fig->center_y), 2));
	if (dist <= fig->radius)
	{
		type = 1;
		if ((fig->radius - dist) < 1)
			type = 2;
	}
	return (type);
}

void	draw(t_background *back, t_figure *fig, char *img)
{
	int		x, y, point;

	y = 0;
	while (y < back->height)
	{
		x = 0;
		while (x < back->width)
		{
			point = curve(x, y, fig);
			if ((point == 2 && fig->type == 'c') || (point && fig->type == 'C'))
				img[((back->width + 1) * y) + x] = fig->symbol;
			x++;
		}
		y++;
	}
}

int		close_and_free(char *msg, FILE *file, char *img)
{
	int		i;

	if (msg)
	{
		i = -1;
		while (msg[++i] != '\0')
			write(1, &msg[i], 1);
	}
	if (file)
		fclose(file);
	if (img)
		free(img);
	return (1);
}

int	main(int argc, char **argv)
{
	FILE			*file;
	t_background	back;
	t_figure		fig;
	char			*img;
	int				ret;
	int				i;

	if (argc != 2)
		return (close_and_free("Error: argument\n", NULL, NULL));
	if (!(file = fopen(argv[1], "r")))
		return (close_and_free("Error: Operation file corrupted\n", NULL, NULL));

	if ((ret = fscanf(file, "%d %d %c\n", &back.width, &back.height, &back.symbol)) != 3)
		return (close_and_free("Error: Operation file corrupted\n", file, NULL));
	if (back.width <= 0 || back.width > 300 || back.height <= 0 || back.height > 300)
		return (close_and_free("Error: Operation file corrupted\n", file, NULL));

	if (!(img = (char *)calloc((back.width + 1) * back.height + 1, sizeof(char))))
		return (close_and_free("Error: Operation file corrupted\n", file, NULL));
	i = 0;
	while (i < back.height)
	{
		memset(img + ((back.width + 1) * i), back.symbol, back.width);
		i++;
		img[(back.width + 1) * i - 1] = '\n';
	}

	while ((ret = fscanf(file, "%c %f %f %f %c\n", &fig.type, &fig.center_x,
			&fig.center_y, &fig.radius, &fig.symbol)) == 5)
	{
		if ((fig.type != 'c' && fig.type != 'C') || fig.radius <= 0)
			return (close_and_free("Error: Operation file corrupted\n", file, img));
		draw(&back, &fig, img);
	}
	if (ret != -1)
		return (close_and_free("Error: Operation file corrupted\n", file, img));

	write(1, img, ((back.width + 1) * back.height));
	close_and_free(NULL, file, img);
	return (0);
}