/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:06:23 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/08 08:42:56 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	edit(int x, int y, t_data *gl)
{
	if (gl->map[gl->player.x + x][gl->player.y + y] == '0')
		gl->map[gl->player.x + x][gl->player.y + y] = 'P';
	else if (gl->map[gl->player.x + x][gl->player.y + y] == 'C')
		gl->map[gl->player.x + x][gl->player.y + y] = 'P';
	else if (gl->map[gl->player.x + x][gl->player.y + y] == 'E' &&
		gl->player.coins == 0 && gl->nu.work == 0)
	{
		gl->map[gl->player.x + x][gl->player.y + y] = 'P';
		gl->nu.work = 1;
	}
	else if (gl->map[gl->player.x + x][gl->player.y + y] == 'N' &&
		gl->nu.work == 0)
	{
		gl->map[gl->player.x + x][gl->player.y + y] = 'P';
		gl->nu.work = 2;
	}
	else
		return ;
	gl->map[gl->player.x][gl->player.y] = '0';
	gl->player.x += x;
	gl->player.y += y;
	gl->player.moves++;
}

int	add_life(int keycode, t_data *gl)
{
	if (keycode == 13)
		edit(-1, 0, gl);
	else if (keycode == 2)
	{
		gl->player.r_l = 1;
		edit(0, 1, gl);
	}
	else if (keycode == 1)
		edit(1, 0, gl);
	else if (keycode == 0)
	{
		gl->player.r_l = 0;
		edit(0, -1, gl);
	}
	else if (keycode == 53)
		exit(0);
	return (1);
}

void	init_coins(t_data *gl)
{
	gl->s.c1.ig = gl->xpm_image(gl->mlx, "xpms/c1.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.c2.ig = gl->xpm_image(gl->mlx, "xpms/c2.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.c3.ig = gl->xpm_image(gl->mlx, "xpms/c3.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.c4.ig = gl->xpm_image(gl->mlx, "xpms/c4.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.c5.ig = gl->xpm_image(gl->mlx, "xpms/c5.xpm", &gl->nu.ps, &gl->nu.ps);
}

void	init_elements(t_data *gl)
{
	gl->nu.ps = 32;
	gl->player.moves = 0;
	gl->nu.work = 0;
	gl->nu.player = 0;
	gl->nu.ene_less = 0;
	gl->nu.ex = 0;
}

void	init_data(t_data *gl)
{
	gl->mlx = mlx_init();
	gl->xpm_image = mlx_xpm_file_to_image;
	gl->s.b.ig = gl->xpm_image(gl->mlx, "xpms/b.xpm", &gl->nu.ps, &gl->nu.ps);
	init_coins(gl);
	gl->s.p1.ig = gl->xpm_image(gl->mlx, "xpms/p.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.p2.ig = gl->xpm_image(gl->mlx, "xpms/p2.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.m.ig = gl->xpm_image(gl->mlx, "xpms/m.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.e.ig = gl->xpm_image(gl->mlx, "xpms/n.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.e1.ig = gl->xpm_image(gl->mlx, "xpms/e1.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.e2.ig = gl->xpm_image(gl->mlx, "xpms/e2.xpm", &gl->nu.ps, &gl->nu.ps);
}
