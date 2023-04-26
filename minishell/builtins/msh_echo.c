/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:41:02 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/26 15:55:51 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	msh_print_no_newline(t_command *command, int i)
{
	int	j;

	j = 0;
	if (i == 1)
		j = 1;
	while (command->cmd_args[i])
	{
		if (command->cmd_args[i + 1])
			pt_printf("%s ", command->cmd_args[i]);
		else
			pt_printf("%s", command->cmd_args[i]);
		i++;
	}
	if (j == 1)
		printf("\n");
}

void	msh_no_newline(t_command *command)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	while (command->cmd_args[++i])
	{
		if (!ft_strncmp(command->cmd_args[i], "-n", 2))
		{
			while (command->cmd_args[i][j] == 'n' && command->cmd_args[i][j])
				j++;
			if (command->cmd_args[i][j] != 'n' && command->cmd_args[i][j])
				break ;
		}
		else
			break ;
		j = 2;
	}
	msh_print_no_newline(command, i);
}

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
		pt_printf("\n");
	else if (!ft_strncmp(command->cmd_args[1], "-n", 2))
		msh_no_newline(command);
	else
	{
		i = 0;
		while (command->cmd_args[++i])
		{
			if (command->cmd_args[i + 1])
				pt_printf("%s ", command->cmd_args[i]);
			else
				pt_printf("%s", command->cmd_args[i]);
		}
		pt_printf("\n");
	}
	shell->exit_code = 0;
}
