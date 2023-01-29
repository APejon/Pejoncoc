/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_locate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:44:52 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/29 14:57:11 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Finds the paths from the environment variable linked list and extracts
 * them
 * 
 * @param enviro The struct containing the environment variables
 * @return char* The paths extracted
 */
char	*msh_find_path(const t_env *enviro)
{
	t_env	*pointer;

	pointer = enviro;
	while (pointer)
	{
		if (!ft_strncmp(pointer->variable, "PATH=", 5) || pointer->next == NULL)
			break ;
		pointer = pointer->next;
	}
	if (pointer->next == NULL && ft_strncmp(pointer->variable, "PATH=", 5))
		return (NULL);
	return (pointer->value);
}

/**
 * @brief Finds the paths using msh_find_path and splits it to different
 * retrievable paths.
 * 
 * @param shell The struct containing variables of used within the shell
 * @return char** All paths found in a 2D array
 */
char	**msh_locate(t_shell *shell, t_command *command)
{
	char	*path;
	char	**cmd_paths;

	cmd_paths = NULL;
	path = msh_find_path(shell->env);
	if (path == NULL)
		msh_print_error(shell, command->cmd_args[0],
			"No such file or directory", 127);
	else
		cmd_paths = ft_split(path, ':');
	return (cmd_paths);
}
