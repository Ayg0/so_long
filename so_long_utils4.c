/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:03:49 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/07 19:05:10 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_sleep(unsigned int time)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < time)
	{
		i++;
		j = 0;
		while (j < time)
		{
			j++;
		}
	}	
}

void	coin_changes(t_data	*gl)
{
	gl->nu.frames++;
	if (gl->nu.frames < 5)
		gl->s.c = gl->s.c1;
	else if (gl->nu.frames < 10)
		gl->s.c = gl->s.c2;
	else if (gl->nu.frames < 15)
		gl->s.c = gl->s.c3;
	else if (gl->nu.frames < 20)
		gl->s.c = gl->s.c4;
	else if (gl->nu.frames < 25)
		gl->s.c = gl->s.c5;
	else
		gl->nu.frames = 0;
}

void	render_mods(t_data	*gl)
{
	if (gl->nu.work == 1)
	{
		mlx_clear_window(gl->mlx, gl->window);
		mlx_string_put(gl->mlx, gl->window, (gl->nu.w / 4) * 32,
			((gl->nu.h + 1) / 3) * 32, 0x00FFFFFF, "Mission Complete");
	}
	else if (gl->nu.work == 2)
	{
		mlx_clear_window(gl->mlx, gl->window);
		mlx_string_put(gl->mlx, gl->window, (gl->nu.w / 4) * 32,
			((gl->nu.h + 1) / 3) * 32, 0x00FFFFFF, "Mission Failed");
	}
	else
		render_map(gl);
}

void	check_places_of_bads(t_data *gl)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	if (gl->nu.en_num == 0)
		return ;
	gl->bad = (t_e_info *)malloc(sizeof(t_e_info) * gl->nu.en_num);
	while (i < gl->nu.h)
	{
		j = 0;
		while (j < gl->nu.w)
		{
			if (gl->map[i][j] == 'N')
			{
				gl->bad[k].x = i;
				gl->bad[k].y = j;
				gl->bad[k].d = 1;
				k++;
			}
			j++;
		}
		i++;
	}
}

int	close_window(void)
{
	exit(0);
}
