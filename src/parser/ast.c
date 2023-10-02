/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:05:27 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/24 15:31:40 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	insert_first_op(t_ast_node **op, t_node *pipe, t_leaf *l_left, t_leaf *l_right)
{
	*op = malloc(sizeof(t_ast_node));
	(*op)->token = pipe->token;
	(*op)->left = l_left;
	(*op)->right = l_right;
	(*op)->prev = NULL;
	(*op)->left_n = NULL;
	(*op)->index = 0;
}

void	insert_op(t_ast_node **op, t_node *pipe, t_ast_node **last_op, t_leaf *l_right)
{
	*op = malloc(sizeof(t_ast_node));
	(*op)->token = pipe->token;
	(*op)->left_n = *last_op;
	(*op)->left = NULL;
	(*op)->right = l_right;
	(*op)->prev = NULL;
	(*last_op)->prev = *op;
}

t_ast_node	*insert_first_ast(t_node *pipe, t_lexer tokens)
{
	t_ast_node	*op;
	t_leaf		*l_left;
	t_leaf		*l_right;

	insert_l_left(&l_left, pipe);
	insert_l_right(&l_right, pipe, tokens);
	insert_first_op(&op, pipe, l_left, l_right);
	return(op);
}

t_ast_node *insert_ast(t_node *pipe, t_ast_node *last_op, int size, t_lexer tokens)
{
	t_ast_node	*op;
	t_leaf		*l_right;

	insert_l_right(&l_right, pipe, tokens);
	insert_op(&op, pipe, &last_op, l_right);
	op->index = size;
	return(op);
}

void	create_ast(t_lexer tokens, t_ast *ast)
{
	t_node		*aux;
	t_ast_node	*last_op;


	aux = tokens.head;
	while(ast->counter++ < tokens.size)
	{
		printf("chega aqui 3\n");
		while(aux->token.type != PIPE && ast->counter++ < tokens.size) //encontro o pipe
			aux = aux->next;
		printf("chega aqui\n");
		if(aux->token.type == PIPE)
		{
			if(ast->size == 0)
			{
				printf("chega aqui 1\n");
				//printf("token: %s\n", aux->token.arr[0]);
				last_op = insert_first_ast(aux, tokens);
			}
			else
				last_op = insert_ast(aux, last_op, ast->size, tokens);
			ast->size++;
		}
		aux = aux->next;
	}
	ast->head = last_op;
}

void    print_ast(t_ast	ast)
{
	int	count = 0;
	t_ast_node  *aux = ast.head;

	printf("\033[1;32m\t\tPrinting AST\033[0m\n");
	printf("size: %d\n", ast.size);
	while (count++ < ast.size)
	{
		printf("\033[1;34mindex:\033[0m %i\n", aux->index);
		printf("\033[1;34mtype:\033[0m %c\n", aux->token.type);
		printf("\033[1;34mnode left:\033[0m \n");
		if(aux->left)
			printf("\033[1;34mtype:\033[0m %c\n", aux->left->token.type);
		else
			printf("\033[1;34mtype:\033[0m %c\n", aux->left_n->token.type);
		if(aux->left)
		{
			if(aux->left->token.arr)
				print_arr(aux->left->token.arr);
			if (aux->left->left)
			{
				printf("\033[1;34mrdr in:\033[0m \n");
				print_list_endnull(aux->left->left);
			}
			if (aux->left->right)
			{
				printf("\033[1;34mrdr out:\033[0m \n");
				print_list_endnull(aux->left->right);
			}
		}
		else
		{
			if(aux->left_n->token.arr)
				print_arr(aux->left_n->token.arr);
		}
		printf("\033[1;34mnode right:\033[0m \n");
		printf("\033[1;34mtype:\033[0m %c\n", aux->right->token.type);
		if(aux->right->token.arr)
			print_arr(aux->right->token.arr);
		if (aux->right->left)
		{
			printf("\033[1;34mrdr in:\033[0m \n");
			print_list_endnull(aux->right->left);
		}
		if (aux->right->right)
		{
			printf("\033[1;34mrdr out:\033[0m \n");
			print_list_endnull(aux->right->right);
		}
		if(aux->left_n)
			aux = aux->left_n;
	}
}
