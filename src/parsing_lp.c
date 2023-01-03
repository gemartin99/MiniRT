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

static void check_fa(char *s, t_mrt *mrt)
{
	char **nums;
	int i;

	nums = ft_split(s, ',');
	if (!nums)
		exit_error("Error malloc", 6);
	i = -1;
	while (nums[++i])
	{
		check_less(nums[i]);
	}
	if (i != 3)
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	mrt->lp->lpoint = init_point(ft_atof(nums[0]), ft_atof(nums[1]), ft_atof(nums[2]));
	i = -1;
	while (nums[++i])
		free(nums[i]);
	free(nums);
	printf("x%f y%f z%f\n", mrt->lp->lpoint->x, mrt->lp->lpoint->y, mrt->lp->lpoint->z);
}

void parsing_lp(char **argv, int argc, t_mrt *mrt)
{
	if (argc != 4)
		exit_error("ERROR\nC CON MAS ARGUMENTOS DE LOS INDICADOS", 1);
	check_fa(argv[1], mrt);
	//check_sa(argv[2], mrt);
	//check_ta(argv[3], mrt);
}