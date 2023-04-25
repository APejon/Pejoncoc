/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambigious.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:28:40 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/25 18:04:20 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ambigious_redir(char *str, int idx, int length, char *replacement)
{
	int	i[2];

	i[0] = idx - 1;
	i[1] = idx + length;
	if (replacement)
	{
		if (replacement[0] == '\0' && str[length] != '\0')
		{
			while (ft_isspace(str[i[0]]))
				i[0]--;
			if (str[i[0]] == '<' || str[i[0]] == '>')
			{
				while (ft_isspace(str[i[1]]))
					i[1]++;
				if (str[i[1]] == '<' || str[i[1]] == '>')
				{
					msh_free(&replacement);
					write (2, "minishell: ambigious redirect\n", 31);
					write (2, "fuck you :)\n", 13);
					return (1);
				}
			}
		}
	}
	return (0);
}
