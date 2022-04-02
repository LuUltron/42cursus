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

// char	*ft_read(FILE *file)
// {
// 	char	*buff;
// 	size_t	len;
// 	int		ret;

// 	buff = (char *)calloc(1, 1);
// 	len = 1;
// 	while ((ret = fread(buff + len - 1, 1, 1, file)) > 0)
// 	{
// 		len += ret;
// 		buff = (char *)realloc(buff, len);
// 		buff[len] = '\0';
// 		printf("Read ret=|%zu|\tstring=|%s|\n", len, buff); //////
// 	}
//	 if (ret < 0)
// 	{
// 		fclose(file);
// 		if (buff)
// 			free(buff);
// 		write(1, "Error: Operation file corrupted\n", 32);
// 		return(NULL);
// 	}
// 	return (buff);
// }

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

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putchar_fd('2', fd);
			n = n % 2000000000 * (-1);
		}
		else
			n = -n;
	}
	if (n < 10)
		ft_putchar_fd(n + '0', fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
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

	ft_putstr_fd("back.width=|", 1);
	ft_putnbr_fd(back.width, 1);
	ft_putstr_fd("| back.height=|", 1);
	ft_putnbr_fd(back.height, 1);
	ft_putstr_fd("| back.symbol=|", 1);
	ft_putchar_fd(back.symbol, 1);
	ft_putstr_fd("|\n", 1);

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
		ft_putstr_fd("ret=|", 1);
		ft_putnbr_fd(ret, 1);
		ft_putstr_fd("|\nfig.type=|", 1);
		ft_putchar_fd(fig.type, 1);
		ft_putstr_fd("| corner_x=|", 1);
		ft_putnbr_fd(fig.corner_x, 1);
		ft_putstr_fd("| corner_y=|", 1);
		ft_putnbr_fd(fig.corner_y, 1);
		ft_putstr_fd("| width=|", 1);
		ft_putnbr_fd(fig.width, 1);
		ft_putstr_fd("| height=|", 1);
		ft_putnbr_fd(fig.height, 1);
		ft_putstr_fd("| symbol=|", 1);
		ft_putchar_fd(fig.symbol, 1);
		ft_putstr_fd("|\n", 1);

		if ((fig.type != 'r' && fig.type != 'R') || fig.width <= 0 || fig.height <= 0)
			return (close_and_free("Error: Operation file corrupted\n", file, img));

		ft_putstr_fd("drawing\n", 1);
		draw(&back, &fig, img);
	}
	if (ret != -1)
		return (close_and_free("Error: Operation file corrupted\n", file, img));


	write(1, img, ((back.width + 1) * back.height));
	close_and_free(NULL, file, img);
	return (0);
}