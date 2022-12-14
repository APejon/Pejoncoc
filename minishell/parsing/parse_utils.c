/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:31:42 by cafriem           #+#    #+#             */
/*   Updated: 2022/12/14 14:44:44 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*everything_smol(char *string)
{
	int	counter;

	counter = 0;
	while (string[counter] != '\n')
	{
		if (string[counter] >= 65 && string[counter] <= 90)
			string[counter] =+ 32;
		counter++;
	}
}
