/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cpyarr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:45:07 by cafriem           #+#    #+#             */
/*   Updated: 2022/12/14 13:20:49 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_cpyarr(int argc, char *argv[], char **string)
{
	int	counter;

	counter = 0;
	string = ft_calloc(argc + 1, sizeof(char *));
	while (counter <= argc)
	{
		string[counter] = ft_calloc(ft_strlen(argv[counter]), sizeof(char *));
		string[counter] = ft_strdup(argv[counter]);
		counter++;
	}
	string[counter] = NULL;
}
