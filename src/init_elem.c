/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:31:34 by smiro             #+#    #+#             */
/*   Updated: 2023/01/02 13:31:39 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"
#include <mlx.h>

t_sp	*init_sp(char **line)
{
	t_sp	*temp;
	int		i;

	i = -1;
	while (line[++i])
		;
	temp = ft_calloc(sizeof(t_sp), 1);
	if (!temp)
		exit_error("Error malloc", 8);
	parsing_sp(line, i, temp);
	return (temp);
}

t_pl	*init_pl(char **line)
{
	t_pl	*temp;
	int		i;

	i = -1;
	while (line[++i])
		;
	temp = ft_calloc(sizeof(t_pl), 1);
	if (!temp)
		exit_error("Error malloc", 9);
	parsing_pl(line, i, temp);
	temp->normal = pl_normal(temp->vector);
	return (temp);
}

static t_obj	*init_cap(t_cy *cylinder, int top)
{
	t_pl	*pl;
	t_obj	*tempo;

	pl = new_calloc(sizeof(t_pl), 1, 32);
	pl->point = new_cpy(cylinder->point, sizeof(t_point));
	pl->normal = new_calloc(sizeof(t_vector), 1, 321);
	if (top)
	{
		*pl->point = v_mult(cylinder->vector, cylinder->hgt);
		*pl->point = v_sum(pl->point, cylinder->point);
		*pl->normal = *cylinder->vector;
	}
	else
		*pl->normal = v_mult(cylinder->vector, -1);
	pl->rgb = new_cpy(cylinder->rgb, sizeof(t_rgb)); 
	tempo = new_calloc(sizeof(t_obj), 1, 189);
	tempo->elem = pl;
	tempo->id = PL;
	tempo->intx = &pl_inter;
	tempo->doesintx = &pl_doesinter;
	return (tempo);
}

t_cy	*init_cy(char **line)
{
	t_cy	*temp;
	int		i;

	i = -1;
	while (line[++i])
		;
	temp = ft_calloc(sizeof(t_cy), 1);
	if (!temp)
		exit_error("Error malloc", 8);
	parsing_cy(line, i, temp);
	temp->topcap = init_cap(temp, 1);
	temp->bottomcap	= init_cap(temp, 0);
	return (temp);
}

t_img	*new_img(t_mlx	*mlx)
{
	t_img	*img;

	img = ft_calloc(sizeof(t_img), 1);
	if (!img)
		exit_error("Error malloc", 14);
	img->img = mlx_new_image(mlx->mlx, W, H);
	if (!img->img)
		exit_error("Error malloc", 12);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}
