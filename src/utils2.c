/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:07:37 by gemartin          #+#    #+#             */
/*   Updated: 2023/01/02 13:07:39 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

t_cam	*ft_last3(t_cam **cam)
{
	t_cam	*temp;

	if (!*cam)
		return (*cam);
	temp = *cam;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_lp	*ft_last2(t_lp **lp)
{
	t_lp	*temp;

	if (!*lp)
		return (*lp);
	temp = *lp;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_obj	*ft_last(t_obj **obj)
{
	t_obj	*temp;

	if (!*obj)
		return (*obj);
	temp = *obj;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	check_point(char *s)

{
	int	i;
	int	j;
	int	c;

	i = -1;
	j = 0;
	c = -1;
	while (s[++i])
	{
		if (s[i] == '.')
			j++;
	}
	i = -1;
	while (s[++i])
	{
		if ((i == 0 && s[i] == '.') || (j > 1))
			exit_error("ERROR\nCARACTER '.' EN POSICION ERRONEA", 1);
		else if (s[i] == '.' && (ft_isdigit(s[i - 1]) != 1
				|| ft_isdigit(s[i + 1]) != 1))
			exit_error("ERROR\nCARACTER '.' EN POSICION ERRONEA", 1);
		else if (s[i] == '.')
			c = i + 4;
		else if (i == c)
			exit_error("ERROR\nMAX 3 DECIMALES", 1);
	}
}

void	check_less(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '-' && i != 0)
			exit_error("ERROR\nCARACTER '-' EN POSICION ERRONEA", 1);
		if (s[0] == '-' && !s[1])
			exit_error("ERROR\nNO HAY CARACTERES NUMERICOS", 1);
	}
}
