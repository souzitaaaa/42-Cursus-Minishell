/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:05:27 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/19 20:56:21 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

insert_l_left(t_ast_node *leave, t_node *special)
{
	leave = malloc(sizeof(t_ast_node));
	leave->token = special->prev->token;
	leave->left = NULL;
	leave->right = NULL;
}

insert_l_right(t_ast_node *leave, t_node *special)
{
	leave = malloc(sizeof(t_ast_node));
	leave->token = special->next->token;
	leave->left = NULL;
	leave->right = NULL;
}

insert_first_op(t_ast_node *op, t_node *special, t_ast_node *l_left, t_ast_node *l_right)
{
	op->token = special->token;
	op->left = l_left;
	op->right = l_right;
	l_left->prev = op;
}

insert_op(t_ast_node *op, t_node *special, t_ast_node *l_left, t_ast_node *l_right)
{
	op->token = special->token;
	op->left = l_left;
	op->right = l_right;
}

insert_first_ast(t_node *special)
{
	t_ast_node	*op;
	t_ast_node	*l_left;
	t_ast_node	*l_right;

	insert_l_left(l_left, special);
	insert_l_right(l_right, special);
	insert_first_op(op, special, l_left, l_right);
}

insert_ast(t_node *special, t_ast_node l_left)
{
	t_ast_node	*op;
	t_ast_node	*l_right;

	insert_l_right(l_right, special);
	insert_op(op, special, l_left, l_right);
}

t_ast	create_ast(t_lexer tokens)
{
	t_ast	imput_exec;
	t_node	*aux_token;
	t_node	*last_op;

	init_ast(&imput_exec);
	aux_token = tokens.head;
	while(imput_exec.counter < tokens.size)
	{
		//imput_exec.counter = 0;
		while(!special_chr(aux_token->token.type) && imput_exec.counter++ < tokens.size)
		{
			imput_exec.size++;
			aux_token->next;
		}
		if(special_chr(aux_token->token.type)) //!initil
		{
			if(imput_exec.size == 1)
				insert_first_ast(aux_token);
			else
				insert_ast(aux_token, last_op);
		}
		last_op = aux_token;
		aux_token->next;
	}
	return(imput_exec);
}
