/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:06:23 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/07 20:18:40 by ted-dafi         ###   ########.fr       */
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
	gl->s.c1.ig = gl->b(gl->mlx, "xpms/c1.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.c1.ad = gl->k(gl->s.c1.ig, &gl->s.c1.bp, &gl->s.c1.l_s, &gl->s.c1.en);
	gl->s.c2.ig = gl->b(gl->mlx, "xpms/c2.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.c2.ad = gl->k(gl->s.c1.ig, &gl->s.c1.bp, &gl->s.c1.l_s, &gl->s.c1.en);
	gl->s.c3.ig = gl->b(gl->mlx, "xpms/c3.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.c3.ad = gl->k(gl->s.c1.ig, &gl->s.c1.bp, &gl->s.c1.l_s, &gl->s.c1.en);
	gl->s.c4.ig = gl->b(gl->mlx, "xpms/c4.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.c4.ad = gl->k(gl->s.c1.ig, &gl->s.c1.bp, &gl->s.c1.l_s, &gl->s.c1.en);
	gl->s.c5.ig = gl->b(gl->mlx, "xpms/c5.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.c5.ad = gl->k(gl->s.c1.ig, &gl->s.c1.bp, &gl->s.c1.l_s, &gl->s.c1.en);
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
	gl->b = mlx_xpm_file_to_image;
	gl->k = mlx_get_data_addr;
	gl->s.b.ig = gl->b(gl->mlx, "xpms/b.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.b.ad = gl->k(gl->s.b.ig, &gl->s.b.bp, &gl->s.b.l_s, &gl->s.b.en);
	init_coins(gl);
	gl->s.p1.ig = gl->b(gl->mlx, "xpms/p.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.p1.ad = gl->k(gl->s.p1.ig, &gl->s.p1.bp, &gl->s.p1.l_s, &gl->s.p1.en);
	gl->s.p2.ig = gl->b(gl->mlx, "xpms/p2.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.p2.ad = gl->k(gl->s.p2.ig, &gl->s.p2.bp, &gl->s.p2.l_s, &gl->s.p2.en);
	gl->s.m.ig = gl->b(gl->mlx, "xpms/m.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.m.ad = gl->k(gl->s.m.ig, &gl->s.m.bp, &gl->s.m.l_s, &gl->s.m.en);
	gl->s.e.ig = gl->b(gl->mlx, "xpms/n.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.e.ad = gl->k(gl->s.e.ig, &gl->s.e.bp, &gl->s.e.l_s, &gl->s.e.en);
	gl->s.e1.ig = gl->b(gl->mlx, "xpms/e1.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.e1.ad = gl->k(gl->s.e1.ig, &gl->s.e1.bp, &gl->s.e1.l_s, &gl->s.e1.en);
	gl->s.e2.ig = gl->b(gl->mlx, "xpms/e2.xpm", &gl->nu.ps, &gl->nu.ps);
	gl->s.e2.ad = gl->k(gl->s.e2.ig, &gl->s.e2.bp, &gl->s.e2.l_s, &gl->s.e2.en);
}
