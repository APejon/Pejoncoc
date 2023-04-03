/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:47:35 by yhaidar           #+#    #+#             */
/*   Updated: 2023/03/30 16:52:05 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Removes char at Index and Removes the New Allocated String */
char	*str_remove_char_at1(char *str, int idx)
{
	char	*new_str;
	char	*start;

	if (!str || idx < 0)
		return (NULL);
	if (idx >= (int)ft_strlen(str))
		return (str);
	new_str = ft_calloc(ft_strlen(str), sizeof(char));
	if (!new_str)
		return (NULL);
	start = new_str;
	while (*str)
	{
		if (idx == 0)
		{
			str++;
			if (!*str)
				break ;
		}
		*new_str = *str;
		str++;
		new_str++;
		idx--;
	}
	return (start);
}

/* Check if the char is a type of Invisible Char */
int	ft_isspace(int c)
{
	if (c == '\v' || c == '\f' || c == '\r'
		|| c == '\t' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

// Only those that we need to interpret in project
int	is_meta_char(int c)
{
	if (c == '>' || c == '<' || c == '|' || c == '$')
		return (1);
	return (0);
}

/* Free 2D Char Array */
void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
