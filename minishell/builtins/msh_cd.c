/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:42:29 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/19 17:11:12 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Uses cd command to move to a target directory
 * 
 * @param shell The struct containing variables of used within the shell
 * @param target Array containing the target directory
 */
void	msh_cd_target(t_shell *shell, t_command *command)
{
	char	*oldpwd;
	char	*dest;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = msh_find_env(shell->env, "PWD=");
	if (!oldpwd)
		return ;
	if (command->target == '/')
		dest = ft_strdup(command->target);
	else
	{
		dest = ft_strjoin(oldpwd, "/");
		dest = ft_free_strjoin(dest, command->target, 1);
	}
	if (chdir(dest) == -1)
		pt_printf("minishell: %s: %s: %s", command->command,
			command->target, strerror(errno));
	msh_update_env(shell->env, "OLDPWD=", oldpwd);
	msh_update_env(shell->env, "PWD=", dest);
	msh_free(&oldpwd);
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
	char	*oldpwd;
	char	*end;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = msh_find_env(shell->env, "PWD=");
	if (!oldpwd)
		return ;
	parent = ft_strdup(oldpwd);
	end = ft_strrchr(parent, '/');
	ft_bzero(end, ft_strlen(end));
	if (chdir(parent) == -1)
		pt_printf("minishell: %s: %s: %s", command->command,
			command->target, strerror(errno));
	else
	{
		msh_update_env(shell->env, "OLDPWD=", oldpwd);
		msh_update_env(shell->env, "PWD=", parent);
		msh_free(&oldpwd);
		msh_free(&parent);
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
	char	*oldpwd;
	char	*home;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = msh_find_env(shell->env, "PWD=");
	if (!oldpwd)
		return ;
	home = ft_substr(msh_find_env(shell->env, "HOME="), 0,
			ft_strlen(msh_find_env(shell->env, "HOME=")));
	if (chdir(home) == -1)
		pt_printf("minishell: %s: %s: %s", command->command,
			command->target, strerror(errno));
	msh_update_env(shell->env, "OLDPWD=", oldpwd);
	msh_update_env(shell->env, "PWD=", home);
	msh_free(&oldpwd);
	msh_free(&home);
}

/**
 * @brief Uses the cd command to move directories within the shell
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command The struct containing the command's components
 */
void	msh_cd(t_shell *shell, t_command *command)
{
	if (!ft_strncmp(command->flag, "-L", 3)
		|| !ft_strncmp(command->flag, "-P", 3)
		|| !ft_strncmp(command->flag, "-LP", 4)
		|| command->flag == NULL)
	{
		if (!command->target)
			msh_cd_home(shell, command);
		else if (!ft_strncmp(command->target, ".", 2))
			return ;
		else if (!ft_strncmp(command->target, "..", 3))
			msh_cd_parent(shell, command);
		else
			msh_cd_target(shell, command);
		shell->exit_code = 0;
	}
	else
		msh_print_flerror(shell, command, "[-L|-P] [dir]");
}
