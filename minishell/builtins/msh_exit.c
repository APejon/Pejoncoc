/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:43:39 by amalbrei          #+#    #+#             */
/*   Updated: 2023/03/16 13:17:09 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Checks whether there are non-numeric characters in target
 * 
 * @param target The array to be read
 * @return int Whether or not there are non-numeric characters, 0 for yes, 1 for
 *  no
 */
static	int	msh_count(char *target)
{
	int	count[2];

	count[0] = 0;
	count[1] = 0;
	while (target[count[0]] >= '0' && target[count[0]] <= '9')
		count[0]++;
	if (target[count[0]] == '\0')
		count[1]++;
	return (count[1]);
}

/**
 * @brief Uses the exit command to terminate the shell and gives an exit code
 * 
 * @param command The struct containing the command's components
 */
void	msh_exit(t_shell *shell, t_command *command)
{
	int	count;

	pt_printf("exit\n");
	shell->exit_code = 0;
	if (command->cmd_args[1])
	{
		if (command->cmd_args[2])
		{
			msh_print_error(shell, command, "too many arguments", 1);
			return ;
		}
		count = msh_count(command->cmd_args[1]);
		if (count == 0)
			msh_print_error(shell, command, "numeric argument required", 255);
		else
			shell->exit_code = ft_atoi(command->cmd_args[1]);
	}
	msh_free_to_exit(shell);
}
