/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:19:12 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/29 14:57:11 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Converts a linked list environment variable into a 2D array for execve
 * 
 * @param enviro The linked list of the environment variables
 * @return char** The environment variables as a 2D array
 */
char	**msh_convert(const t_env *enviro)
{
	char	**envp;
	int		count[2];
	t_env	*pointer;

	count[0] = 0;
	count[1] = 0;
	pointer = enviro;
	while (pointer)
	{
		count[0]++;
		pointer = pointer->next;
	}	
	pointer = enviro;
	envp = (char **)malloc((count[0] + 1) * sizeof(char *));
	while (count[1] < count[0])
	{
		envp[count[1]] = ft_strjoin(pointer->variable, pointer->value);
		pointer = pointer->next;
		count[1]++;
	}
	envp[count[1]] = 0;
	return (envp);
}

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
void	msh_execute(t_shell *shell, t_command *command, char **cmd_paths)
{
	char	**cmd_args;
	char	**envp;
	char	*cmd;

	cmd = retrieve_cmd(cmd_paths, command->cmd_args[0]);
	if (!cmd)
	{
		msh_print_error(shell, shell->command, "command not found", 127);
		exit (shell->exit_code);
	}
	envp = msh_convert(shell->env);
	execve(cmd, command->cmd_args, envp);
}
