/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_structs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:34:43 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/22 13:54:27 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_direct	*redir_content_init(t_shell *data, t_direct *redir,
				t_list *search)
{
	redir = ft_calloc(1, sizeof(t_direct));
	if (!ft_strncmp(search->content, ">", 2))
		redir->direct = RE_OUTPUT;
	else if (!ft_strncmp(search->content, ">>", 3))
		redir->direct = APPEND;
	else if (!ft_strncmp(search->content, "<", 2))
		redir->direct = RE_INPUT;
	else if (!ft_strncmp(search->content, "<<", 3))
	{
		data->nohd++;
		redir->direct = HERE_DOC;
	}
	if (!ft_strncmp(search->content, "<<", 3))
	{
		search = search->next;
		redir->file = ft_strjoin(search->content, "\n");
	}
	else
	{
		search = search->next;
		redir->file = ft_strdup(search->content);
	}
	redir->hd_content = NULL;
	redir->fd = 0;
	return (redir);
}

t_direct	**redirs_transfer(t_shell *data, t_list *section, int no_of_redirs)
{
	int			i;
	t_list		*search;
	t_direct	**redirs;

	if (no_of_redirs == 0)
		return (NULL);
	redirs = ft_calloc((no_of_redirs + 1), (sizeof(t_direct *)));
	i = 0;
	search = section;
	while (i < no_of_redirs)
	{
		if (is_str_redir(search->content))
		{
			redirs[i] = redir_content_init(data, redirs[i], search);
			i++;
		}
		search = search->next;
	}
	redirs[i] = NULL;
	return (redirs);
}

char	**cmd_args_transfer(t_list *section, int no_of_cmd_args)
{
	int		i;
	char	**args;
	t_list	*search;

	if (no_of_cmd_args == 0)
		return (NULL);
	args = ft_calloc((no_of_cmd_args + 1), (sizeof(char *)));
	i = 0;
	search = section;
	while (i < no_of_cmd_args)
	{
		if (is_str_redir(search->content))
			search = search->next;
		else
		{
			edge_case(search);
			args[i] = ft_strdup(search->content);
			i++;
		}
		search = search->next;
	}
	args[i] = NULL;
	return (args);
}

void	count_inputs(t_shell *data, t_list *section)
{
	int		count_args;
	int		count_redirs;
	t_list	*search;

	search = section;
	count_args = 0;
	count_redirs = 0;
	while (search)
	{
		if (is_str_redir(search->content))
		{
			count_redirs++;
			search = search->next;
		}
		else
			count_args++;
		if (search)
			search = search->next;
	}
	data->par->no_of_cmd_args = count_args;
	data->par->no_of_redirs = count_redirs;
}

void	transfer_structs(t_shell *data, t_list *section, int i)
{
	data->command[i]->fd_in = -2;
	data->command[i]->fd_out = -2;
	data->command[i]->p_fd[0] = -2;
	data->command[i]->p_fd[1] = -2;
	data->command[i]->pid = 0;
	g_stdin = 0;
	count_inputs(data, section);
	data->command[i]->cmd_args = cmd_args_transfer(section,
			data->par->no_of_cmd_args);
	data->command[i]->redir = redirs_transfer(data, section,
			data->par->no_of_redirs);
}
