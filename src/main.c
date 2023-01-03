/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:01:08 by smiro             #+#    #+#             */
/*   Updated: 2023/01/02 15:01:17 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

int main(int argc, char **argv)
{
	t_mrt *mrt;

	mrt = ft_calloc(sizeof(t_mrt), 1);
	if (!mrt)
		exit_error("Malloc error", 1);
	if (argc != 2)
		exit(0);
	parsing(argv[1], mrt);
	//init_mlx(mrt);
	return (0);
}
