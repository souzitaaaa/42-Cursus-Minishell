/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 23:01:58 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/23 23:01:58 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//*Encontra o comando à esquerda do pipe
//*Recebe o node à esquerda do pipe
//*Anda para o nó anterior até encontrar o comando
//*Quando encontra o comando, devolve o token correspendente
//*Se não existir comando, cria e devolve um token de tipo EMPTY
t_token	find_cmd_left(t_node *aux)
{
	t_token	token;

	while (1)
	{
		if (aux->token.type == STRING)
			return (aux->token);
		if (aux->index == 0)
			break ;
		aux = aux->prev;
	}
	token.arr = NULL;
	token.quotes = 0;
	token.type = EMPTY;
	return (token);
}

//*Esta função cria e insere a leaf à esquerda do operator (pipe)
//*Recebe a leaf (tipo ast_node que vai conter o comando à esquerda do pipe)
//*Recebe o pipe
//*Alloca memória para a leaf
//*Atribui o token do cmd à esquerda do pipe ao token da leaf
void	insert_l_left(t_leaf **leaf, t_node *pipe)
{
	t_lexer	list_in;
	t_lexer	list_out;

	*leaf = malloc(sizeof(t_leaf));
	(*leaf)->token = find_cmd_left(pipe->prev);
	left_create_list_in(&list_in, pipe->prev);
	left_create_list_out(&list_out, pipe->prev);
	(*leaf)->left = list_in.head;
	(*leaf)->right = list_out.head;
	(*leaf)->prev = NULL;
	(*leaf)->pid = 0;
	(*leaf)->hd.fd = 0;
	(*leaf)->hd.flag = false;
	(*leaf)->hd.index = 0;
}

//*Encontra o comando à direita do pipe
//*Recebe o node à direita do pipe
//*Anda para o próximo nó até encontrar o comando
//ou até encontrar o próximo pipe
//*Quando encontra o comando, devolve o token correspendente
//*Se não existir comando, cria e devolve um token de tipo EMPTY
t_token	find_cmd_right(t_node *aux, t_lexer tokens)
{
	t_token	token;

	while (aux->token.type != PIPE && aux != tokens.head)
	{
		if (aux->token.type == STRING)
			return (aux->token);
		aux = aux->next;
	}
	token.arr = NULL;
	token.quotes = 0;
	token.type = EMPTY;
	return (token);
}

void	insert_l_right(t_leaf **leaf, t_node *pipe, t_lexer tokens)
{
	t_lexer	list_in;
	t_lexer	list_out;

	*leaf = malloc(sizeof(t_leaf));
	(*leaf)->token = find_cmd_right(pipe->next, tokens);
	right_create_list_in(&list_in, pipe->next, tokens);
	right_create_list_out(&list_out, pipe->next, tokens);
	(*leaf)->left = list_in.head;
	(*leaf)->right = list_out.head;
	(*leaf)->prev = NULL;
	(*leaf)->pid = 0;
	(*leaf)->hd.fd = 0;
	(*leaf)->hd.flag = false;
	(*leaf)->hd.index = 0;
}
