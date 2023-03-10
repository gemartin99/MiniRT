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

static void	check_ta(char *s, t_pl *pl)
{
	char	**n;
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == '.')
			exit_error("ERROR\nCARACTER INCORRECTO", 1);
	i = 0;
	check_doble_coma(s);
	n = ft_split(s, ',');
	if (!n)
		exit_error("Error malloc", 5);
	while (n[i])
		i++;
	if (i != 3)
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	pl->rgb = init_rgb(ft_atoi(n[0]), ft_atoi(n[1]), ft_atoi(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
	if ((pl->rgb->r < 0 || pl->rgb->r > 255)
		|| (pl->rgb->g < 0 || pl->rgb->g > 255)
		|| (pl->rgb->b < 0 || pl->rgb->b > 255))
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
}

static void	check_sa(char *s, t_pl *pl)
{
	char	**n;
	int		i;

	check_doble_coma(s);
	n = ft_split(s, ',');
	if (!n)
		exit_error("Error malloc", 6);
	i = -1;
	while (n[++i])
	{
		check_less(n[i]);
		check_point(n[i]);
	}
	if (i != 3)
		exit_error("ERROR\nPARAMETROS VECTOR INCORRECTOS", 1);
	pl->vector = init_point(ft_atof(n[0]), ft_atof(n[1]), ft_atof(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
	if ((pl->vector->x > 1 || pl->vector->x < -1)
		|| (pl->vector->y > 1 || pl->vector->y < -1)
		|| (pl->vector->z > 1 || pl->vector->z < -1))
		exit_error("ERROR\nPARAMETROS VECTOR INCORRECTOS", 1);
	pl->vector = v_normalized(pl->vector, 1);
}

static void	check_fa(char *s, t_pl *pl)
{
	char	**n;
	int		i;

	check_doble_coma(s);
	n = ft_split(s, ',');
	if (!n)
		exit_error("Error malloc", 6);
	i = -1;
	while (n[++i])
	{
		check_less(n[i]);
		check_point(n[i]);
		check_max_float(n[i]);
	}
	if (i != 3)
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	pl->point = init_point(ft_atof(n[0]), ft_atof(n[1]), ft_atof(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
}

void	parsing_pl(char **argv, int argc, t_pl *pl)
{
	if (argc != 4)
		exit_error("ERROR\nPL CON NUMERO DE ARGUMENTOS INCORRECTO", 1);
	check_fa(argv[1], pl);
	check_sa(argv[2], pl);
	check_ta(argv[3], pl);
}
