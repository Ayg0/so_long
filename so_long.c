/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 18:06:14 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/04 19:01:12 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_ig
{
	void	*ig;
	char	*ad;
	int		bp;
	int		l_s;
	int		en;
}	t_xml_ig;

typedef struct s_player_info
{
	int		moves;
	int		x;
	int		y;
	int		r_l;
	char	*e;
	int		coins;
}	t_p_info;

typedef struct s_numbers
{
	int	w;
	int	h;
	int	c;
	int	p;
	int	ex;
	int	ps;
	int	work;
}	t_num;

typedef struct s_sprites
{
	t_xml_ig	p1;
	t_xml_ig	p2;
	t_xml_ig	e;
	t_xml_ig	c;
	t_xml_ig	b;
	t_xml_ig	e1;
	t_xml_ig	e2;
	t_xml_ig	m;
}	t_sp;

typedef struct all_in_one
{
	void		*mlx;
	void		*window;
	char		**map;
	char		*(*k)(void *ig, int *b, int *sl, int *e);
	void		*(*b)(void *mlx, char *file, int *w, int *h);
	t_p_info	p;
	t_sp		s;
	t_num		nu;
}	t_data;

void	arr_swap(char *s)
{
	int	i;
	int	a;

	i = 0;
	a = ft_strlen(s);
	while (i < (a / 2))
	{
		s[i] ^= s[a - i - 1];
		s[a - i - 1] ^= s[i];
		s[i] ^= s[a - i - 1];
		i++;
	}
}

char	*ft_strstr(char *haystack, char *needle, int len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack && !len)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && j + i < len)
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

int	ft_strchr(char *s, int c, int f1, int f2)
{
	int	i;

	i = 0;
	if (f1 || f2)
		s = "1";
	while (s[i])
	{
		if (s[i] == (char )c)
			return (i);
		i++;
	}
	return (-1);
}

int	load_map(char *name, t_data *gl)
{
	int		fd;
	char	*line;

	fd = open(name, 2);
	if (fd < 0)
		return (0);
	line = get_next_line(fd, 1);
	gl->nu.w = ft_strlen(line);
	gl->nu.h = 0;
	while (line)
	{
		gl->nu.h++;
		free(line);
		line = get_next_line(fd, 1);
		if (ft_strlen(line) != gl->nu.w && ft_strlen(line) != 0)
			return (0);
	}
	close(fd);
	return (1);
}

int	final_check(t_data *gl)
{
	int	i;
	int	j;

	i = 0;
	while (i < gl->nu.h)
	{
		j = 0;
		while (j < gl->nu.w)
		{
			if (gl->map[i][j] == 'P')
				gl->nu.p = 1;
			else if (gl->map[i][j] == 'C')
				gl->nu.c = 1;
			if (gl->map[i][j] == 'E')
				gl->nu.ex = 1;
			j++;
		}
		i++;
	}
	return (gl->nu.p && gl->nu.c && gl->nu.ex && (gl->nu.h != gl->nu.w));
}

int	check_map(char *name, t_data *gl)
{
	int	i;
	int	j;

	i = 0;
	j = open(name, 2);
	gl->map = (char **)ft_calloc(gl->nu.h, sizeof(char *));
	while (i < gl->nu.h)
		gl->map[i++] = get_next_line(j, 1);
	close(j);
	i = 0;
	while (i < gl->nu.h)
	{
		j = 0;
		while (j < gl->nu.w)
		{
			if (ft_strchr("01CPEN", gl->map[i][j], i == 0 || i == gl->nu.h - 1,
				j == 0 || j == gl->nu.w - 1) < 0)
				return (0);
			j++;
		}
		i++;
	}
	return (final_check(gl));
}

void	*the_one(t_data *gl, char c, int i, int j)
{
	if (c == '1')
		return (gl->s.b.ig);
	else if (c == 'P')
	{
		gl->p.x = i;
		gl->p.y = j;
		if (gl->p.r_l == 0)
			return (gl->s.p2.ig);
		return (gl->s.p1.ig);
	}
	else if (c == 'E')
	{
		if (gl->p.coins == 0)
			return (gl->s.e1.ig);
		return (gl->s.e2.ig);
	}
	else if (c == 'N')
		return (gl->s.e.ig);
	else if (c == '0')
		return (gl->s.m.ig);
	else
	{
		gl->p.coins++;
		return (gl->s.c.ig);
	}
}

void	render_map(t_data *gl)
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
	while (i < gl->nu.h)
	{
		j = 0;
		while (j < gl->nu.w)
		{
			m = the_one(gl, gl->map[i][j], i, j);
			mlx_put_image_to_window(gl->mlx, gl->window, m, j * gl->nu.ps,
				(i + 1) * gl->nu.ps);
			j++;
		}
		i++;
	}
}

