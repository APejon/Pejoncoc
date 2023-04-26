/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:19:12 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/26 20:40:33 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

struct stat	msh_check_dir(t_shell *shell, t_command *command, char *cmd,
			char **cmd_paths)
{
	int			i;
	struct stat	info;

	info.st_mode = 0;
	i = -1;
	stat(cmd, &info);
	if (ft_strchr(cmd, '/') && S_ISDIR(info.st_mode))
	{
		msh_print_error(shell, command, "is a directory", 126);
		while (cmd_paths[++i])
			msh_free(&cmd_paths[i]);
		msh_free(&cmd_paths);
		msh_free_to_exit(shell);
	}
	if (ft_strchr(cmd, '/') && access(cmd, F_OK))
	{
		msh_print_error(shell, command, "No such file or directory", 127);
		while (cmd_paths[++i])
			msh_free(&cmd_paths[i]);
		msh_free(&cmd_paths);
		msh_free_to_exit(shell);
	}
	return (info);
}

/**
 * @brief Converts a linked list environment variable into a 2D array for execve
 * 
 * @param enviro The linked list of the environment variables
 * @return char** The environment variables as a 2D array
 */
char	**msh_convert(t_env *enviro)
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

	if (access(cmd, X_OK) == 0 && ft_strchr(cmd, '/'))
		return (cmd);
	while (*paths)
	{
		if (!cmd)
			break ;
		temp = ft_strjoin(*paths, "/");
		bash_command = ft_strjoin(temp, cmd);
		if (access(bash_command, X_OK) == 0 && cmd[0] != '\0')
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
	int			i;
	char		**envp;
	char		*cmd;
	struct stat	info;

	i = -1;
	info = msh_check_dir(shell, command, command->cmd_args[0], cmd_paths);
	cmd = msh_retrieve_command(cmd_paths, command->cmd_args[0]);
	if (!cmd)
	{
		while (cmd_paths[++i])
			msh_free(&cmd_paths[i]);
		msh_free(&cmd_paths);
		if (access(command->cmd_args[0], F_OK) || S_ISDIR(info.st_mode))
			msh_print_error(shell, command, "command not found", 127);
		else
			msh_print_error(shell, command, "Permission denied", 126);
		msh_free_to_exit(shell);
	}
	envp = msh_convert(shell->env);
	msh_complete_close(shell, command);
	execve(cmd, command->cmd_args, envp);
	msh_free_to_exit(shell);
}
