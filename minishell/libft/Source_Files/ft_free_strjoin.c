/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:42:36 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/13 13:43:03 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_strjoin(char *s1, char *s2, char flag)
{
	char	*combine;

	combine = ft_strjoin(s1, s2);
	if (flag == '1')
		free (s1);
	if (flag == '2')
	{
		free(s1);
		free(s2);
	}
	if (flag == '3')
		free (s2);
	return (combine);
}
