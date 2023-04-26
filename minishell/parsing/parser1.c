/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:47:35 by yhaidar           #+#    #+#             */
/*   Updated: 2023/04/26 20:18:05 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Removing the Quotes */
int	clean_quote(char **str)
{
	int		i;
	char	quote;
	char	*tmp;

	quote = 0;
	i = 0;
	while ((*str)[i])
	{
		if ((!quote && ((*str)[i] == '"' || (*str)[i] == '\''))
			|| (quote && (*str)[i] == quote))
		{
			if (!quote && ((*str)[i] == '"' || (*str)[i] == '\''))
				quote = (*str)[i];
			else if (quote && (*str)[i] == quote)
				quote = 0;
			tmp = str_remove_char_at1(*str, i);
			free(*str);
			if (!tmp)
				return (0);
			*str = tmp;
		}
		else
			i++;
	}
	return (1);
}

/*	Dividing in to Substrings and Sending the Substrings
    to have the Quotes Removed, Creating the List */
static int	get_clean_input(char *line, t_list **lexar_list,
	int *start, int *end)
{
	char	*con;

	if (line[0] == '\0')
		con = ft_strdup(line);
	else
		con = ft_substr(line, *start, *end - *start);
	if (!con)
		return (0);
	if ((con[0] == '"' || con[0] == '\'') && is_meta_char(con[1])
		&& (con[2] == '"' || con[2] == '\'' || is_meta_char(con[2])))
		ft_laddb(lexar_list, ft_ln(con));
	else
	{
		if (!clean_quote(&con))
			return (0);
		ft_laddb(lexar_list, ft_ln(con));
	}
	while (line[*end] && ft_isspace(line[*end]))
		(*end)++;
	*start = *end;
	return (1);
}

/*	Checking if in Line there is a In File Char or Here Doc Char	*/
static void	get_metachar_end(char *line, int *end)
{
	if ((line[*end] == '>' && line[*end + 1] == '>')
		|| (line[*end] == '<' && line[*end + 1] == '<'))
		*end += 2;
	else
		*end += 1;
}

/*	Finding the Last Quote	*/
static int	get_end(char *line, int *end)
{
	char	quote;

	if (line[*end] == '"' || line[*end] == '\'')
	{
		quote = line[*end];
		(*end)++;
		while (line[*end] && quote != line[*end])
			(*end)++;
		if (line[*end])
			(*end)++;
		else
			return (0);
		return (1);
	}
	else if (is_meta_char(line[*end]) && *end == 0)
		get_metachar_end(line, end);
	else if (is_meta_char(line[*end]) && line[*end - 1] != '\\')
		get_metachar_end(line, end);
	else
		(*end)++;
	return (1);
}

/*	Checking for Quotes, Sending the Line
    to the List Creating Function  */
int	lexer(char *line, t_list **lexar_list)
{
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (line[end])
	{
		if (line[end] == '#')
			ft_bzero(&line[end], ft_strlen(&line[end]));
		if (!get_end(line, &end))
			return (0);
		if (line[start] && (ft_isspace(line[end]) || is_meta_char(line[end])
				|| is_meta_char(line[end - 1])) && line[end - 1] != '\\')
		{
			if (!get_clean_input(line, lexar_list, &start, &end))
				return (0);
		}
	}
	if (line[start] && !get_clean_input(line, lexar_list, &start, &end))
		return (0);
	return (1);
}
