/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:42:29 by amalbrei          #+#    #+#             */
/*   Updated: 2023/02/27 13:35:31 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		dest = command->cmd_args[1];
	else
	{
		dest = ft_strjoin(shell->oldpwd, "/");
		dest = ft_free_strjoin(dest, command->cmd_args[1], '1');
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
	parent = shell->oldpwd;
	end = ft_strrchr(parent, '/');
	ft_bzero(end, ft_strlen(end));
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
	else
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
