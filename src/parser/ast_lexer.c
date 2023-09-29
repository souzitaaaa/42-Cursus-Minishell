#include "../../includes/minishell.h"

t_node	*node_dup(t_node *src)
{
	t_node	*dst;

	dst = malloc(sizeof(t_node));
	if (!dst)
		return (NULL);
	dst->token.type = src->token.type;
	dst->token.arr = ft_arrdup(src->token.arr);
	dst->token.quotes = src->token.quotes;
	return (dst);
}

void	init_list_ast(t_lexer *list)
{
	list->head = NULL;
	list->size = 0;
	list->str_len = 0;
}

void	left_create_list_in(t_lexer *list_in, t_node *aux)
{
	t_node	*new_node;

	init_list_ast(list_in);
	while(1)
	{
		if(aux->token.type == IN || aux->token.type == HEREDOC)
		{
			new_node = node_dup(aux);
			insert_head_endnull(list_in, new_node);
		}
		if(aux->index == 0)
			break ;
		aux = aux->prev;
	}
	if (list_in->head != NULL)
		shift_index_endnull(list_in);
}

void	left_create_list_out(t_lexer *list_out, t_node *aux)
{
	t_node	*new_node;

	init_list_ast(list_out);
	while(1)
	{
		if(aux->token.type == OUT || aux->token.type == APPEND)
		{
			new_node = node_dup(aux);
			insert_head_endnull(list_out, new_node);
		}
		if(aux->index == 0)
			break ;
		aux = aux->prev;
	}
	if (list_out->head != NULL)
		shift_index_endnull(list_out);
}

void	right_create_list_in(t_lexer *list_in, t_node *aux, t_lexer tokens)
{
	int counter;
	t_node	*new_node;

	init_list_ast(list_in);
	counter = 0;
	while(aux->token.type != PIPE && aux != tokens.head)
	{
		if(aux->token.type == IN || aux->token.type == HEREDOC)
		{
			new_node = node_dup(aux);
			insert_last_endnull(list_in, new_node, counter);
			counter++;
		}
		aux = aux->next;
	}
}

void	right_create_list_out(t_lexer *list_out, t_node *aux, t_lexer tokens)
{
	int		counter;
	t_node	*new_node;

	init_list_ast(list_out);
	counter = 0;
	//printf("%p, %c, %s\n", aux, aux->token.type, aux->token.arr[0]);
	printf("%p, %c, %s\n", tokens.head, tokens.head->token.type, tokens.head->token.arr[0]);
	while(aux->token.type != PIPE && aux != tokens.head)
	{
		//printf("%p, %c, %s\n", aux, aux->token.type, aux->token.arr[0]);
		if(aux->token.type == OUT || aux->token.type == APPEND)
		{
			new_node = node_dup(aux);
			insert_last_endnull(list_out, new_node, counter);
			counter++;
		}
		aux = aux->next;
	}
}
