/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:27:12 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/30 16:20:42 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Finds the last node of an environment variable struct
 * 
 * @param env The struct containing the environment variables
 * @return t_env* Pointer to the end of the struct (Linked List)
 */
t_env	*msh_find_last_node(t_env *env)
{
	t_env	*end;
	t_env	*point;

	point = env;
	while (point->next != NULL)
		point = point->next;
	end = point;
	return (end);
}

/**
 * @brief Finds a specific node within the environment
 * 
 * @param env The struct containing the environment variables
 * @param line The variable to be found
 * @return t_env* The node found
 */
t_env	*msh_find_node(t_env *env, char *line)
{
	size_t	len;
	t_env	*point;

	point = env;
	len = ft_strlen(line);
	while (ft_strncmp(line, point->variable, len) && point->next != NULL)
		point = point->next;
	if (point->next == NULL && !ft_strncmp(line, point->variable, len))
		return (NULL);
	else
		return (point);
}

/*DESCRIPTION

Finds a specific line within the environment variable

PARAMETERS

char *envp: the environment variables, used to help programs know what
directory to install files in, where to store temporary files and find user
profile settings.
char *line: The target to be found within the env.

NOTE

Remember that envp is a 2D array, so *envp is each line when comparing, type
env in your terminal to find the environmental variables.

Here strncmp is comparing the given string to the string within the 
environment variable

*/
char	*msh_find_env(t_env *env, char *line)
{
	size_t	len;
	t_env	*point;

	point = env;
	len = ft_strlen(line);
	while (ft_strncmp(line, point->variable, len) && point->next != NULL)
		point = point->next;
	if (point->next == NULL && !ft_strncmp(line, point->variable, len))
		return (NULL);
	else
		return (point->value);
}