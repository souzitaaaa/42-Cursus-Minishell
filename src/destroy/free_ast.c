/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:20:42 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/25 08:01:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*Liberta o último ast_node(pipe) da lista 
//(primeiro da ordem de execucao)
void	free_last_node(t_ast_node *aux)
{
	free_list(&aux->right->left);
	free_list(&aux->right->right);
	free_list(&aux->left->left);
	free_list(&aux->left->right);
	free(aux->right);
	free(aux->left);
	free(aux);
}

void	free_ast(t_ast	*ast)
{
	t_ast_node	*aux;
	t_ast_node	*temp;

	ast->counter = 0;
	if (ast->head == NULL)
		return ;
	aux = ast->head;
	while (ast->counter++ < ast->size)
	{
		if (aux->left)
			free_last_node(aux);
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
