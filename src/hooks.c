#include "cub3d.h"

void	*repaint_map(void *param)
{
	t_mlx_data *mlx_data = (t_mlx_data *)param;
	paint_image_black(*mlx_data);
	projection(*mlx_data);
	paint_map(*mlx_data);
	paint_horizontal_lines(*mlx_data);
	paint_vertical_lines(*mlx_data);
	put_player(*mlx_data);
	put_ray(*mlx_data);

	return (0);
}

void	call_movement_hooks(t_mlx_data *mlx_data, struct mlx_key_data keydata)
{
	if (keydata.key == MLX_KEY_RIGHT || keydata.action == MLX_PRESS)
		mlx_data->player.angle += 355;
	if (keydata.key == MLX_KEY_LEFT || keydata.action == MLX_PRESS)
		mlx_data->player.angle += 5;
}

int	collision(t_mlx_data *data, float x, float y)
{
	x /= PIXEL_SIZE;
	y /= PIXEL_SIZE;
	return (data->map_data.map[(int)floorf(y)][(int)floorf(x)].value == '1');
}

float get_xcord(t_mlx_data mlx_data, t_point vel)
{
	if(mlx_data.player.angle % 360 <= 180)
		return(mlx_data.player.position.xcoord + vel.xcoord);
	else
		return(mlx_data.player.position.xcoord - vel.xcoord);

}

float get_ycord(t_mlx_data mlx_data, t_point vel)
{
	if(mlx_data.player.angle % 360 >= 90 && mlx_data.player.angle % 360 <= 270)
		return(mlx_data.player.position.ycoord + vel.ycoord);
	else
		return(mlx_data.player.position.ycoord - vel.ycoord);

}

void	hook(struct mlx_key_data keydata, void *param)
{
	t_mlx_data	*mlx_data;
	t_point		vel;

	vel.xcoord = 0;
	vel.ycoord = 0;
	mlx_data = (t_mlx_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(mlx_data->mlx);
		exit(0);
	}
	else if (keydata.key == MLX_KEY_W)
	{
		vel.xcoord = roundf(3 * sin(grade_to_radian(mlx_data->player.angle)));
		vel.ycoord = roundf(3 * cos(grade_to_radian(mlx_data->player.angle)));
	}
	else if (keydata.key == MLX_KEY_S)
	{
		vel.xcoord = roundf(-3 * sin(grade_to_radian(mlx_data->player.angle)));
		vel.ycoord = roundf(-3 * cos(grade_to_radian(mlx_data->player.angle)));
	}
	else if (keydata.key == MLX_KEY_D)
	{
		vel.xcoord = roundf(-3 * sin(grade_to_radian(mlx_data->player.angle
						+ 90)));
		vel.ycoord = roundf(-3 * cos(grade_to_radian(mlx_data->player.angle
						+ 90)));
	}
	else if (keydata.key == MLX_KEY_A)
	{
		vel.xcoord = roundf(3 * sin(grade_to_radian(mlx_data->player.angle
						+ 90)));
		vel.ycoord = roundf(3 * cos(grade_to_radian(mlx_data->player.angle
						+ 90)));
	}
	if (!collision(mlx_data, get_xcord(*mlx_data, vel),get_ycord(*mlx_data, vel)))
	{
		mlx_data->player.position.xcoord += vel.xcoord;
		mlx_data->player.position.ycoord += vel.ycoord;
	}
	call_movement_hooks(mlx_data, keydata);
}

void cursor_hook(double xpos, double ypos, void* param)
{
	(void)ypos;
	t_mlx_data *data = (t_mlx_data *)param;
	mlx_set_mouse_pos(data->mlx, SCREEN_WIDTH/2, SCREEN_HEIGH/2);
	if(xpos - SCREEN_WIDTH/2 > 0)
		data->player.angle += 356;
	else
		data->player.angle += 4;
}