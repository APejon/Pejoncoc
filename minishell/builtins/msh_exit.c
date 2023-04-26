/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:43:39 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/26 19:37:40 by amalbrei         ###   ########.fr       */
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
	while (!ft_isdigit(target[count[0]]) && target[count[0]])
		count[0]++;
	while (target[count[0]] >= '0' && target[count[0]] <= '9')
		count[0]++;
	if (target[count[0]] == '\0' && ft_isdigit(target[count[0] - 1]))
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
	int		count;
	bool	check;

	check = true;
	pt_printf("exit\n");
	if (command->cmd_args[1])
	{
		count = msh_count(command->cmd_args[1]);
		ft_atol(command->cmd_args[1], &check);
		if (count == 0 || check == false)
			msh_print_error(shell, command, "numeric argument required", 255);
		else if (command->cmd_args[2])
		{
			msh_print_error(shell, command, "too many arguments", 1);
			return ;
		}
		else
			shell->exit_code = ft_atol(command->cmd_args[1], &check);
	}
	msh_free_to_exit(shell);
}
