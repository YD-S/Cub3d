#include "cub3d.h"

void	ft_quit(t_mlx_data *mlx_data)
{
	mlx_terminate(mlx_data->mlx);
	mlx_delete_texture(mlx_data->map_data.texture.no);
	mlx_delete_texture(mlx_data->map_data.texture.so);
	mlx_delete_texture(mlx_data->map_data.texture.ea);
	mlx_delete_texture(mlx_data->map_data.texture.we);
	exit(0);
}

void	ret_coord(t_point *vel, int i, int angle)
{
	vel->xcoord = roundf(i * sin(grade_to_radian(angle)));
	vel->ycoord = roundf(i * cos(grade_to_radian(angle)));
}

void	hook(struct mlx_key_data keydata, void *param)
{
	t_mlx_data	*mlx_data;
	t_point		vel;

	vel.xcoord = 0;
	vel.ycoord = 0;
	mlx_data = (t_mlx_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		ft_quit(mlx_data);
	else if (keydata.key == MLX_KEY_W)
		ret_coord(&vel, 3, mlx_data->player.angle);
	else if (keydata.key == MLX_KEY_S)
		ret_coord(&vel, -3, mlx_data->player.angle);
	else if (keydata.key == MLX_KEY_D)
		ret_coord(&vel, -3, mlx_data->player.angle + 90);
	else if (keydata.key == MLX_KEY_A)
		ret_coord(&vel, 3, mlx_data->player.angle + 90);
	if (!collision(mlx_data, mlx_data->player.position.xcoord + (vel.xcoord
				* 2), mlx_data->player.position.ycoord + (vel.ycoord * 2)))
	{
		mlx_data->player.position.xcoord += vel.xcoord;
		mlx_data->player.position.ycoord += vel.ycoord;
	}
	call_movement_hooks(mlx_data, keydata);
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_mlx_data	*data;

	(void)ypos;
	data = (t_mlx_data *)param;
	mlx_set_mouse_pos(data->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGH / 2);
	if (xpos - SCREEN_WIDTH / 2 > 0)
		data->player.angle += 356;
	else
		data->player.angle += 4;
}

void	ft_get_texture(t_mlx_data *mlx_data)
{
	mlx_data->map_data.texture.no = mlx_load_png(mlx_data->map_data.no);
	mlx_data->map_data.texture.ea = mlx_load_png(mlx_data->map_data.ea);
	mlx_data->map_data.texture.so = mlx_load_png(mlx_data->map_data.so);
	mlx_data->map_data.texture.we = mlx_load_png(mlx_data->map_data.we);
}
