/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:03:41 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/16 15:37:56 by joe              ###   ########.fr       */
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
typedef struct s_token
{
	char			**token; //se o tipo for um careter especial o array pode ser NULL?
	t_type			type;
}
t_token;

typedef struct s_node
{
	struct s_node	*prev;
	//char			**token;
	//t_type			type;
	t_token			token;
	int				index;
	struct s_node	*next;
	int				quotes;
}t_node;

typedef struct s_list
{
	t_node          *head;
	int				size;
	int             str_len;
}t_list;

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
