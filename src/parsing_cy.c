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

static void	check_fia(char *s, t_cy *cy)
{
	char	**n;
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == '.')
			exit_error("ERROR\nCARACTER INCORRECTO", 1);
	i = 0;
	n = ft_split(s, ',');
	if (!n)
		exit_error("Error malloc", 5);
	while (n[i])
		i++;
	if (i != 3)
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	cy->rgb = init_rgb(ft_atoi(n[0]), ft_atoi(n[1]), ft_atoi(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
	if ((cy->rgb->r < 0 || cy->rgb->r > 255)
		|| (cy->rgb->g < 0 || cy->rgb->g > 255)
		|| (cy->rgb->b < 0 || cy->rgb->b > 255))
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
}

static float	check_ta_foa(char *s)
{
	int	i;

	i = -1;
	if (ft_strlen(s) == 1 && ft_isdigit(s[0]) != 0)
		return (ft_atof(s));
	check_point(s);
	while (s[++i])
	{
		if (ft_isdigit(s[i]) == 0 && s[i] != '.')
			exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	}
	return (ft_atof(s));
}

static void	check_sa(char *s, t_cy *cy)
{
	char	**n;
	int		i;

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
	cy->vector = init_point(ft_atof(n[0]), ft_atof(n[1]), ft_atof(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
	if ((cy->vector->x > 1 || cy->vector->x < -1)
		|| (cy->vector->y > 1 || cy->vector->y < -1)
		|| (cy->vector->z > 1 || cy->vector->z < -1))
		exit_error("ERROR\nPARAMETROS VECTOR INCORRECTOS", 1);
}

static void	check_fa(char *s, t_cy *cy)
{
	char	**n;
	int		i;

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
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	cy->point = init_point(ft_atof(n[0]), ft_atof(n[1]), ft_atof(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
}

void	parsing_cy(char **argv, int argc, t_cy *cy)
{
	if (argc != 6)
		exit_error("ERROR\nCY CON MAS ARGUMENTOS DE LOS INDICADOS", 1);
	check_fa(argv[1], cy);
	check_sa(argv[2], cy);
	cy->dia = check_ta_foa(argv[3]);
	cy->hgt = check_ta_foa(argv[4]);
	check_fia(argv[5], cy);
}
