/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:38:56 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/31 18:55:06 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Prints out an error message
 * 
 * @param shell The struct containing shell variables
 * @param command The struct containing the command
 * @param err_message Error message to show
 */
void	msh_print_error(t_shell *shell, t_command *command, char *err_message,
		int exit)
{
	int	i;

	if (command->cmd_args)
	{
		i = 1;
		pt_printf("minishell: %s: ", command->cmd_args[0]);
		while (command->cmd_args[i])
		{
			pt_printf("%s: ", command->cmd_args[i]);
			i++;
		}
		pt_printf("%s\n", err_message);
	}
	shell->exit_code = exit;
}
