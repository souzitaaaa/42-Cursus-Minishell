/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:20:42 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/19 23:57:48 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*Ultimo ast_node/pipe da lista (primeiro da ordem de execucao)
void	free_ast(t_ast	*ast)
{
	int			count;
	t_ast_node	*aux;
	t_ast_node	*temp;

	count = 0;
	if (ast->head == NULL)
		return ;
	aux = ast->head;
	while (count++ < ast->size)
	{
		if (aux->left)
		{
			free_list(&aux->right->left);
			free_list(&aux->right->right);
			free_list(&aux->left->left);
			free_list(&aux->left->right);
			free(aux->right);
			free(aux->left);
			free(aux);
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
