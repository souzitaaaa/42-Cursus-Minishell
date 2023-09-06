/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:32:50 by rimarque          #+#    #+#             */
/*   Updated: 2023/09/06 18:19:16 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*O parcer organiza o imput para a execução
//*1º faz a analise sintatica e retorna caso a sintase esteja errada
//*2º caso a lista tenha apenas 1 elemento tipo STRING vai executar o comando, caso contrario segue para os passos seguintes
//*3º concatena todos os tipos strings no mesmo comando, até ao próximo pipe
//*4º verifica se existem pipes, nesse caso faz a arvore e depois a execuçao
//*5º caso nao hajam pipes, a execucao dos riderects é feita usando a lista

/*bool syntase()
{
	pipes seguidos, redirects seguidos, acabar em pipe ou riderect (o arr tem que ser NULL), começar em pipe, redirect e pipe por esta ordem, erro & (?)
}*/

//*Devolve verdadeiro se tiver pipes ou rdr e falso se nao tiver
/*bool	find_tk(t_lexer tokens)
{
	int counter;
	t_node *aux;

	counter = 0;
	aux = tokens.head;
	while(counter++ < tokens.size)
	{
		if(aux->token.type != STRING)
			return (true);
		aux = aux->next;
	}
	return (false);
}*/

bool	find_pipes(t_lexer tokens)
{
	int counter;
	t_node *aux;

	counter = 0;
	aux = tokens.head;
	while(counter++ < tokens.size)
	{
		if(aux->token.type == PIPE)
			return (true);
		aux = aux->next;
	}
	return (false);
}

int	find_first_cmd(t_node *aux, int size)
{
	int counter;

	counter = 0;
	while(counter++ < size)
	{
		if(aux->token.type == STRING)
			return (aux->index);
		aux = aux->next;
	}
	return (-1);
}

char	**copy_first_cmd(t_lexer tokens, int index)
{
	int	counter;
	t_node *aux;

	counter = 0;
	aux = tokens.head;
	while(counter++ < index)
		aux = aux->next;
	return (ft_arrdup(aux->token.arr));
}

t_node	*find_node(t_lexer tokens, int index)
{
	int	counter;
	t_node *aux;

	counter = 0;
	aux = tokens.head;
	while(counter++ < index)
		aux = aux->next;
	return (aux);
}

t_node *create_n_cmd(char **temp)
{
	t_node *new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->token.arr = ft_arrdup(temp);
	ft_free_array(&temp);
	new->token.type = STRING;
	return(new);
}

void	insert_temp(t_lexer *tokens, int index, char **temp)
{
	t_node *new;

	remove_node(tokens, index);
	new = create_n_cmd(temp);
	insert_node(tokens, new, index);
}

void	cmdpipecat(t_lexer *tokens, t_node *aux, int index)
{
	char **temp;

	temp = copy_first_cmd(*tokens, index);
	aux = aux->next;
	while(aux->token.type != PIPE && aux != tokens->head)
	{
		if(aux->token.type == STRING && aux->index != index)
		{
				temp = ft_arrjoin(temp, aux->token.arr); //!NAO TESTEI
				remove_node(tokens, aux->index);
				aux = find_node(*tokens, aux->index);
		}
		else
			aux = aux->next;
	}
	insert_temp(tokens, index, temp);
}

//*Esta função junta os tipos S todos no mesmo nó, para que entre pipes só haja um tipo S
void	cmdcat(t_lexer *tokens) //!TESTAR
{
	int	counter;
	t_node *aux;
	int	cmd_index;
	int	size;

	counter = 0;
	aux = tokens->head;
	size = tokens->size;
	while(counter < size)
	{
		cmd_index = find_first_cmd(aux, tokens->size); //*encontra o primeiro comando e devolve o seu index
		if(cmd_index == -1) //*Se não houver cmd, acaba aqui;
			return ;
		cmdpipecat(tokens, aux, cmd_index); //*concatenar os tipo S até ao próximo pipe ou até ao fim da lista
		while(aux->token.type != PIPE && counter++ < size)
			aux = aux->next;
		aux = aux->next;
	}
}

void	parcer(t_main *main)
{
	//if(!syntase())
		//	return ;
	if(main->tokens.size == 1 && main->tokens.head->token.type == STRING)
	{
		exec_cmd(main->tokens.head->token.arr, main, false);
	}
	//cmdcat(&main->tokens);
	else
	{
		if(find_pipes(main->tokens))
		{
			test_ast(main->tokens, &main->ast);
			init_exec_ast(main->ast, main);
		}
		else
		{
			init_rdr(main->tokens, main);
		}
	}
}
