/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_structs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:34:43 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/12 15:56:35 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_direct	*redir_content_init(t_shell *data, t_direct *redir,
				t_list *search)
{
	redir = malloc(sizeof(t_direct));
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
	return (redir);
}

t_direct	**redirs_transfer(t_shell *data, t_list *section, int no_of_redirs)
{
	int			i;
	t_list		*search;
	t_direct	**redirs;

	if (no_of_redirs == 0)
		return (NULL);
	redirs = malloc(sizeof(t_direct *) * (no_of_redirs + 1));
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
	args = malloc(sizeof(char *) * (no_of_cmd_args + 1));
	i = 0;
	search = section;
	while (i < no_of_cmd_args)
	{
		if (is_str_redir(search->content))
			search = search->next;
		else
		{
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
		search = search->next;
	}
	data->par->no_of_cmd_args = count_args;
	data->par->no_of_redirs = count_redirs;
}

void	transfer_structs(t_shell *data, t_list *section, int i)
{
	data->command[i]->fd_in = STDIN_FILENO;
	data->command[i]->fd_out = STDOUT_FILENO;
	data->command[i]->p_fd[0] = STDIN_FILENO;
	data->command[i]->p_fd[1] = STDOUT_FILENO;
	data->command[i]->pid = 0;
	data->exit_code = 0;
	count_inputs(data, section);
	data->command[i]->cmd_args = cmd_args_transfer(section,
			data->par->no_of_cmd_args);
	data->command[i]->redir = redirs_transfer(data, section,
			data->par->no_of_redirs);
}
