/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:42:36 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/22 13:01:32 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Utilized str_join to join two strings then frees accordingly to the 
 * flag
 * 
 * @param s1 First string
 * @param s2 Second string
 * @param flag Flag to identify what to free, 1 for s1, 2 for both, 3 for s2
 * @return char* Joined string
 */
char	*ft_free_strjoin(char *s1, char *s2, int flag)
{
	char	*combine;

	combine = ft_strjoin(s1, s2);
	if (flag == 1)
		ft_free(&s1);
	if (flag == 2)
	{
		ft_free(&s1);
		ft_free(&s2);
	}
	if (flag == 3)
		ft_free(&s2);
	return (combine);
}
