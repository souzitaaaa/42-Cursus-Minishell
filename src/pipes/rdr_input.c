/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:47:38 by rimarque          #+#    #+#             */
/*   Updated: 2023/09/29 18:24:42 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//i_hd -> index do ultimo hd
void	ft_redirect_in(t_node	*head, t_main *main)
{
	t_node *aux;
	int	counter;

	aux = head;
	counter = 0;
	while(aux != NULL)
	{
		if(aux->token.type == HEREDOC && aux->index != main->hd.index)
			aux = aux->next;
		exec_rdr(aux->token, main);
		aux = aux->next;
		counter++;
	}
}

void	exec_hd_p(t_node *head, t_main *main)
{
	t_node *aux;
	bool hd;

	hd = false;
	aux = head;
	while(aux != NULL)
	{
		if(aux->token.type == HEREDOC)
		{
			if(!hd)
				hd = true;
			else
				close(main->hd.fd);
			if(aux->token.arr[1] == NULL)
				main->hd.fd = open_hd(aux->token.arr[0], aux->token.quotes, main);
			else
				main->hd.fd = open_hd(aux->token.arr[1], aux->token.quotes, main);
			main->hd.index = aux->index;
		}
		aux = aux->next;
	}
}
