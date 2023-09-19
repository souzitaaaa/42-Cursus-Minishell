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

void	insert_l_left(t_ast_node **leave, t_node *special)
{
	*leave = malloc(sizeof(t_ast_node));
	(*leave)->token = special->prev->token;
	(*leave)->left = NULL;
	(*leave)->right = NULL;
	(*leave)->prev = NULL;
	(*leave)->index = 0;
	(*leave)->pid = 0;
}

void	insert_l_right(t_ast_node **leave, t_node *special)
{
	*leave = malloc(sizeof(t_ast_node));
	(*leave)->token = special->next->token;
	(*leave)->left = NULL;
	(*leave)->right = NULL;
	(*leave)->prev = NULL;
	(*leave)->index = 0;
	(*leave)->pid = 0;
}

void	insert_first_op(t_ast_node **op, t_node *special, t_ast_node *l_left, t_ast_node *l_right)
{
	*op = malloc(sizeof(t_ast_node));
	(*op)->token = special->token;
	(*op)->left = l_left;
	(*op)->right = l_right;
	(*op)->prev = NULL;
	(*op)->index = 0;
	(*op)->pid = 0;
}

void	insert_op(t_ast_node **op, t_node *special, t_ast_node **l_left, t_ast_node *l_right)
{
	*op = malloc(sizeof(t_ast_node));
	(*op)->token = special->token;
	(*op)->left = *l_left;
	(*op)->right = l_right;
	(*op)->prev = NULL;
	(*op)->pid = 0;
	(*l_left)->prev = *op;
}

t_ast_node	*insert_first_ast(t_node *special)
{
	t_ast_node	*op;
	t_ast_node	*l_left;
	t_ast_node	*l_right;

	insert_l_left(&l_left, special);
	insert_l_right(&l_right, special);
	insert_first_op(&op, special, l_left, l_right);
	return(op);
}

t_ast_node *insert_ast(t_node *special, t_ast_node *l_left, int size)
{
	t_ast_node	*op;
	t_ast_node	*l_right;

	insert_l_right(&l_right, special);
	insert_op(&op, special, &l_left, l_right);
	op->index = size;
	return(op);
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
		printf("\033[1;34mtype:\033[0m %c\n", aux->left->token.type);
		print_arr(aux->left->token.arr);
		printf("\033[1;34mnnode right:\033[0m \n");
		printf("\033[1;34mtype:\033[0m %c\n", aux->right->token.type);
		print_arr(aux->right->token.arr);
		aux = aux->left;
	}
}

void	create_ast(t_lexer tokens, t_ast *ast)
{
	t_node	*aux_token;
	t_ast_node	*last_op;


	aux_token = tokens.head;
	while(ast->counter++ < tokens.size)
	{
		while(!special_chr(aux_token->token.type) && ast->counter++ < tokens.size)
			aux_token = aux_token->next;
		if(special_chr(aux_token->token.type))
		{
			if(ast->size == 0)
			{
				//printf("token: %s\n", aux_token->token.arr[0]);
				last_op = insert_first_ast(aux_token);
			}
			else
				last_op = insert_ast(aux_token, last_op, ast->size);
			ast->size++;
		}
		aux_token = aux_token->next;
	}
	ast->head = last_op;
}

void	test_ast(t_lexer tokens, t_ast *ast)
{
	create_ast(tokens, ast);
	//print_ast(*ast);
}
