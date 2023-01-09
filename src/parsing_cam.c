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

static void	check_ta(char *s, t_mrt *mrt)
{
	int		i;
	char	*temp;

	i = -1;
	temp = ft_strtrim(s, "\n");
	free(s);
	if (ft_strlen(temp) > 3)
		exit_error("ERROR\nC CON MAS PARAMETROS DE LOS INDICADOS", 1);
	while (temp[++i])
		if (ft_isdigit(temp[i]) != 1)
			exit_error("ERROR\nCARACTER INCORRECTO", 1);
	mrt->cam->fov = ft_atoi(temp);
	if (mrt->cam->fov > 180)
		exit_error("ERROR\nPARAMETRO FUERA DE RANGO", 1);
}

static void	check_sa(char *s, t_mrt *mrt)
{
	char	**n;
	int		i;

	if (ft_strlen(s) > 17)
		exit_error("ERROR\nC CON MAS PARAMETROS DE LOS INDICADOS", 1);
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
	mrt->cam->vector = init_point(ft_atof(n[0]), ft_atof(n[1]), ft_atof(n[2]));
	if ((mrt->cam->vector->x > 1 || mrt->cam->vector->x < -1)
		|| (mrt->cam->vector->y > 1 || mrt->cam->vector->y < -1)
		|| (mrt->cam->vector->z > 1 || mrt->cam->vector->z < -1))
		exit_error("ERROR\nVECTOR FUERA DE RANGO", 1);
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
}

static void	check_fa(char *s, t_mrt *mrt)
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
	mrt->cam->pov = init_point(ft_atof(n[0]), ft_atof(n[1]), ft_atof(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
}

void	parsing_cam(char **argv, int argc, t_mrt *mrt)
{
	if (argc != 4)
		exit_error("ERROR\nL CON MAS ARGUMENTOS DE LOS INDICADOS", 1);
	check_fa(argv[1], mrt);
	check_sa(argv[2], mrt);
	check_ta(argv[3], mrt);
}
