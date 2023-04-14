/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:56:49 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/12 15:08:18 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Finds the secluded declared environment variable and updates it with
 * an equal "=" sign
 * 
 * @param env The linked list containing environment variables
 * @param variable The variable to be added (concatenated with an "=")
 */
void	msh_update_secluded(t_env *env, char *variable)
{
	char	*variable2;

	variable2 = ft_strjoin(variable, "=");
	ft_bzero(env->variable, ft_strlen(env->variable));
	msh_free(&(env->variable));
	env->variable = ft_strdup(variable2);
	msh_free(&variable2);
}

/**
 * @brief Finds a specific node within the environment, update the variable and
 * return the node
 * 
 * @param env The struct containing the environment variables
 * @param line The variable to be found
 * @return t_env* The node found
 */
t_env	*msh_find_node_ex(t_env *env, char *line)
{
	size_t	len;
	char	*line_t;
	t_env	*point;

	point = env;
	len = ft_strlen(line);
	while (ft_strncmp(line, point->variable, len) && point->next != NULL)
		point = point->next;
	if (!ft_strncmp(line, point->variable, len))
		return (point);
	point = env;
	line_t = ft_strtrim(line, "=");
	len = ft_strlen(line_t);
	while (ft_strncmp(line_t, point->variable, len) && point->next != NULL)
		point = point->next;
	if (point->next == NULL && ft_strncmp(line_t, point->variable, len))
	{
		msh_free(&line_t);
		return (NULL);
	}
	msh_update_secluded(point, line_t);
	msh_free(&line_t);
	return (point);
}

/**
 * @brief Finds a node containing a specific variable then returns it
 * 
 * @param env The linked list containing the environment variables
 * @param line The variable to be found
 * @return char* The variable found within the linked list
 */
char	*msh_find_env_ex(t_env *env, char *line)
{
	size_t	len;
	char	*line_j;
	t_env	*point;

	point = env;
	len = ft_strlen(line) + 1;
	while (ft_strncmp(line, point->variable, len) && point->next != NULL)
		point = point->next;
	if (point->next == NULL && !ft_strncmp(line, point->variable, len))
		return (point->variable);
	line_j = ft_strjoin(line, "=");
	len = ft_strlen(line_j) + 1;
	while (ft_strncmp(line_j, point->variable, len) && point->next != NULL)
		point = point->next;
	if (point->next == NULL && ft_strncmp(line_j, point->variable, len))
	{
		msh_free(&line_j);
		return (NULL);
	}
	msh_free(&line_j);
	return (point->variable);
}
