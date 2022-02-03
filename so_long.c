#include "get_next_line.h"
#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct the_img
{
	void	*img;
	char	*addr;
	int		b_per_p;
	int		line_lenght;
	int		endian;
}	xml_img;

typedef struct player_info
{
	int		moves;
	int		x;
	int		y;
	int		r_l;
	char	*e;
	int		coins;
} p_info;

typedef struct numbers
{
	int	width;
	int	hight;
	int	pixels;
	int	work;
} num;

typedef struct sprites
{
	xml_img	player1;
	xml_img	player2;
	xml_img	enemy;
	xml_img	coin;
	xml_img	block;
	xml_img	exit;
	xml_img	empty;
} sp;

typedef struct all_in_one
{
	void	*mlx;
	void	*window;
	char	**map;
	p_info	p;
	sp		spi;
	num		nu;
	xml_img image;
} a_data;

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (0);
}

static int	how_long(int c)
{
	int	i;

	i = 0;
	if (c == 0)
		return (1);
	while (c)
	{
		c /= 10;
		i++;
	}
	return (i);
}

static int	plas_wn(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	int				c;
	char			*p;
	int				i;

	c = how_long(n) + plas_wn(n);
	i = 0;
	p = (char *)ft_calloc((size_t)(c + 1), sizeof(char));
	if (p == 0)
		return (0);
	if (plas_wn(n))
	{
		p[i] = '-';
		n *= -1;
	}
	while (n || i == 0)
	{
		p[c - i - 1] = n % 10 + '0';
		n /= 10;
		i++;
	}
	return (p);
}

void	ft_putnbr_base(unsigned long a, unsigned long len, char *s)
{
	if (a >= len)
		ft_putnbr_base((a / len), len, s);
	write(1, &s[a % len], 1);
}
int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char )c)
			return (i);
		i++;
	}
	return (-1);
}

int	load_map(char *name, a_data *gl)
{
	int		fd;
	char	*line;

	fd = open(name, 2);
	if(fd < 0)
		return (0);
	line = get_next_line(fd, 1);
	gl->nu.width = ft_strlen(line) - 1;
	gl->nu.hight = 0;
	while(line)
	{
		gl->nu.hight++;
		free(line);
		line = get_next_line(fd, 1);
	}
	close(fd);
	return (1);
}

