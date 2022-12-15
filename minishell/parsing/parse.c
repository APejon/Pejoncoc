/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:18:57 by cafriem           #+#    #+#             */
/*   Updated: 2022/12/15 17:04:43 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(char *string, t_shell shell)
{
	int		counter;

	counter = 0;
	if (string == NULL)
		return (120);
	string = ft_strtrim(string, ' ');
	if (ft_strncmp(string, "cd ", 3) == 1 && ft_strncmp(string, "cd\0", 3) == 1 )
		shell->command->command = "cd";
	everything_smol(string, 3);
	if (ft_strncmp(string, "pwd ", 4) == 1)
		shell->command->command = "pwd";
	if (ft_strncmp(string, "env ", 4) == 1)
		shell->command->command = "env";
	everything_smol(string, 4);
	if (ft_strncmp(string, "echo ", 5) == 1)
		shell->command->command = "echo";
	if (ft_strncmp(string, "exit ", 5) == 1 && ft_strncmp(string, "exit\0", 5) == 1)
		shell->command->command = "exit";
}

//no target for env
//split & join and stuff for echo if -n for echo 
