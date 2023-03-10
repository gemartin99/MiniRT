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

void	check_doble_coma(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == ',' && !s[i + 1])
			exit_error("ERROR\nNO SE PUEDEN PONER COMAS SIN NUMEROS DESPUES", 1);
		if (s[i] == ',' && s[i + 1] == ',')
			exit_error("ERROR\nNO SE PUEDEN PONER COMAS SEGUIDAS", 1);
		if (s[i] == ',' && !ft_isdigit(s[i + 1]) && s[i + 1] != '-')
			exit_error("ERROR\nNO SE PUEDEN PONER COMAS SIN NUMEROS DESPUES", 1);
		if (s[i] == ',' && !ft_isdigit(s[i - 1]))
			exit_error("ERROR\nNO SE PUEDEN PONER COMAS SIN NUMEROS ANTES", 1);
	}
}

static int	check_sa(char *s, t_mrt *mrt, int i)
{
	char	**n;

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
	mrt->al->rgb = init_rgb(ft_atoi(n[0]), ft_atoi(n[1]), ft_atoi(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
	if ((mrt->al->rgb->r < 0 || mrt->al->rgb->r > 255)
		|| (mrt->al->rgb->g < 0 || mrt->al->rgb->g > 255)
		|| (mrt->al->rgb->b < 0 || mrt->al->rgb->b > 255))
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	return (0);
}

static int	check_fa(char *s)
{
	int	i;

	i = -1;
	if (ft_strlen(s) == 1 && ft_isdigit(s[0]) != 0)
		return (0);
	check_point(s);
	while (s[++i])
	{
		if (ft_isdigit(s[i]) == 0 && s[i] != '.')
			exit_error("ERROR\nCARACTER INCORRECTO", 1);
	}
	return (0);
}

void	parsing_la(char **argv, int argc, t_mrt *mrt)
{
	int	i;

	i = -1;
	if (argc != 3)
		exit_error("ERROR\nA CON NUMERO DE ARGUMENTOS INCORRECTO", 1);
	check_fa(argv[1]);
	mrt->al->ratio = ft_atof(argv[1]);
	if (mrt->al->ratio > 1 || mrt->al->ratio < 0)
		exit_error("ERROR\nPARAMETRO INCORRECTO AL", 1);
	if (ft_strlen(argv[2]) > 12 || check_sa(argv[2], mrt, -1) == -1)
		exit_error("ERROR\nARGUMENTO CON DEMASIADOS CARACTERES", 1);
}
