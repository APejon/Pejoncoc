/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:42:43 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/10 13:32:16 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints out the pwd
 * 
 * @param pwd String containing the current directory
 */
void	msh_print_pwd(char *pwd)
{
	pt_printf("%s\n", pwd);
}

/**
 * @brief Uses the pwd command to Print Working Directory
 * 
 * @param shell Struct containing variables related to the shell
 * @param command Struct containing variables related to a command
 * @note Flags will not be implemented due to the project's request 
 * to NOT handle them
 */
void	msh_pwd(t_shell *shell, t_command *command)
{
	msh_print_pwd(shell->oldpwd);
	shell->exit_code = 0;
}
