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

int	check_max_float(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s[0] == '-')
		j++;
	while (s[i + j] && s[i + j] != '.')
		i++;
	if (i > 10)
		exit_error("ERROR\nMAXIMO 10 DIGITOS EN LOS FLOATS", 1);
	return (0);
}

static void	check_ta(char *s, t_cam *cam)
{
	int		i;
	char	*temp;

	i = -1;
	temp = ft_strdup(s);
	free(s);
	s = ft_strtrim(temp, "\n");
	free(temp);
	if (ft_strlen(s) > 3)
		exit_error("ERROR\nC CON MAS PARAMETROS DE LOS INDICADOS", 1);
	while (s[++i])
		if (ft_isdigit(s[i]) != 1)
			exit_error("ERROR\nCARACTER INCORRECTO", 1);
	cam->fov = ft_atoi(s);
	if (cam->fov > 180)
		exit_error("ERROR\nPARAMETRO FUERA DE RANGO", 1);
}

static void	check_sa(char *s, t_cam *cam)
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
	cam->vector = init_point(ft_atof(n[0]), ft_atof(n[1]), ft_atof(n[2]));
	if ((cam->vector->x > 1 || cam->vector->x < -1)
		|| (cam->vector->y > 1 || cam->vector->y < -1)
		|| (cam->vector->z > 1 || cam->vector->z < -1))
		exit_error("ERROR\nVECTOR FUERA DE RANGO", 1);
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
}

static void	check_fa(char *s, t_cam *cam)
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
		check_max_float(n[i]);
	}
	if (i != 3)
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	cam->pov = init_point(ft_atof(n[0]), ft_atof(n[1]), ft_atof(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
}

void	parsing_cam(char **argv, int argc, t_cam *cam)
{
	if (argc != 4)
		exit_error("ERROR\nL CON NUMERO DE ARGUMENTOS INCORRECTO", 1);
	check_fa(argv[1], cam);
	check_sa(argv[2], cam);
	check_ta(argv[3], cam);
}
