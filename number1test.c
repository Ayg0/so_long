#include <mlx.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_data
{
	void	*img;
	char	*add;
	int		b_per_p;
	int		line_lenght;
	int		endian;
}	t_data;
typedef struct s_vars
{
	void	*mlx;
	void	*window;
	t_data	image;
}	t_vars;

void	put_pixel(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->add + (y * data->line_lenght + x * (data->b_per_p / 8));
	*(unsigned int *)dst = color;
}
int	number_of_moves(int keycode, t_vars *vars)
{
	static int	i;

	i++;
	return(printf("%d\n", keycode));
}
int	display_it(t_vars *wow)
{
	static int	i;
	int	arr[3] = {0x00FF0000, 0x000000FF, 0x0000FF00};
	int	a = 0;
	sleep(1);
	if (i < 2)
		i++;
	else
		i = 0;
	while(a < 50)
	{
		put_pixel(&(wow->image), a + i + wow->image.line_lenght, 5, arr[i]);
		put_pixel(&(wow->image), a + i + wow->image.line_lenght, 6, arr[i]);
		put_pixel(&(wow->image), a + i + wow->image.line_lenght, 7, arr[i]);
		a++;
	}
	mlx_put_image_to_window(wow->mlx, wow->window, wow->image.img, 0, 0);
	return(0);
}
int	main()
{
	t_vars	wow;
	void	*window;
	wow.mlx = mlx_init();
	wow.window = mlx_new_window(wow.mlx, 1280, 720, "new ");
	wow.image.img = mlx_new_image(wow.mlx, 100, 80);
	wow.image.add = mlx_get_data_addr(wow.image.img,&wow.image.b_per_p, &wow.image.line_lenght, &wow.image.endian);
	mlx_key_hook(wow.window, number_of_moves, &wow);
	while(1)
	{
		mlx_loop_hook(wow.mlx, display_it, &wow);
		mlx_loop(wow.mlx);
	}

}