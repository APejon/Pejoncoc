/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:19:12 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/12 19:28:59 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	char	**msh_convert(const t_env *enviro)
// {
// 	t_env *pointer;

// 	pointer = 
// }
/**
 * @brief Identifies whether the commands are accessable or not, then returns it
 * 
 * @param paths The paths extracted from the environment variables
 * @param cmd The command to be checked on
 * @return char* accessible and executable command
 */
static char	*msh_retrieve_command(char **paths, char *cmd)
{
	char	*temp;
	char	*bash_command;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (*paths)
	{
		if (!cmd)
			break ;
		temp = ft_strjoin(*paths, "/");
		bash_command = ft_strjoin(temp, cmd);
		if (access(bash_command, X_OK) == 0)
		{
			free (temp);
			return (bash_command);
		}
		free (bash_command);
		free (temp);
		paths++;
	}
	return (NULL);
}

/**
 * @brief Executes a given command
 * 
 * @param shell The struct containing variables of used within the shell
 * @param cmd_paths The paths extracted from the environment variables
 * @note Needs to convert linked list environment variable to a 2D array
 * environment variable
 */
void	msh_execute(t_shell *shell, char **cmd_paths)
{
	char	**cmd_args;
	char	**envp;
	char	*cmd;

	if (check_doublequotes(shell->command->target))
		cmd_args = msh_pipex_split(shell->command->target, ' ');
	else
		cmd_args = ft_split(shell->command->target, ' ');
	cmd = retrieve_cmd(cmd_paths, shell->command->command);
	if (!cmd)
		msh_print_error(shell, shell->command, "command not found", 127);
	envp = msh_convert(shell->env);
	execve(cmd, cmd_args, envp);
}
