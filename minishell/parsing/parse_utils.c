/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:31:42 by cafriem           #+#    #+#             */
/*   Updated: 2022/12/15 18:46:40 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*everything_smol(char *string, size_t len)
{
	int	counter;

	counter = 0;
	while (counter <= len && string)
	{
		if ((string [counter] >= 65) && (string[counter] <= 90))
			string[counter] += 32;
		counter++;
	}
}
