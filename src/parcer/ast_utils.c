
#include "../../includes/minishell.h"

//*Encontra o comando à esquerda do pipe
//*Recebe o node à esquerda do pipe
//*Anda para o nó anterior até encontrar o comando
//*Quando encontra o comando, devolve o token correspendente
//*Se não existir comando, cria e devolve um token de tipo EMPTY
t_token	find_cmd_left(t_node *aux)
{
	t_token token;

	while(1)
	{
		if(aux->token.type == STRING)
			return (aux->token);
		if(aux->index == 0)
			break ;
		aux = aux->prev;
	}
	token.arr = NULL;
	token.quotes = 0;
	token.type = EMPTY;
	return(token);
}

//*Esta função cria e insere a leave à esquerda do operator (pipe)
//*Recebe a leave (tipo ast_node que vai conter o comando à esquerda do pipe)
//*Recebe o pipe
//*Alloca memória para a leave
//*Atribui o token do cmd à esquerda do pipe ao token da leave
void	insert_l_left(t_leave **leave, t_node *pipe)
{
	t_lexer	list_in;
	t_lexer list_out;

	printf("chega aqui 5\n");
	*leave = malloc(sizeof(t_leave));
	(*leave)->token = find_cmd_left(pipe->prev);
	printf("chega aqui 6\n");
	left_create_list_in(&list_in, pipe->prev);
	printf("head: %p\n", list_in.head);
	printf("chega aqui 7\n");
	left_create_list_out(&list_out, pipe->prev);
	(*leave)->left = list_in.head;
	//printf("head: %p\n", (*leave)->left->head);
	(*leave)->right = list_out.head;
	(*leave)->prev = NULL;
	(*leave)->pid = 0;
}

//*Encontra o comando à direita do pipe
//*Recebe o node à direita do pipe
//*Anda para o próximo nó até encontrar o comando ou até emcontrar o próximo pipe
//*Quando encontra o comando, devolve o token correspendente
//*Se não existir comando, cria e devolve um token de tipo EMPTY
t_token	find_cmd_right(t_node *aux, t_lexer tokens)
{
	t_token token;
	while(aux->token.type != PIPE && aux != tokens.head)
	{
		if(aux->token.type == STRING)
			return (aux->token);
		aux = aux->next;
	}
	token.arr = NULL;
	token.quotes = 0;
	token.type = EMPTY;
	return(token);
}

void	insert_l_right(t_leave **leave, t_node *pipe, t_lexer tokens)
{
	t_lexer	list_in;
	t_lexer list_out;

	printf("chega aqui 4\n");
	*leave = malloc(sizeof(t_leave));
	(*leave)->token = find_cmd_right(pipe->next, tokens);
	printf("chega aqui 10\n");
	right_create_list_in(&list_in, pipe->next, tokens);
	printf("chega aqui 11\n");
	printf("pipe next: %s\n", pipe->next->token.arr[0]);
	right_create_list_out(&list_out, pipe->next, tokens);
	(*leave)->left = list_in.head;
	(*leave)->right = list_out.head;
	(*leave)->prev = NULL;
	(*leave)->pid = 0;
}
