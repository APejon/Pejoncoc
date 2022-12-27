/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:31:42 by cafriem           #+#    #+#             */
/*   Updated: 2022/12/26 15:23:16 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	everything_smol(char *string, size_t len)
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

void	op_finder(char *string, t_shell shell, char *string2)
{
	int	counter;

	counter = 0;
	while (string[counter] != '\0' || string[counter] != '|')
		counter++;
	string2 = ft_substr(string, counter, ft_strlen(string));
}

int	n_finder(char *string, t_shell shell)
{
	int	sp_marks;
	int	counter;
	int	end;

	counter = 0;
	sp_marks = 0;
	end = ft_strlen(string);
	while (string[counter] != '\0')
	{
		if (string[counter] == '"')
			sp_marks++;
		if (string[counter] == '|' && (sp_marks % 2 == 0))
			return (counter - 1);
		counter++;
	}
	return (counter);
}

// void	wrong_command(char *string, t_shell shell)
// {
// 	char	**point;

// 	point = ft_split(string, ' ');
// 	shell->command->command = point[0];
// }
