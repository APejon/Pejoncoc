/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:42:22 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/14 13:59:20 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*DESCRIPTION

Finds a specific line within the environment variable

PARAMETERS

char **envp: the environment variables, used to help programs know what
directory to install files in, where to store temporary files and find user
profile settings.

NOTE

Remember that envp is a 2D array, so *envp is each line when comparing, type
env in your terminal to find the environmental variables.

Here strncmp is comparing the given string to the string within the 
environment variable

*/
char	*msh_find_env(char **envp, char *line)
{
	size_t	len;

	len = ft_strlen(line);
	while (ft_strncmp(line, *envp, len) && *envp != NULL)
		envp++;
	if (*envp == NULL)
		return (NULL);
	else
		return (*envp + len);
}
