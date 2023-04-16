/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pipex_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:03:59 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/29 14:57:11 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*DESCRIPTION

Function to get the number of words

PARAMETERS

const char *s: string to be splitted.
char c: the delimiter used for the split.
*/
int	pipex_getwordcount(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i + 1] == '"')
		{
			i += 2;
			while (&s[i] != ft_strrchr(s, '"'))
				i++;
		}
		else if (s[i] == c)
			i++;
		else if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			j++;
			i++;
		}
		else if (s[i] != c && s[i + 1] != c)
			i++;
	}
	return (j);
}

/*DESCRIPTION

the assigning portion of pipex_split to assign characters unto a malloc'ed string

PARAMETERS

const char *s: string to be splitted.
char **str: output of the split string.
char c: the delimiter.
int	count: number of words (or sentences) within the string *s.
*/
void	pipex_assigns(const char *s, char **str, char c, int count)
{
	int	i;
	int	j;
	int	start_index;

	i = 0;
	j = 0;
	while (i < count && s[j])
	{
		while (s[j] == c)
			j++;
		if (s[j] == '"')
			j++;
		start_index = j;
		if (s[j - 1] == '"')
			while (&s[j] != ft_strrchr(s, '"'))
				j++;
		else
			while (s[j] != c && s[j] != '\0')
				j++;
		str[i] = ft_substr(s, start_index, j - start_index);
		i++;
	}
	str[i] = 0;
}

/*DESCRIPTION

Splits the 1D argument of a command to several arguments, skipping any content
within double quotes to ensure sentences can be passed as arguments.

PARAMETERS

const char *s: string to be splitted.
char c: the delimiter used for the split.
*/
char	**pipex_split(const char *s, char c)
{
	char	**str;
	int		count;

	if (!s)
		return (NULL);
	count = pipex_getwordcount(s, c);
	str = (char **)malloc((count + 1) * sizeof(char *));
	if (str == NULL)
		return (str);
	pipex_assigns(s, str, c, count);
	return (str);
}
