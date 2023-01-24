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
	int		i;
	t_rgb	*temp;

	i = -1;
	while (line[++i])
		;
	if (mrt->al)
		exit_error("Error\nThere are more than one Ambient ligth", 1);
	mrt->al = ft_calloc(sizeof(t_al), 1);
	if (!mrt->al)
		exit_error("Error malloc", 2);
	parsing_la(line, i, mrt);
	temp = intensity(mrt->al->rgb, mrt->al->ratio);
	free(mrt->al->rgb);
	mrt->al->rgb = temp;
}

void	init_cam(t_cam **cam, char **line)
{
	int		i;
	t_cam	*temp;

	i = -1;
	while (line[++i])
		;
	temp = ft_calloc(sizeof(t_cam), 1);
	if (!temp)
		exit_error("Error malloc", 6);
	temp->next = NULL;
	if (*cam)
	{
		temp->prev = (ft_last3(cam));
		(ft_last3(cam))->next = temp;
	}
	else
	{
		(*cam) = temp;
		temp->prev = NULL;
	}
	parsing_cam(line, i, temp);
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
	temp->id = id;
	temp->next = NULL;
	if (!temp)
		exit_error("Error malloc", 7);
	if (id == SP)
		temp->elem = init_sp(line);
	else if (id == PL)
		temp->elem = (void *)init_pl(line);
	else if (id == CY)
	{
		temp->elem = (void *)init_cy(line);
	}
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
	put_func(&(mrt->obj));
	start(mrt);
}
