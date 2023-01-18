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
#include "../inc/libft/libft.h"
#include <mlx.h>

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	raytrace(t_mrt *mrt)
{
	float			x;
	float			y;
	t_intersection	*i;
	t_perpective	*p;

	y = 0;
	i = ft_calloc(sizeof(t_intersection), 1);
	p = new_perp(mrt->cam);
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			i->t = RAY_T_MAX;
			i->ray = makeray(p, vector2((2 * x)
						/ (float)W - 1, (2 * y) / (float)H - 1));
			if (obj_int(i, &(mrt->obj)))
			{
				pixel_put(mrt->img, x, y, create_trgb(lightray(i, mrt, i->shape->elem)));
			}
			free(i->ray->origin);
			free(i->ray->direction);
			free(i->ray);
			x++;
		}
		y++;
	}
	free(p->forward);
	free(p->origin);
	free(p->rigth);
	free(p->up);
	free(p);
	free(i);
}

void	start(t_mrt *mrt)
{	
	raytrace(mrt);
	mlx_put_image_to_window(mrt->mlx->mlx, mrt->mlx->win, mrt->img->img, 0, 0);
	mlx_hook(mrt->mlx->win, 17, 0, close_program, mrt);
	mlx_hook(mrt->mlx->win, 2, 0, key_hook, mrt);
	mlx_loop(mrt->mlx->mlx);
}
