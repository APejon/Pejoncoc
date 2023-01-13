/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_a_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:38:18 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/13 12:21:23 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks whether a command is builtin or executable, parent or child
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command Struct containing the command's details
 * @param flag Checks whether its a command for parent or child
 */
void	msh_check_command(t_shell *shell, t_command *command, char flag)
{
	char	**cmd_paths;

	if (command->command && flag == 'p')
	{
		if (msh_is_builtin(shell))
			msh_allocate_parent(shell);
		else
		{
			cmd_paths = msh_locate(shell);
			if (cmd_paths == NULL)
				return ;
			msh_execute(shell, cmd_paths);
		}
	}
	// if (command->command && flag == 'c')
}

/**
 * @brief Checks on the redirection, whether or not they are there
 * and which one they are.
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command The struct containing the command's components
 */
void	msh_check_link(t_shell *shell, t_command *command)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
		shell->oldpwd = getcwd(NULL, 0);
	if (command->redir == NULL)
		msh_check_command(shell, command, 'p');
	else
	{
		if (command->redir == RE_INPUT)
		else if (command->redir == RE_OUTPUT)
		else if (command->redir == APPEND)
		else if (command->redir == HERE_DOC)
		else
	}
	if (cwd)
		msh_free(&cwd);
}
