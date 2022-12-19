/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:41:02 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/19 15:57:05 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Uses the echo command to print out a message onto the shell terminal
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command The struct containing the command's components
 */
void	msh_echo(t_shell *shell, t_command *command)
{
	if (command->flag == NULL)
		pt_printf("%s\n", command->target);
	else if (!ft_strncmp(command->flag, "-n", 3))
		pt_printf("%s", command->target);
	else
		pt_printf("%s\n", command->target);
	shell->exit_code = 0;
}
