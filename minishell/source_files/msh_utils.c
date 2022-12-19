/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:42:22 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/19 16:22:29 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints out an error message
 * 
 * @param shell The struct containing shell variables
 * @param command The struct containing the command
 * @param err_message Error message to show
 */
void	msh_print_error(t_shell *shell, t_command *command, char *err_message)
{
	pt_printf("minishell: %s: %s: %s\n", command->command, command->target,
		err_message);
	shell->exit_code = 1;
}

/**
 * @brief Prints out an error incase of using the wrong flags
 * 
 * @param command The struct containing the command
 * @param rec_flags The reccommended flags to use for the command to work
 */
void	msh_print_flerror(t_shell *shell, t_command *command, char *rec_flags)
{
	pt_printf("minishell: %s: %s: invalid option\n",
		command->command, command->flag);
	pt_printf("%s: usage: %s %s\n", command->command, rec_flags);
	shell->exit_code = 1;
}

/**
 * @brief Frees allocated memory, parameter given are set to void for wider
 * compatability
 * 
 * @param memory The memory to free when no longer needed. 
 */
void	msh_free(void *memory)
{
	if (*(void **)memory != NULL)
		free(*(void **)memory);
	*(void **)memory = NULL;
}
