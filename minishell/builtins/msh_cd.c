/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:42:29 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/14 18:51:03 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_cd_home(t_shell *shell, char *home)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = msh_find_env(shell->u_env, "PWD=");
	if (!oldpwd)
		return ;
	home = ft_substr(msh_find_env(shell->u_env, "HOME="), 0,
			ft_strlen(msh_find_env(shell->u_env, "HOME=")));
	chdir(home);
	msh_update_oldpwd(shell, oldpwd);
	msh_update_pwd(shell, home);
	msh_free(&oldpwd);
	msh_free(&home);
}

void	msh_cd_target(t_shell *shell)
{
	
}

void	msh_cd(t_shell *shell)
{
	char	*home;

	if (shell->command->target)
		msh_cd_target(shell);
	else
	{
		home = NULL;
		msh_cd_home(shell, home);
	}
}
