/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:07:15 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/08 17:46:31 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_map(char *name, t_data *gl)
{
	int		fd;
	char	*line;
	int		k;

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
		k = ft_strlen(line) != gl->nu.w;
		if (k && ft_strlen(line) != 0 && line[ft_strlen(line) - 1] == '\n')
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
					gl->nu.player += 1;
			else if (gl->map[i][j] == 'C')
				gl->nu.c = 1;
			if (gl->map[i][j] == 'E')
				gl->nu.ex = 1;
			else if (gl->map[i][j] == 'N')
				gl->nu.en_num++;
			j++;
		}
		i++;
	}
	check_places_of_bads(gl);
	return (gl->nu.player == 1 && gl->nu.c && gl->nu.ex);
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
		while (j < gl->nu.w - 1)
		{
			if (ft_strchr("01CPEN", gl->map[i][j], i == 0 || i == gl->nu.h - 1,
				j == 0 || j == gl->nu.w - 2) < 0)
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
		gl->player.x = i;
		gl->player.y = j;
		if (gl->player.r_l == 0)
			return (gl->s.p[1].ig);
		return (gl->s.p[2].ig);
	}
	else if (c == 'E')
	{
		if (gl->player.coins == 0)
			return (gl->s.ex[1].ig);
		return (gl->s.ex[2].ig);
	}
	else if (c == 'N')
		return (gl->s.e.ig);
	else if (c == '0')
		return (gl->s.m.ig);
	else
	{
		gl->player.coins++;
		return (gl->s.c[0].ig);
	}
}

void	render_map(t_data *gl)
{
	int		i;
	int		j;
	void	*m;

	i = 0;
	gl->player.coins = 0;
	m = ft_itoa(gl->player.moves);
	mlx_clear_window(gl->mlx, gl->window);
	mlx_string_put(gl->mlx, gl->window, 0, 0, 0x00FFFFFF, "moves:");
	mlx_string_put(gl->mlx, gl->window, 5 * 16, 0, 0x00FFFFFF, m);
	free(m);
	while (i < gl->nu.h)
	{
		j = 0;
		while (j < gl->nu.w - 1)
		{
			m = the_one(gl, gl->map[i][j], i, j);
			mlx_put_image_to_window(gl->mlx, gl->window, m, j * gl->nu.ps,
				(i + 1) * gl->nu.ps);
			j++;
		}
		i++;
	}
}
