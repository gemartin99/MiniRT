/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:28:12 by smiro             #+#    #+#             */
/*   Updated: 2023/01/03 11:28:14 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/*
void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	raytrace(t_mrt *mrt)
{
	float	x;
	float	y;
	t_intersection i;

	y = 0;
	while(y < H)
	{
		x = 0;
		while (x < W)
		{
			i.ray = makeray(new_perp(mrt->cam), vector2((2 * x) / (float)W - 1, (2 * y) / (float)H - 1));
			if (obj_int(&i, mrt->obj))
				pixel_put(mrt->img, x, y, 0x00FFFFFF);
			x++;
		}
		y++;
	}
}

void	start(t_mrt *mrt)
{
	mlx_put_image_to_window(mrt->mlx->mlx, mrt->mlx->win, mrt->img->img, 0, 0);
	mlx_hook(mrt->mlx->win, 17, 0, close_program, mrt);
	mlx_hook(mrt->mlx->win, 2, 0, key_hook, mrt);
	mlx_loop(mrt->mlx->mlx);
}
*/