/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:03:49 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/10 16:33:48 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	coin_changes(t_data	*gl)
{
	gl->nu.frames++;
	if (gl->nu.frames < 10)
		gl->s.c[0] = gl->s.c[1];
	else if (gl->nu.frames < 20)
		gl->s.c[0] = gl->s.c[2];
	else if (gl->nu.frames < 30)
		gl->s.c[0] = gl->s.c[3];
	else if (gl->nu.frames < 40)
		gl->s.c[0] = gl->s.c[4];
	else if (gl->nu.frames < 50)
		gl->s.c[0] = gl->s.c[5];
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

int	close_window(void)
{
	exit(0);
}

char	last_char(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen(line) != 0 && line[ft_strlen(line) - 1] == '\n')
		return (0);
	else
		return (1);
}
