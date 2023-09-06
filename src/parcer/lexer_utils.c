#include "../../includes/minishell.h"

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
