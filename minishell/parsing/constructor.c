/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:47:19 by yhaidar           #+#    #+#             */
/*   Updated: 2023/04/07 21:41:20 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_sections(t_list *section)
{
	ft_lstclear(&section, free);
	msh_free(&section);
}

void	null_making(t_list *lexar)
{
	while (lexar)
	{
		lexar->content = NULL;
		lexar = lexar->next;
	}
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
	char	*tmp;

	tmp = ft_strtrim(*line, " \v\t\f\r\n");
	free(*line);
	*line = tmp;
	if (!*line || !env_resolver(data, line))
		return (parser_error(data, &data->par->lexar, line, NULL));
	if (!lexer(*line, &data->par->lexar))
		return (parser_error(data, &data->par->lexar, line, NULL));
	if (!split_into_commands(data, data->par->lexar))
		return (free_parser(data, &data->par->lexar, line, 1));
	null_making(data->par->lexar);
	ft_lstclear(&data->par->lexar, free);
	msh_free(&data->par->lexar);
	i = -1;
	while (data->par->sections[++i])
		free_sections(data->par->sections[i]);
	if (data->par->pipe)
		ft_lstclear(&data->par->pipe, free);
	return (1);
}
