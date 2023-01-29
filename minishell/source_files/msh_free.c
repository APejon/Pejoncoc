/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:39:41 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/29 14:57:11 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Completely frees all malloced pointers
 * 
 * @param shell The struct containing shell variables
 */
void	msh_complete_free(t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	while (shell->command[++i])
	{
		j = -1;
		while (shell->command[i]->cmd_args[++j])
			msh_free(&shell->command[i]->cmd_args[j]);
		msh_free(&shell->command[i]->cmd_args);
		j = -1;
		while (shell->command[i]->redir[++j])
		{
			msh_free(&shell->command[i]->redir[j]->file);
			msh_free(&shell->command[i]->redir[j]->hd_content);
			msh_free(&shell->command[i]->redir[j]);
		}
		msh_free(&shell->command[i]->redir);
		msh_free(&shell->command[i]);
	}
	msh_free_list(&shell->env);
	msh_free_list(&shell->dec_env);
	msh_free(&shell->oldpwd);
	msh_free(&shell);
}

/**
 * @brief Frees a node from the environment
 * 
 * @param node The node to be freed
 */
void	msh_free_node(t_env *node)
{
	msh_free(&node->variable);
	msh_free(&node->value);
	msh_free(&node);
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