void	edit(int x, int y, t_data *gl)
{
	if (gl->map[gl->p.x + x][gl->p.y + y] == '0')
		gl->map[gl->p.x + x][gl->p.y + y] = 'P';
	else if (gl->map[gl->p.x + x][gl->p.y + y] == 'C')
		gl->map[gl->p.x + x][gl->p.y + y] = 'P';
	else if (gl->map[gl->p.x + x][gl->p.y + y] == 'E' && gl->p.coins == 0)
	{
		gl->map[gl->p.x + x][gl->p.y + y] = 'P';
		gl->nu.work = 1;
	}
	else if (gl->map[gl->p.x + x][gl->p.y + y] == 'N')
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

void	render_it(t_data *gl, int flag)
{
	if (flag == 1)
	{
		mlx_clear_window(gl->mlx, gl->window);
		mlx_string_put(gl->mlx, gl->window, (gl->nu.w / 4) * 32,
			((gl->nu.h + 1) / 3) * 32, 0x00FFFFFF, "Wa rba7tiii");
	}
	else if (flag == 2)
	{
		mlx_clear_window(gl->mlx, gl->window);
		mlx_string_put(gl->mlx, gl->window, (gl->nu.w / 4) * 32,
			((gl->nu.h + 1) / 3) * 32, 0x00FFFFFF, "Wa matiiiii");
	}
	else
		render_map(gl);
}

int	add_life(int keycode, t_data *gl)
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

void	init(t_data	*gl)
{
	gl->mlx = mlx_init();
	gl->nu.ps = 32;
	gl->p.moves = 0;
	gl->nu.work = 0;
	gl->nu.c = 0;
	gl->nu.p = 0;
	gl->nu.ex = 0;
	gl->b = mlx_xpm_file_to_image;
	gl->k = mlx_get_data_addr;
	gl->s.b.ig = gl->b(gl->mlx, "b.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.b.ad = gl->k(gl->s.b.ig, &gl->s.b.bp, &gl->s.b.l_s, &gl->s.b.en);
	gl->s.c.ig = gl->b(gl->mlx, "c.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.c.ad = gl->k(gl->s.c.ig, &gl->s.c.bp, &gl->s.c.l_s, &gl->s.c.en);
	gl->s.p1.ig = gl->b(gl->mlx, "p.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.p1.ad = gl->k(gl->s.p1.ig, &gl->s.p1.bp, &gl->s.p1.l_s, &gl->s.p1.en);
	gl->s.p2.ig = gl->b(gl->mlx, "p2.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.p2.ad = gl->k(gl->s.p2.ig, &gl->s.p2.bp, &gl->s.p2.l_s, &gl->s.p2.en);
	gl->s.m.ig = gl->b(gl->mlx, "m.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.m.ad = gl->k(gl->s.m.ig, &gl->s.m.bp, &gl->s.m.l_s, &gl->s.m.en);
	gl->s.e.ig = gl->b(gl->mlx, "n.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.e.ad = gl->k(gl->s.e.ig, &gl->s.e.bp, &gl->s.e.l_s, &gl->s.e.en);
	gl->s.e1.ig = gl->b(gl->mlx, "e1.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.e1.ad = gl->k(gl->s.e1.ig, &gl->s.e1.bp, &gl->s.e1.l_s, &gl->s.e1.en);
	gl->s.e2.ig = gl->b(gl->mlx, "e2.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.e2.ad = gl->k(gl->s.e2.ig, &gl->s.e2.bp, &gl->s.e2.l_s, &gl->s.e2.en);
}

int	close_window(int keycode, t_data gl)
{
	exit(0);
}

int	main(int ac, char **av)
{
	t_data	gl;
	int		err;

	arr_swap(av[1]);
	if (!ft_strstr(av[1], "reb.", 4))
		return (write(1, "error", 5));
	arr_swap(av[1]);
	init(&gl);
	err = load_map(av[1], &gl);
	if (!err)
		return (write(1, "error", 5));
	err = check_map(av[1], &gl);
	if (!err)
		return (write(1, "error", 5));
	gl.window = mlx_new_window(gl.mlx, gl.nu.w * 32, (gl.nu.h + 1) * 32, "IO");
	render_map(&gl);
	mlx_key_hook(gl.window, add_life, &gl);
	mlx_hook(gl.window, 17, 1L << 5, close_window, &gl);
	mlx_loop(gl.mlx);
	return (0);
}
