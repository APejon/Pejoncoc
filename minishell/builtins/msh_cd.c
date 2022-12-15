/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:42:29 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/15 18:05:22 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Uses cd command to move to a target directory
 * 
 * @param shell The struct containing variables of used within the shell
 * @param target Array containing the target directory
 */
void	msh_cd_target(t_shell *shell, char *target)
{
	char	*oldpwd;
	char	*dest;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = msh_find_env(shell->env, "PWD=");
	if (!oldpwd)
		return ;
	if (*target == '/')
		dest = ft_strdup(target);
	else
	{
		dest = ft_strjoin(oldpwd, "/");
		dest = ft_free_strjoin(dest, target, 1);
	}
	chdir(dest);
	msh_update_env(shell->env, "OLDPWD=", oldpwd);
	msh_update_env(shell->env, "PWD=", dest);
	msh_free(&oldpwd);
	msh_free(&dest);
}

/**
 * @brief Uses cd command to move to a parent directory
 * 
 * @param shell The struct containing variables of used within the shell
 */
void	msh_cd_parent(t_shell *shell, char *parent)
{
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
	chdir(parent);
	msh_update_env(shell->env, "OLDPWD=", oldpwd);
	msh_update_env(shell->env, "PWD=", parent);
	msh_free(&oldpwd);
	msh_free(&parent);
}

/**
 * @brief Uses cd command to move to the home directory stated within the env
 * 
 * @param shell The struct containing variables of used within the shell
 * @param home Array containing the home directory
 */
void	msh_cd_home(t_shell *shell, char *home)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = msh_find_env(shell->env, "PWD=");
	if (!oldpwd)
		return ;
	home = ft_substr(msh_find_env(shell->env, "HOME="), 0,
			ft_strlen(msh_find_env(shell->env, "HOME=")));
	chdir(home);
	msh_update_env(shell->env, "OLDPWD=", oldpwd);
	msh_update_env(shell->env, "PWD=", home);
	msh_free(&oldpwd);
	msh_free(&home);
}

/**
 * @brief Uses the cd command to move directories within the shell
 * 
 * @param shell The struct containing variables of used within the shell
 */
void	msh_cd(t_shell *shell)
{
	char	*home;
	char	*parent;

	if (!shell->command->target)
	{
		home = NULL;
		msh_cd_home(shell, home);
	}
	else if (!ft_strncmp(shell->command->target, ".", 1))
		return ;
	else if (!ft_strncmp(shell->command->target, "..", 2))
	{
		parent = NULL;
		msh_cd_parent(shell, parent);
	}
	else
	{
		msh_cd_target(shell, shell->command->target);
	}
}
