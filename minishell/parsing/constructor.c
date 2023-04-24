/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:47:19 by yhaidar           #+#    #+#             */
/*   Updated: 2023/04/24 18:49:24 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_syntax(t_shell *data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		data->par->error = line[i];
		if (line[0] == '|')
			return (0);
		if (is_meta_char(line[i]))
		{
			if ((line[i] == '<' || line[i] == '>') && line[i] == line[i + 1])
				i++;
			i++;
			while (ft_isspace(line[i]))
				i++;
			if (is_meta_char(line[i]) || !line[i])
				return (0);
		}
		i++;
	}
	return (1);
}

/* Cleans the Command List, If All Clean then Cleans Commands as well */
// static int	free_parser(t_list **lexar, char **line)
static int	free_parser(t_shell *data, t_list **lexar, char **line,
	int clean_all)
{
	int	i;

	free(*line);
	if (clean_all == 2)
	{
		ft_lstclear(lexar, free);
		ft_lstclear(data->par->sections, \
		(void (*)(void *))free_array);
	}
	if (clean_all == 3)
	{
		ft_lstclear(lexar, free);
		msh_free(&data->par->lexar);
		i = -1;
		while (data->par->sections[++i])
		{
			ft_lstclear(&data->par->sections[i], free);
			msh_free(&data->par->sections[i]);
		}
		msh_free(&data->par->sections);
	}
	return (0);
}

/* Detecting and Handling Errors in the Parser */
static int	parser_error(t_shell *data, t_list **lexar, char **line,
	char *err)
{
	if (err)
	{
		if (data->par->error)
		{
			ft_putstr_fd(err, 2);
			ft_putstr_fd("\'", 2);
			ft_putchar_fd(data->par->error, 2);
			ft_putendl_fd("\'", 2);
			free_parser(data, lexar, line, 1);
		}
		else
		{
			ft_putendl_fd(err, 2);
			free_parser(data, lexar, line, 2);
		}
	}
	data->exit_code = 258;
	return (0);
}

/* Sending Input in order to Construct: The ENV 2D Char Array, /
the Parser, The Command List, and Freeing the Parser */
int	parser(t_shell *data, char **line)
{
	if (!check_syntax(data, *line))
		return (parser_error(data, NULL, line,
				"minishell: syntax error: near unexpected token: "));
	data->par->error = 0;
	if (!env_resolver(data, line))
		return (free_parser(data, NULL, line, 1));
	if (!lexer(*line, &data->par->lexar))
		return (parser_error(data, &data->par->lexar, line,
				"minishell: syntax error: unclosed quotes"));
	split_into_commands(data, data->par->lexar);
	free_parser(data, &data->par->lexar, line, 3);
	if (data->par->pipe)
		ft_lstclear(&data->par->pipe, free);
	return (1);
}
