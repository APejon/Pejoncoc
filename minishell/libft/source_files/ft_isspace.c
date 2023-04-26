/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:56:06 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/26 18:56:52 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks whether the character is any form of spaces
 * 
 * @param c Character to be checked
 * @return int Whether it is a number or not as a number
 */
int	ft_isspace(int c)
{
	if (c == '\v' || c == '\f' || c == '\r'
		|| c == '\t' || c == '\n' || c == ' ')
		return (1);
	return (0);
}
