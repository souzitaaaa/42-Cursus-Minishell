/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:55:40 by joe               #+#    #+#             */
/*   Updated: 2023/08/28 17:28:44 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

/*
!JOIN
*/
typedef struct s_join
{
	char	**before;
	char	*str;
	char	**after;
} t_join;

/*
!HD
*/
typedef struct s_hd
{
	bool		flag;
	int			fd;
	int			index;
	char		*str;
} t_hd;

/*
!BOOL
*/
typedef struct s_bool
{
	bool			put_node_behind; //!APAGAR
	bool			rdr_treated;
	bool			rdr_err;
	bool			signal;
	bool			not_print;
	bool			hd;
} t_bool;

/*
!ENV
*/
//* Cada node vai conter uma string com a variavel de ambiente
typedef struct s_var
{
    struct s_var    *prev;
    char            *var;
    int             index;
    struct s_var    *next;
} t_var;

//* Struct inicial da t_env
typedef struct s_env
{
    t_var   *head;
    int     size;
    int     i;
} t_env;

/*
!TOKENS
*/

typedef struct s_extra
{
	int		start;
	bool	fd;
	bool	run;
	bool	extra;
	int		n_len;
}t_extra;

//* Enum struct para ajudar na procura dos tokens
typedef enum s_type
{
	PIPE = '|',      // |
	IN = '<',        // <
	HEREDOC = 'H',   // <<
	OUT = '>',       // >
	APPEND = 'A',    // >>
	COMERCIAL = '&', // &
	STRING = 'S',    // Comando
	EMPTY = 'E',	 // Vazio
}t_type;

//* Estrutura que define os tokens, metendo na array o token em si e afirmando o tipo dele
typedef struct s_token
{
	char			**arr; //se o tipo for um careter especial o array pode ser NULL?
	t_type			type;
	bool			quotes;
}
t_token;

/*
!LEXER
*/

//* Estes sao os nodes da lista, neles temos ligacoes para o anterior e proximo
	//* e tambem uma ligacao a outra estrutura junto com mais algumas informacoes
typedef struct s_node
{
	struct s_node	*prev;
	t_token			token;
	int				index;
	int				quotes;
	struct s_node	*next;
	int				fd;
}t_node;

//* Esta e a struct inicial do t_lexer, ela aponta para o node head (1 node)
typedef struct s_lexer
{
	t_node			*head;
	int				size;
	int				str_len;
}t_lexer;


/*
!Abstract Syntaxt Tree (AST)
*/

typedef struct s_leaf		t_leaf;
typedef struct s_ast_node	t_ast_node;

//*Nodes da ast, onde vai conter os pipes
//Os t_ast_node prev aponta para o pipe seguinte (ordem de execucao)
//Os t_leave apontam para os comandos anterior (left) e seguinte (right) ao pipe
//Os t_ast_node left_n aponta para o pipe anterior (ordem de execucao)
//O index esta ao contrario da arvore, a favor da ordem de execução
typedef struct s_ast_node
{
	t_ast_node		*prev;
	t_token			token;
	t_leaf			*right;
	t_leaf			*left;
	t_ast_node		*left_n;
	int				index;
}
t_ast_node;

//*Leaves da lista da ast, onde vai conter os comandos
//Os t_node apontam para listas de rdr in (left) e rdr out(right)
typedef struct s_leaf
{
	t_ast_node			*prev;
	t_token				token;
	t_node				*left;
	t_node				*right;
	int					pid;
	t_hd				hd;
}
t_leaf;

//* Struct inicial do t_ast
//O size corresponde ao numero de de nodes/pipes
typedef	struct s_ast
{
	t_ast_node			*head;
	int					counter;
	int					size;
}
t_ast;

/*
!QUOTES STRUCT
*/

//* Estes sao os nodes da lista, neles temos ligacoes para o anterior e proximo
	//* e tambem uma ligacao a outra estrutura junto com mais algumas informacoes
typedef struct s_node_quotes
{
	struct s_node_quotes	*prev;
	int				index;
	int				type;
	int				start;
	int				end;
	struct s_node_quotes	*next;
}t_node_quotes;

typedef	struct s_quotes
{
	t_node_quotes			*head;
	int					counter;
	int					size;
}t_quotes;

//* Estrutura que guarda uma copia dos file descriptor
	//*para imput (stdin), output (stdout), error (stderr)
typedef struct s_std
{
	int	stdin;
	int	stdout;
	int	stderr;
}
t_std;

typedef struct s_prompt
{
	char	*out;
	char	*logname;
	char	*pwd;
}t_prompt;

typedef struct s_len
{
	int		pipe;
	int		in;
	int		out;
	int		squote;
	int		dquote;
}t_len;

/*
!MAIN STRUCT
*/
//*Struct principal do programa, vai ser a struct por onde vamos conseguir aceder a tudo
//* que seja informacao no nosso programa
typedef struct s_main
{
	char 			*input_prompt;
	char			**env_arr;
	char			*prev;
	int				exit_code;
	int				line;
	t_lexer			tokens;
	t_env			export_list;
	t_env			env_list;
	t_quotes		quotes;
	t_ast 			ast;
	t_std			fd;
	t_hd			hd;
	t_prompt		prompt_list;
	t_bool			flags;
}t_main;

#endif
