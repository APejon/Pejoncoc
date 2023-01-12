/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:42:22 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/12 17:10:24 by amalbrei         ###   ########.fr       */
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
void	msh_print_error(t_shell *shell, t_command *command, char *err_message,
		int exit)
{
	if (command->target)
		pt_printf("minishell: %s: %s: %s\n", command->command, command->target,
			err_message);
	else
		pt_printf("minishell: %s: %s\n", command->command, err_message);
	shell->exit_code = exit;
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
	pt_printf("%s: usage: %s %s\n", command->command, command->command,
		rec_flags);
	shell->exit_code = 1;
}

/**
 * @brief Frees a node from the environment
 * 
 * @param node The node to be freed
 */
void	msh_free_node(t_env *node)
{
	free(node->variable);
	if (node->value)
		free(node->value);
	free(node);
}

/**
 * @brief Frees an entire list of nodes
 * 
 * @param list The linked list
 */
void	msh_free_list(t_env **list)
{
	t_env	*temp;

	if (list)
	{
		while (*list)
		{
			temp = (*list)->next;
			msh_free_node(*list);
			(*list) = temp;
		}
	}
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
