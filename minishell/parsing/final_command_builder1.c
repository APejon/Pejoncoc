/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_command_builder1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:47:19 by yhaidar           #+#    #+#             */
/*   Updated: 2023/03/30 17:02:19 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes_in_lexar(t_list *lexar)
{
	t_list	*head;
	int		pipe_counter;

	head = lexar;
	pipe_counter = 1;
	while (head)
	{
		if (!ft_strncmp(head->content, "|", 2))
			pipe_counter++;
		head = head->next;
	}
	if (head)
		null_making(head);
	if (head)
		ft_lstclear(&head, free);
	if (head)
		free(head);
	return (pipe_counter);
}

/* Splits the Lexar List into Command List for executor */
int	split_into_commands(t_shell *data, t_list *lexar)
{
	int		i;
	int		pipe_counter;
	t_list	*head;

	i = 0;
	head = lexar;
	pipe_counter = count_pipes_in_lexar(head);
	data->par->sections = ft_calloc(pipe_counter + 1, \
	sizeof(t_list *));
	while (lexar)
	{
		if (is_str_redir(lexar->content))
			ft_laddb(&data->par->sections[i], ft_ln(lexar->content));
		else if (!ft_strncmp(lexar->content, "|", 2))
		{
			ft_laddb(&data->par->pipe, ft_ln(lexar->content));
			i++;
		}
		else if (!is_str_redir(lexar->content))
			ft_laddb(&data->par->sections[i], ft_ln(lexar->content));
		lexar = lexar->next;
	}
	if (data->par->pipe)
		ft_lstclear(&data->par->pipe, free);
	return (1);
}

/* Get Length of 2D Char Array */
int	char_array_len(char **arr)
{
	int	length;

	length = 0;
	while (arr[length])
		length++;
	return (length);
}

/* Return 1 if String is Redirected */
int	is_str_redir(char *str)
{
	if (!ft_strncmp(str, ">", 2)
		|| !ft_strncmp(str, ">>", 3)
		|| !ft_strncmp(str, "<", 2)
		|| !ft_strncmp(str, "<<", 3))
		return (1);
	return (0);
}
