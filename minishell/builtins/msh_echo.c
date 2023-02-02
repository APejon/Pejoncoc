/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:41:02 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/31 20:59:05 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Uses the echo command to print out a message onto the shell terminal
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command The struct containing the command's components
 */
void	msh_echo(t_shell *shell, t_command *command)
{
	int	i;

	if (!command->cmd_args[1])
	{
		if (command->cmd_args[1])
		{
		if (!ft_strncmp(command->cmd_args[1], "-n", 3))
			return ;
		}
		else
			pt_printf("\n");
	}
	else if (!ft_strncmp(command->cmd_args[1], "-n", 3))
	{
		i = 1;
		while (command->cmd_args[++i])
			pt_printf("%s", command->cmd_args[i]);
	}
	else
	{
		i = 0;
		while (command->cmd_args[++i])
			pt_printf("%s", command->cmd_args[i]);
		pt_printf("\n");
	}
	shell->exit_code = 0;
}
