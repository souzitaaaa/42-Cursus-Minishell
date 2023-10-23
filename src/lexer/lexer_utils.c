/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:03:48 by dinoguei          #+#    #+#             */
/*   Updated: 2023/10/18 16:03:48 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//* Remove nodes num index especifico
void	remove_node(t_lexer *lexer, int index, bool ft_free)
{
	t_node	*current;
	int		count;

	current = lexer->head;
	count = 0;
	if (lexer->size == 1)
		lexer->head = NULL;
	else
	{
		while (count++ < index)
			current = current->next;
		current->next->prev = current->prev;
		current->prev->next = current->next;
		if (index == 0)
			lexer->head = current->next;
		shift_index(lexer);
	}
	lexer->size--;
	if(ft_free)
		ft_free_array(&current->token.arr);
	else
		free(current->token.arr);
	free(current);
}

//* Insere nodes num index especifico
void	insert_node(t_lexer *lexer, t_node *new, int index)
{
	t_node	*current;
	int		count;

	count = 0;
	current = lexer->head;
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

/*
void    print_tokens(t_lexer *tokens)
{
	int count = 0;
	t_node  *aux = tokens->head;

				printf("\033[1;32m\t\t(Printing tokens)\033[0m\n");
	while (count++ < tokens->size)
	{
		printf("\033[1;34m[INDEX] \033[0m %i\n", aux->index);
		printf("\033[1;34m[TYPE]  \033[0m %c\n", aux->token.type);
		printf("\033[1;34m[ARR] \033[0m \n");
		print_arr(aux->token.arr);
		printf("\033[1;34m[QUOTES HEREDOC]  \033[0m %i\n\n", aux->token.quotes);
		aux = aux->next;
	}
			printf("\033[1;32m\t\t(End printing tokens)\033[0m\n");
}
*/

//* Vai devolver o node do respetivo index em que queremos trabalhar
t_node	*get_node(t_lexer tokens, int index_wanted)
{
	int		count;
	t_node	*aux;

	count = 0;
	aux = tokens.head;
	while (count++ < tokens.size)
	{
		if (aux->index == index_wanted)
			return (aux);
		aux = aux->next;
	}
	return (NULL);
}

//* Funcao de ajuda para a search_extra_tokens para verificar se encontrou
//*  um caracter delimitador de token
bool	special_chr(char c)
{
	if (ft_strchr("|<>", c))
		return (true);
	return (false);
}
