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

static void	check_ta(char *s, t_lp *lp)
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
	lp->rgb = init_rgb(ft_atoi(n[0]), ft_atoi(n[1]), ft_atoi(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
	if ((lp->rgb->r < 0 || lp->rgb->r > 255)
		|| (lp->rgb->g < 0 || lp->rgb->g > 255)
		|| (lp->rgb->b < 0 || lp->rgb->b > 255))
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
}

static void	check_sa(char *s)
{
	int	i;

	i = -1;
	if (ft_strlen(s) == 1 && ft_isdigit(s[0]) != 0)
		return ;
	check_point(s);
	while (s[++i])
	{
		if (ft_isdigit(s[i]) == 0 && s[i] != '.')
			exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	}
}

static void	check_fa(char *s, t_lp *lp)
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
	lp->lpoint = init_point(ft_atof(n[0]), ft_atof(n[1]), ft_atof(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
}

void	parsing_lp(char **argv, int argc, t_lp *lp)
{
	if (argc != 4)
		exit_error("ERROR\nC CON NUMERO DE ARGUMENTOS INCORRECTO", 1);
	check_fa(argv[1], lp);
	check_sa(argv[2]);
	lp->brt = ft_atof(argv[2]);
	if (lp->brt > 1 || lp->brt < 0)
		exit_error("ERROR\nPARAMETRO INCORRECTO AL\n", 1);
	if (ft_strlen(argv[3]) > 12)
		exit_error("ERROR\nARGUMENTO CON DEMASIADOS CARACTERES\n", 1);
	check_ta(argv[3], lp);
}
