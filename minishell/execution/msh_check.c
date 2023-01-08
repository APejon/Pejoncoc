/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:38:18 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/08 18:52:25 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_check(t_shell *shell, t_command *command)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
		shell->oldpwd = getcwd(NULL, 0);
	if (command->command)
	{
		msh_allocate(shell);
		if (shell->yet_to_execute)
		{
			
		}
	}
	if (cwd)
		msh_free(&cwd);
	shell->yet_to_execute = 1;
}
