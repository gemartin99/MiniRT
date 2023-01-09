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
#include "../inc/libft/libft.h"
#include <mlx.h>

void	exit_error(char *str, int n)
{
	ft_putendl_fd(str, 2);
	exit(n);
}

void	*new_calloc(size_t n, size_t size, int error)
{
	void	*temp;

	temp = ft_calloc(n, size);
	if (!temp)
		exit_error("Error malloc", error);
	return (temp);
}