int	check_map(char *name, a_data *gl)
{
	int	i;
	int	j;

	i = 0;
	j = open(name, 2);
	gl->map = (char **)ft_calloc(gl->nu.hight, sizeof(char *));
	while (i < gl->nu.hight)
	{
		gl->map[i] = get_next_line(j, 1);
		i++;
	}
	close(j);
	i = 0;
	while(i < gl->nu.hight)
	{
		j = 0;
		while(j < gl->nu.width)
		{
			if(ft_strchr("01CPEN", gl->map[i][j]) < 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void *the_one(a_data *gl, char c, int i, int j)
{
	if(c == '1')
		return (gl->spi.block.img);
	else if (c == 'P')
	{
		gl->p.x = i;
		gl->p.y = j;
	if(gl->p.r_l == 0)
		return (gl->spi.player2.img);
	return (gl->spi.player1.img);
	}
	else if (c == 'E')
		return (gl->spi.exit.img);
	else if (c == 'N')
		return (gl->spi.enemy.img);
	else if (c == '0')
		return (gl->spi.empty.img);
	else
	{
		gl->p.coins++;
		return(gl->spi.coin.img);
	}
}

void	render_map(a_data *gl)
{
	int		i;
	int		j;
	void	*m;

	i = 0;
	gl->p.coins = 0;
	m = ft_itoa(gl->p.moves);
	mlx_clear_window(gl->mlx, gl->window);
	mlx_string_put(gl->mlx, gl->window, 0, 0, 0x00FFFFFF, "moves:");
	mlx_string_put(gl->mlx, gl->window, 7 * 16, 0, 0x00FFFFFF, m);
	free(m);
	while(i < gl->nu.hight)
	{
		j = 0;
		while(j < gl->nu.width)
		{
			m = the_one(gl, gl->map[i][j], i, j);
			mlx_put_image_to_window(gl->mlx, gl->window, m, j * gl->nu.pixels, (i + 1) * gl->nu.pixels);
			j++;
		}
		i++;
	}
}

void	edit(int x, int y, a_data *gl)
{
	if(gl->map[gl->p.x + x][gl->p.y + y] == '0')
		gl->map[gl->p.x + x][gl->p.y + y] = 'P';
	else if(gl->map[gl->p.x + x][gl->p.y + y] == 'C')
		gl->map[gl->p.x + x][gl->p.y + y] = 'P';
	else if(gl->map[gl->p.x + x][gl->p.y + y] == 'E' && gl->p.coins == 0)
	{
		gl->map[gl->p.x + x][gl->p.y + y] = 'P';
		gl->nu.work = 1;
	}
		else if(gl->map[gl->p.x + x][gl->p.y + y] == 'N')
	{
		gl->map[gl->p.x + x][gl->p.y + y] = 'P';
		gl->nu.work = 2;
	}
	else
		return ;
	gl->map[gl->p.x][gl->p.y] = '0';
	gl->p.x += x;
	gl->p.y += y;
	gl->p.moves++;
}

void	render_it(a_data *gl, int flag)
{
	if(flag == 1)
	{
		mlx_clear_window(gl->mlx, gl->window);
		mlx_string_put(gl->mlx, gl->window, (gl->nu.width / 4 ) * 32, ((gl->nu.hight + 1) / 3 ) * 32, 0x00FFFFFF, "Wa rba7tiiii");
	}
	else if(flag == 2)
	{
		mlx_clear_window(gl->mlx, gl->window);
		mlx_string_put(gl->mlx, gl->window, (gl->nu.width / 4 ) * 32, ((gl->nu.hight + 1) / 3 ) * 32, 0x00FFFFFF, "Wa matiiiii");
	}
	else
		render_map(gl);
}

int	add_life(int keycode, a_data *gl)
{
	if (keycode == 13)
		edit(-1, 0, gl);
	else if (keycode == 2)
	{
		gl->p.r_l = 1;
		edit(0, 1, gl);
	}
	else if (keycode == 1)
		edit(1, 0, gl);
	else if (keycode == 0)
	{
		gl->p.r_l = 0;
		edit(0, -1, gl);
	}
	else if (keycode == 53)
		exit(0);
	render_it(gl, gl->nu.work);
	return (1);
}

void	init(a_data	*gl)
{
	gl->mlx = mlx_init();
	gl->nu.pixels = 32;
	gl->p.moves = 0;
	gl->nu.work = 0;
	gl->spi.block.img = mlx_xpm_file_to_image(gl->mlx, "block.xpm", &gl->nu.pixels, &gl->nu.pixels);
	gl->spi.block.addr = mlx_get_data_addr(gl->spi.block.img, &gl->spi.block.b_per_p, &gl->spi.block.line_lenght, &gl->spi.block.endian);
	gl->spi.coin.img = mlx_xpm_file_to_image(gl->mlx, "coin.xpm", &gl->nu.pixels, &gl->nu.pixels);
	gl->spi.coin.addr = mlx_get_data_addr(gl->spi.coin.img, &gl->spi.coin.b_per_p, &gl->spi.coin.line_lenght, &gl->spi.coin.endian);
	gl->spi.player1.img = mlx_xpm_file_to_image(gl->mlx, "p.xpm", &gl->nu.pixels, &gl->nu.pixels);
	gl->spi.player1.addr = mlx_get_data_addr(gl->spi.player1.img, &gl->spi.player1.b_per_p, &gl->spi.player1.line_lenght, &gl->spi.player1.endian);
	gl->spi.player2.img = mlx_xpm_file_to_image(gl->mlx, "p2.xpm", &gl->nu.pixels, &gl->nu.pixels);	
	gl->spi.player2.addr = mlx_get_data_addr(gl->spi.player2.img, &gl->spi.player2.b_per_p, &gl->spi.player2.line_lenght, &gl->spi.player2.endian);
	gl->spi.empty.img = mlx_xpm_file_to_image(gl->mlx, "empty.xpm", &gl->nu.pixels, &gl->nu.pixels);
	gl->spi.empty.addr = mlx_get_data_addr(gl->spi.empty.img, &gl->spi.empty.b_per_p, &gl->spi.empty.line_lenght, &gl->spi.empty.endian);
	gl->spi.enemy.img = mlx_xpm_file_to_image(gl->mlx, "enemy.xpm", &gl->nu.pixels, &gl->nu.pixels);
	gl->spi.enemy.addr = mlx_get_data_addr(gl->spi.enemy.img, &gl->spi.enemy.b_per_p, &gl->spi.enemy.line_lenght, &gl->spi.enemy.endian);
	gl->spi.exit.img = mlx_xpm_file_to_image(gl->mlx, "exit.xpm", &gl->nu.pixels, &gl->nu.pixels);
	gl->spi.exit.addr = mlx_get_data_addr(gl->spi.exit.img, &gl->spi.exit.b_per_p, &gl->spi.exit.line_lenght, &gl->spi.exit.endian);
}

int	close_window(int keycode, a_data gl)
{
	exit(0);
}

int	main(int ac, char **av)
{
	a_data	gl;
	int		err;
	char	*c;

	c = ft_strstr(av[1], ".ber");
	if (!ft_strstr(av[1], ".ber"))
		return (write(1, "error", 5));
	init(&gl);
	err = load_map(av[1], &gl);
	if(!err)
		return (write(1, "error", 5));
	err = check_map(av[1], &gl);
	if(!err)
		return (write(1, "error", 5));
	gl.window = mlx_new_window(gl.mlx, gl.nu.width * 32, (gl.nu.hight + 1) * 32, "The road to albion");
	render_map(&gl);
	mlx_key_hook(gl.window, add_life, &gl);
	mlx_hook(gl.window, 17, 1L<<5, close_window, &gl);
	mlx_loop(gl.mlx);
	return (0);
}