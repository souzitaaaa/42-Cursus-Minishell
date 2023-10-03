/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:35:09 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/01 18:36:45 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redirect_out(t_node	*head, t_main *main)
{
	t_node *aux;
	int	counter;

	aux = head;
	counter = 0;
	while(aux != NULL)
	{
		exec_rdr(aux->token, main, 0);
		aux = aux->next;
		counter++;
	}
}
