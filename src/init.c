/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:43:42 by smiro             #+#    #+#             */
/*   Updated: 2023/01/02 12:43:45 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"
#include <mlx.h>

void	init_al(t_mrt *mrt, char **line)
{
	int	i;

	i = -1;
	while (line[++i])
		;
	if (mrt->al)
		exit_error("Error\nThere are more than one Ambient ligth", 1);
	mrt->al = ft_calloc(sizeof(t_al), 1);
	if (!mrt->al)
		exit_error("Error malloc", 2);
	parsing_la(line, i, mrt);	
	mrt->al->rgb = intensity(mrt->al->rgb, mrt->al->ratio);
}

void	init_cam(t_mrt *mrt, char **line)
{
	int	i;

	i = -1;
	while (line[++i])
		;
	if (mrt->cam)
		exit_error("Error\nnThere are more than oneCamera ligth", 3);
	mrt->cam = ft_calloc(sizeof(t_cam), 1);
	if (!mrt->cam)
		exit_error("Error malloc", 4);
	parsing_cam(line, i, mrt);
}

void	init_lp(t_lp **lp, char **line)
{
	int		i;
	t_lp	*temp;

	i = -1;
	while (line[++i])
		;
	temp = ft_calloc(sizeof(t_lp), 1);
	if (!temp)
		exit_error("Error malloc", 6);
	temp->next = NULL;
	if (*lp)
		(ft_last2(lp))->next = temp;
	else
		(*lp) = temp;
	parsing_lp(line, i, temp);
}

void	init_newobj(t_obj **obj, char **line, int id)
{
	t_obj	*temp;

	temp = ft_calloc(sizeof(t_obj), 1);
	if (!temp)
		exit_error("Error malloc", 7);
	if (id == SP)
	{
		temp->id = id;
		temp->elem = init_sp(line);
	}
	else if (id == PL)
	{
		temp->id = id;
		temp->elem = (void *)init_pl(line);
	}
	else if (id == CY)
	{
		temp->id = id;
		temp->elem = (void *)init_cy(line);
	}
	temp->next = NULL;
	if ((*obj))
		(ft_last(obj))->next = temp;
	else
		(*obj) = temp;
}

void	init_mlx(t_mrt	*mrt)
{
	mrt->mlx = ft_calloc(sizeof(t_mlx), 1);
	if (!mrt->mlx)
		exit_error("Error malloc", 13);
	mrt->mlx->mlx = mlx_init();
	if (!mrt->mlx->mlx)
		exit_error("Error malloc", 10);
	mrt->mlx->win = mlx_new_window(mrt->mlx->mlx, W, H, "MiniRT");
	if (!mrt->mlx->win)
		exit_error("Error malloc", 11);
	mrt->img = ft_calloc(sizeof(t_img), 1);
	if (!mrt->img)
		exit_error("Error malloc", 14);
	mrt->img->img = mlx_new_image(mrt->mlx->mlx, W, H);
	if (!mrt->img->img)
		exit_error("Error malloc", 12);
	mrt->img->addr = mlx_get_data_addr(mrt->img->img, &mrt->img->bits_per_pixel,
			&mrt->img->line_length, &mrt->img->endian);
	put_func(&(mrt->obj));	
	start(mrt);
}
