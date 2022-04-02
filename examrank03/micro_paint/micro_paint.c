#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_background
{
	int			width;
	int			height;
	char		symbol;
}				t_background;

typedef struct	s_fig
{
	char		type;
	float		corner_x;
	float		corner_y;
	float		width;
	float		height;
	char		symbol;
}				t_figure;

int		border(int x, int y, t_figure *fig)
{
	int		type;

	type = 0;
	if (fig->corner_x <= x && x <= (fig->corner_x + fig->width) &&
			fig->corner_y <= y && y <= (fig->corner_y + fig->height))
	{
		type = 1;
		if ((x - fig->corner_x) < 1 || (fig->corner_x + fig->width - x) < 1 ||
			(y - fig->corner_y) < 1 || (fig->corner_y + fig->height - y) < 1)
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
			point = border(x, y, fig);
			if ((point == 2 && fig->type == 'r') || (point && fig->type == 'R'))
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

	while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &fig.type, &fig.corner_x,
			&fig.corner_y, &fig.width, &fig.height, &fig.symbol)) == 6)
	{
		if ((fig.type != 'r' && fig.type != 'R') || fig.width <= 0 || fig.height <= 0)
			return (close_and_free("Error: Operation file corrupted\n", file, img));
		draw(&back, &fig, img);
	}
	if (ret != -1)
		return (close_and_free("Error: Operation file corrupted\n", file, img));

	write(1, img, ((back.width + 1) * back.height));
	close_and_free(NULL, file, img);
	return (0);
}