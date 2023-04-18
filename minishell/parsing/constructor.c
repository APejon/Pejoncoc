/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:47:19 by yhaidar           #+#    #+#             */
/*   Updated: 2023/04/18 15:06:31 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_sections(t_list *section)
{
	ft_lstclear(&section, free);
	msh_free(&section);
}

static int	check_syntax(t_list **lexar)
{
	char	*string;
	t_list	*search;

	search = *lexar;
	while (search)
	{
		if (!ft_strncmp(search->content, "<", 2)
			|| !ft_strncmp(search->content, ">", 2)
			|| !ft_strncmp(search->content, "<<", 3)
			|| !ft_strncmp(search->content, ">>", 3)
			|| !ft_strncmp(search->content, "|", 2))
		{
			string = (char *)search->next->content;
			if (!ft_strncmp(search->next->content, "<", 2)
				|| !ft_strncmp(search->next->content, ">", 2)
				|| !ft_strncmp(search->next->content, "<<", 3)
				|| !ft_strncmp(search->next->content, ">>", 3)
				|| !ft_strncmp(search->next->content, "|", 2)
				|| string[0] == '\0')
				return (0);
		}
		search = search->next;
	}
	return (1);
}

/* Cleans the Command List, If All Clean then Cleans Commands as well */
// static int	free_parser(t_list **lexar, char **line)
static int	free_parser(t_shell *data, t_list **lexar, char **line,
	int clean_all)
{
	if (*line)
		free(*line);
	ft_lstclear(lexar, free);
	if (clean_all)
	{
		ft_lstclear(data->par->sections, \
		(void (*)(void *))free_array);
	}
	return (0);
}

/* Detecting and Handling Errors in the Parser */
static int	parser_error(t_shell *data, t_list **lexar, char **line,
	char *err)
{
	free_parser(data, lexar, line, 1);
	if (err)
		ft_putendl_fd(err, 2);
	else
		perror(err);
	return (0);
}

/* Sending Input in order to Construct: The ENV 2D Char Array, /
the Parser, The Command List, and Freeing the Parser */
int	parser(t_shell *data, char **line)
{
	int		i;

	env_resolver(data, line);
	if (!lexer(*line, &data->par->lexar))
		return (parser_error(data, &data->par->lexar, line,
				"minishell: syntax error near unexpected token"));
	if (!check_syntax(&data->par->lexar))
		return (parser_error(data, &data->par->lexar, line,
				"minishell: syntax error near unexpected token"));
	split_into_commands(data, data->par->lexar);
	ft_lstclear(&data->par->lexar, free);
	msh_free(&data->par->lexar);
	i = -1;
	while (data->par->sections[++i])
		free_sections(data->par->sections[i]);
	msh_free(&data->par->sections);
	if (data->par->pipe)
		ft_lstclear(&data->par->pipe, free);
	ft_bzero(data->line, ft_strlen(data->line));
	msh_free(&data->line);
	return (1);
}
