/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-da <jcruz-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:40:15 by jcruz-da          #+#    #+#             */
/*   Updated: 2023/10/23 19:51:51 by jcruz-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int cont_word(char *str)
{
    int i = 0;
    int word = 0;

    while (str[i])
    {
        while (str[i] <= 32 && str[i] != '\0') 
            i++;

        if (str[i] == '\0')
            break;

        while (str[i] > 32 && str[i] < 127)
            i++;
        word++;
    }
    return (word);
}

char **ft_split_tab(char *str)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int l = cont_word(str);
    
    //criar variavel que vai guardar as palavras como vetor de vetor
    char **split = malloc(sizeof(char *) * (l + 1)); //malloc para a quantidade de palavras, vetor de vetor
    if(!split)//segurança do malloc
        return (0);
    while (str[i])
    {
        j = 0;
        while (str[i] <= 32 && str[i] != '\0')  //pular os espaços do inicio das palavras 
            i++;

        if (str[i] == '\0') //segurança para parar quando encontrar um '\0'
            break;
        while (str[i] > 32 && str[i] < 127) //Quando encontrar caracteres imprimiveis andar com i e j
        {
            i++;
            j++;
        }
        split[k] = malloc(sizeof(char) * (j + i)); //guardar o espaço de cada palavra na posição split[k]
        i = i - j;//
        j = 0;//zerar j

        while (str[i] > 32 && str[i] < 127) //Escrever dentro do espaço mallocado
        {
            split[k][j] = str[i];
            j++; 
            i++; 
        }
        split[k][j] = '\0'; //inserir /0 no final de cada vetor preenchido com uma palavra
        k++; //ir para o proximo vetor
    }
	split[k] = NULL;
    return (split);//retornar o vetor de vetor
}