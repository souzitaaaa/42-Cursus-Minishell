#include "../../../includes/minishell.h"

void    remove_node(t_lexer *lexer, int index)
{
	t_node   *current;

    int count = 0;
    current = lexer->head;
    if (lexer->size == 1)
		lexer->head = NULL;
    else
    {
        while (count++ < index)
        {
            current = current->next;
        }
            current->next->prev = current->prev;
            current->prev->next = current->next;
            if (index == 0)
                lexer->head = current->next;
            shift_index(lexer);
    }
    lexer->size--;
    free(current);
}

void    insert_node(t_lexer *lexer, t_node *new, int index)
{
    t_node   *current;

    current = lexer->head;
    int count = 0;
    if (lexer->head == NULL)
        put_head_node(lexer, new);
    else
    {
        while (count++ < index)
        {
            current = current->next;
        }
	    new->next = current;
		new->prev = current->prev;
		current->prev->next = new;
		current->prev = new;
		if (index == 0)
                lexer->head = new;
		shift_index(lexer);
    }
    lexer->size++;
}

//* Funcao para debug, podem reutiliza-la, so mandar a lista que pretenderem
	//* e os argumentos que querem imprimir
void    print_tokens(t_lexer *tokens)
{
	int count = 0;
	t_node  *aux = tokens->head;

				printf("\033[1;32m\t\t(Printing tokens)\033[0m\n");
	while (count++ < tokens->size)
	{
        printf("loop??\n");
		printf("\033[1;34m[INDEX] \033[0m %i\n", aux->index);
		printf("\033[1;34m[TYPE]  \033[0m %c\n", aux->token.type);
		printf("\033[1;34m[ARR] \033[0m \n");
		print_arr(aux->token.arr);
		printf("\033[1;34m[QUOTES HEREDOC]  \033[0m %i\n\n", aux->token.quotes);
		aux = aux->next;
	}
			printf("\033[1;32m\t\t(End printing tokens)\033[0m\n");
}

t_node	*find_node(t_lexer tokens, int index)
{
	int	counter;
	t_node *aux;

	counter = 0;
	aux = tokens.head;
	while(counter < index && counter < tokens.size)
    {
        aux = aux->next;
        counter++;
    }
	return (aux);
}
