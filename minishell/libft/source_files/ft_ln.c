/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ln.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:24:02 by yhaidar           #+#    #+#             */
/*   Updated: 2023/03/30 17:31:42 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Allocates (with malloc(3)) and returns a new element.The variable ’content’
**	is initialized with the value of the parameter ’content’. The variable
**	’next’ is initialized to NULL.
**	is used to create a new linked list element of type t_list 
**	with the provided content.
*/

t_list	*ft_ln(void *content)
{
	t_list	*new_element;

	new_element = (t_list *)malloc(sizeof(t_list) * 1);
	if (new_element)
	{
		new_element->content = content;
		new_element->next = NULL;
	}
	return (new_element);
}
