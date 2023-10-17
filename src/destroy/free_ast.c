/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:20:42 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/17 15:21:41 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    free_ast(t_ast	*ast)
{
	int	count = 0;
	t_ast_node  *aux;
	t_ast_node	*temp;

	if (ast->head == NULL)
		return ;
	aux = ast->head;
	while (count++ < ast->size)
	{
		if(aux->left) //*Ultimo ast_node/pipe da lista (primeiro da ordem de execucao)
		{
			free_list(&aux->right->left);
			free_list(&aux->right->right);
			free_list(&aux->left->left);
			free_list(&aux->left->right);
			free(aux->right);
			free(aux->left);
		}
		else
		{
			free_list(&aux->right->left);
			free_list(&aux->right->right);
			free(aux->right);
			temp = aux;
			aux = aux->left_n;
			free(temp);
		}
	}
}
