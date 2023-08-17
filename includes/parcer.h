/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:03:41 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/17 21:16:52 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCER_H
# define PARCER_H

# include "minishell.h"

typedef enum s_type
{
	PIPE = '|',     // |
	IN = '<',       // <
	HEREDOC = 'H',  // <<
	OUT = '>',      // >
	APPEND = 'A',   // >>
	STRING = 'S',   // string (pode ser comando, ficheiro)
}t_type;

/*
TOKENS
*/

//* Estrutura que define os tokens, metendo na array o tokem em si e afirmando o tipo dele
typedef struct s_token
{
	char			**arr; //se o tipo for um careter especial o array pode ser NULL?
	t_type			type;
}
t_token;

//* Estes sao os nodes da lista, neles temos ligacoes para o anterior e proximo
	//* e tambem uma ligacao a outra estrutura junto com mais algumas informacoes
typedef struct s_node
{
	struct s_node	*prev;
	t_token			token;
	int				index;
	int				quotes;
	struct s_node	*next;
}t_node;

//* Esta e a struct inicial do t_lexer, ela aponta para o node head (1 node)
typedef struct s_lexer
{
	t_node			*head;
	int				size;
	int				str_len;
}t_lexer;

/*
AST
*/
typedef struct s_ast_node
{
	struct s_ast_node	*left;
	t_token				token;
	struct s_ast_node	*right;
}
t_ast_node;

typedef	struct s_ast
{
	t_ast_node			*head;
	int					counter;
}
t_ast;

#endif
