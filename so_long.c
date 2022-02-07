/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 18:06:14 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/07 20:10:19 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	condition_of_moves(t_data *gl, int i)
{
	if (ft_strchr("CE1N",
			gl->map[gl->bad[i].x][gl->bad[i].y + gl->bad[i].d], 0, 0) >= 0)
		gl->bad[i].d *= -1;
	else if (gl->map[gl->bad[i].x][gl->bad[i].y + gl->bad[i].d] == 'P'
		&& gl->nu.work == 0)
		gl->nu.work = 2;
	else
	{
		gl->map[gl->bad[i].x][gl->bad[i].y] = '0';
		gl->bad[i].y += gl->bad[i].d;
		gl->map[gl->bad[i].x][gl->bad[i].y] = 'N';
	}	
}

void	enemy_logic(t_data *gl)
{
	int	i;

	i = 0;
	if (gl->nu.en_num == 0)
		return ;
	gl->nu.ene_less++;
	if (gl->nu.ene_less < 20)
		return ;
	else if (gl->nu.ene_less == 20)
		gl->nu.ene_less = 0;
	while (i < gl->nu.en_num)
	{
		condition_of_moves(gl, i);
		i++;
	}
}

int	render_next_frame(t_data *gl)
{
	int	i;

	i = 0;
	ft_sleep(2000);
	coin_changes(gl);
	render_mods(gl);
	ft_sleep(2000);
	coin_changes(gl);
	render_mods(gl);
	enemy_logic(gl);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	game_info;
	int		err;

	if (ac != 2)
		return (write(1, "Error\nput only the map", 23));
	arr_swap(av[1]);
	if (!ft_strstr(av[1], "reb.", 4))
		return (write(1, "Error\nthe map should be .ber", 29));
	init_elements(&game_info);
	arr_swap(av[1]);
	game_info.nu.frames = -1;
	err = load_map(av[1], &game_info);
	if (!err)
		return (write(1, "Error\nbad map", 14));
	err = check_map(av[1], &game_info);
	if (!err)
		return (write(1, "Error\nbad map elements", 23));
	init_data(&game_info);
	game_info.window = mlx_new_window(game_info.mlx, (game_info.nu.w - 1) * 32,
			(game_info.nu.h + 1) * 32, "The Road to albion");
	mlx_hook(game_info.window, 17, 1L << 5, close_window, &game_info);
	mlx_key_hook(game_info.window, add_life, &game_info);
	mlx_loop_hook(game_info.mlx, render_next_frame, &game_info);
	mlx_loop(game_info.mlx);
	return (0);
}
