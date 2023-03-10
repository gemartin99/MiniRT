/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:29:48 by smiro             #+#    #+#             */
/*   Updated: 2023/01/02 17:29:50 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include <mlx.h>

int	close_program(t_mrt *mrt)
{
	mlx_destroy_window(mrt->mlx->mlx, mrt->mlx->win);
	exit(0);
}

int	key_hook(int key, t_mrt *mrt)
{
	if (key == 53)
		close_program(mrt);
	if (key == 123)
	{
		mrt->cam = mrt->cam->prev;
		mlx_put_image_to_window(mrt->mlx->mlx,
			mrt->mlx->win, mrt->cam->img->img, 0, 0);
	}
	if (key == 124)
	{
		mrt->cam = mrt->cam->next;
		mlx_put_image_to_window(mrt->mlx->mlx,
			mrt->mlx->win, mrt->cam->img->img, 0, 0);
	}
	return (0);
}
