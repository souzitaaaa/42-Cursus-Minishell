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

# include "defines.h"
# include "minishell.h"
# include <stdbool.h>

/*
typedef struct s_main
{
	char 			*input_prompt;
	char			**env_arr;
	int				exit_code;
	t_lexer			tokens;
	t_env			env_list;
	t_quotes		quotes;
	t_ast 			input_exec;
	t_std			fd;
	t_prompt		prompt_list;
	t_bool          flags;
}t_main;*/

typedef struct s_bool
{
	bool            put_node_behind;
	bool            rdr_treated;
	bool            rdr_err;
	bool			signal;
} t_bool;

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
TOKENS
*/
//* Enum struct para ajudar na procura dos tokens
typedef enum s_type
{
	PIPE = '|',      // |
	IN = '<',        // <
	HEREDOC = 'H',   // <<
	OUT = '>',       // >
	APPEND = 'A',    // >>
	COMERCIAL = '&', // & //!APAGAR
	STRING = 'S',    // string (pode ser comando, ficheiro)
}t_type;

//* Estrutura que define os tokens, metendo na array o tokem em si e afirmando o tipo dele
typedef struct s_token
{
	char			**arr; //se o tipo for um careter especial o array pode ser NULL?
	t_type			type;
	bool			quotes;
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
AST
*/
//* Nodes da lista da ast, onde vai conter os tokens pela ordem de execução
typedef struct s_ast_node
{
	struct s_ast_node	*left;
	t_token				token;
	struct s_ast_node	*right;
	struct s_ast_node	*prev;
	int					pid;
	int					index; //*index dos nodes/pipes: o index esta ao contrario da arvore, a favor da ordem de execução
}
t_ast_node;

//* Struct inicial do t_ast (abstract syntax tree)
typedef	struct s_ast
{
	t_ast_node			*head;
	int					counter;
	int					size; //number of pipes/nodes
}
t_ast;

/*
QUOTES STRUCT
*/

//*Estrutura para ajudar o tratamento de quotes no lexer
typedef struct s_quotes
{
	int				type;
    int				start;
    int				end;
    int				error;
}t_quotes;

//* estrutura que guarda uma copia dos file descriptor para imput (stdin), output (stdout), error (stderr)
//--> quando se manda msg de erro deve sempre escrever-se para o stderr
//--> para usar nas redirecoes
//!APAGAR
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
	t_lexer			tokens;
	t_env			export_list;
	t_env			env_list;
	t_quotes		quotes;
	t_ast 			ast;
	t_std			fd;
	t_prompt		prompt_list;
	t_bool          flags;
}t_main;

#endif
