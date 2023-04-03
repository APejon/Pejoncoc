/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_laddb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:14:51 by yhaidar           #+#    #+#             */
/*   Updated: 2023/03/30 17:32:09 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Adds the element ’new’ at the end of the list.
**	#1. The address of a pointer to the first link of a list.
**	#2. The address of a pointer to the element to be added to the list.
*/

void	ft_laddb(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (*lst)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
		*lst = new;
}
