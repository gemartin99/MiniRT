/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:45:54 by smiro             #+#    #+#             */
/*   Updated: 2023/01/02 12:45:55 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	printrgb(t_rgb *c, char *str)
{
	printf("%s:", str);
	printf(" R:%d, G:%d, B:%d\n", c->r, c->g, c->b);
}

int	create_trgb(t_rgb	*color)
{
	int	rgb;

	rgb = 00 << 24 | color->r << 16 | color->g << 8 | color->b;
	free(color);
	return (rgb);
}

t_rgb	*color_mult(t_rgb *c1, t_rgb *c2)
{
	t_rgb	*temp;

	temp = new_calloc(sizeof(t_rgb), 1, 92);
	temp->r = ((float)c1->r / 255) * ((float)c2->r / 255) * 255;
	temp->g = ((float)c1->g / 255) * ((float)c2->g / 255) * 255;
	temp->b = ((float)c1->b / 255) * ((float)c2->b / 255) * 255;
	return (temp);
}

t_rgb	*color_sum(t_rgb *c1, t_rgb *c2)
{
	t_rgb	*temp;

	temp = new_calloc(sizeof(t_rgb), 1, 92);
	temp->r = c1->r + c2->r;
	if (temp->r > 255)
		temp->r = 255;
	temp->g = c1->g + c2->g;
	if (temp->g > 255)
		temp->g = 255;
	temp->b = c1->b + c2->b;
	if (temp->b > 255)
		temp->b = 255;
	free(c1);
	free(c2);
	return (temp);
}

t_rgb	*intensity(t_rgb *c, float intensity)
{
	t_rgb	*temp;

	temp = new_calloc(sizeof(t_rgb), 1, 92);
	temp->r = c->r * intensity;
	temp->g = c->g * intensity;
	temp->b = c->b * intensity;
	return (temp);
}
