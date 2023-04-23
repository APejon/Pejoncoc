/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:47:19 by yhaidar           #+#    #+#             */
/*   Updated: 2023/04/23 11:27:16 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_meta_syntax(t_list *search)
{
	if (search)
	{
		if (!ft_strncmp(search->content, "<", 2)
			|| !ft_strncmp(search->content, ">", 2)
			|| !ft_strncmp(search->content, "<<", 3)
			|| !ft_strncmp(search->content, ">>", 3)
			|| !ft_strncmp(search->content, "|", 2))
			return (1);
		else
			return (0);
	}
	else
		return (1);
}

static char	*check_syntax(t_shell *data, t_list **lexar)
{
	t_list	*search;

	search = *lexar;
	while (search)
	{
		if (is_meta_syntax(search))
		{
			data->par->error = (char *)search->content;
			if (search->next)
			{
				if (!ft_strncmp(search->content, "|", 2)
					&& is_str_redir(search->next->content))
					search = search->next;
				search = search->next;
				if (is_meta_syntax(search))
					return (data->par->error);
			}
			else
				return (data->par->error);
		}
		search = search->next;
	}
	return (NULL);
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
	if (err)
	{
		if (data->par->error)
		{
			ft_putstr_fd(err, 2);
			ft_putstr_fd("\'", 2);
			ft_putstr_fd(data->par->error, 2);
			ft_putendl_fd("\'", 2);
		}
		else
			ft_putendl_fd(err, 2);
	}
	else
		perror(err);
	free_parser(data, lexar, line, 1);
	data->exit_code = 258;
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
				"minishell: syntax error: unclosed quotes"));
	if (check_syntax(data, &data->par->lexar))
		return (parser_error(data, &data->par->lexar, line,
				"minishell: syntax error: near unexpected token: "));
	split_into_commands(data, data->par->lexar);
	ft_lstclear(&data->par->lexar, free);
	msh_free(&data->par->lexar);
	i = -1;
	while (data->par->sections[++i])
	{
		ft_lstclear(&data->par->sections[i], free);
		msh_free(&data->par->sections[i]);
	}
	msh_free(&data->par->sections);
	if (data->par->pipe)
		ft_lstclear(&data->par->pipe, free);
	ft_bzero(data->line, ft_strlen(data->line));
	msh_free(&data->line);
	return (1);
}
