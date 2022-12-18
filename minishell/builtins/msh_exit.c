/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:43:39 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/18 17:30:23 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	msh_count(char *target)
{
	
}

/**
 * @brief Uses the exit command to terminate the shell and gives an exit code
 * 
 * @param command The struct containing the command's components
 */
void	msh_exit(t_command *command)
{
	int	exit_code;
	int	count;
	int	mult;

	exit_code = 0;
	count = msh_count(command->target);
	if (command->target == NULL)
		exit(0);
	if (command->target)
	{
		if (count == 0)
			//starts with non-numeric value
		if (count > 1)
			//too many arguments
		exit_code = ft_atoi(command->target);
		if (exit_code >= 0 && exit_code <= 255)
			exit(exit_code);
		else if (exit_code >= 255)
			exit(exit_code - 255);
		else if (exit_code <= 0)
			exit(exit_code + 255);
	}
}
