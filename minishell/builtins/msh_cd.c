/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:42:29 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/23 14:08:59 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*msh_cd_special(t_shell *shell, t_command *command)
{
	char	*dest;

	dest = NULL;
	if (command->cmd_args[1][0] == '~')
	{
		if (ft_strchr(command->cmd_args[1], '/'))
			dest = ft_strjoin(msh_find_env(shell->env, "HOME="),
					ft_strchr(command->cmd_args[1], '/'));
		else
			dest = ft_strdup(msh_find_env(shell->env, "HOME="));
	}
	return (dest);
}

/**
 * @brief Uses cd command to move to a target directory
 * 
 * @param shell The struct containing variables of used within the shell
 * @param target Array containing the target directory
 */
void	msh_cd_target(t_shell *shell, t_command *command)
{
	char	*dest;

	if (!(shell->oldpwd))
		shell->oldpwd = msh_find_env(shell->env, "PWD=");
	if ((command->cmd_args[1][0]) == '/')
		dest = ft_strdup(command->cmd_args[1]);
	else if (command->cmd_args[1][0] == '~')
		dest = msh_cd_special(shell, command);
	else
	{
		dest = ft_strjoin(shell->oldpwd, "/");
		dest = ft_free_strjoin(dest, command->cmd_args[1], 1);
	}
	if (chdir(dest) == -1)
		msh_print_error(shell, command, strerror(errno), 1);
	else
	{
		msh_update_env(shell->env, "OLDPWD=", shell->oldpwd);
		msh_update_env(shell->env, "PWD=", dest);
		msh_update_dec_env(shell->dec_env, "OLDPWD=", shell->oldpwd);
		msh_update_dec_env(shell->dec_env, "PWD=", dest);
		shell->exit_code = 0;
	}
	msh_free(&dest);
}

/**
 * @brief Uses cd command to move to a parent directory
 * 
 * @param shell The struct containing variables of used within the shell
 * @param parent The string that will contain the path to parent directory
 */
void	msh_cd_parent(t_shell *shell, t_command *command)
{
	char	*parent;
	char	*end;

	if (!(shell->oldpwd))
		shell->oldpwd = msh_find_env(shell->env, "PWD=");
	if (!ft_strncmp(command->cmd_args[1], "..", 3))
	{
		parent = ft_strdup(shell->oldpwd);
		end = ft_strrchr(parent, '/');
		ft_bzero(end, ft_strlen(end));
	}
	else if (!ft_strncmp(command->cmd_args[1], "-", 2))
		parent = msh_cd_special(shell, command);
	if (chdir(parent) == -1)
		msh_print_error(shell, command, strerror(errno), 1);
	else
	{
		msh_update_env(shell->env, "OLDPWD=", shell->oldpwd);
		msh_update_env(shell->env, "PWD=", parent);
		msh_update_dec_env(shell->dec_env, "OLDPWD=", shell->oldpwd);
		msh_update_dec_env(shell->dec_env, "PWD=", parent);
		shell->exit_code = 0;
	}
	msh_free(&parent);
}

/**
 * @brief Uses cd command to move to the home directory stated within the env
 * 
 * @param shell The struct containing variables of used within the shell
 * @param home Array containing the home directory
 */
void	msh_cd_home(t_shell *shell, t_command *command)
{
	char	*home;

	home = msh_find_env(shell->env, "HOME=");
	if (!home)
	{
		msh_print_error(shell, command, "HOME not set", 1);
		return ;
	}
	if (!shell->oldpwd)
		shell->oldpwd = msh_find_env(shell->env, "PWD=");
	if (chdir(home) == -1)
		msh_print_error(shell, command, strerror(errno), 1);
	else
	{
		msh_update_env(shell->env, "OLDPWD=", shell->oldpwd);
		msh_update_env(shell->env, "PWD=", home);
		msh_update_dec_env(shell->dec_env, "OLDPWD=", shell->oldpwd);
		msh_update_dec_env(shell->dec_env, "PWD=", home);
		shell->exit_code = 0;
	}
}

/**
 * @brief Uses the cd command to move directories within the shell
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command The struct containing the command's components
 */
void	msh_cd(t_shell *shell, t_command *command)
{
	if (!command->cmd_args[1])
		msh_cd_home(shell, command);
	else if (!ft_strncmp(command->cmd_args[1], ".", 2))
	{
		shell->exit_code = 0;
		return ;
	}
	else if (!ft_strncmp(command->cmd_args[1], "..", 3))
		msh_cd_parent(shell, command);
	else
		msh_cd_target(shell, command);
}
