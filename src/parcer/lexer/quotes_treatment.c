/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_treatment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:18:03 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/25 16:18:03 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    single_quotes(t_main *main, int *i, int start)
{
    char    *str;
    char    *out;
            printf("\033[1;35m\t(Single quotes treatment)\033[0m\n");
        printf("Start on the str: %c\n", main->input_prompt[main->quotes.start]);
        printf("End on the str: %c\n", main->input_prompt[main->quotes.end]);
        
    out = ft_substr(main->input_prompt, start, (main->quotes.start - start));
    str = ft_substr(main->input_prompt, main->quotes.start + 1, (main->quotes.end - main->quotes.start) - 1);
        printf("str: %s\n", str);
    out = ft_strjoin(out, str);
        printf("out: %s\n", out);
    add_token(main, STRING, i, out);
    (*i) = main->quotes.end;
            printf("\033[1;35m\t(End single quotes treatment)\033[0m\n");
}

void    double_quotes(t_main *main, int *i, int start)
{
    char    *str;
    char    *out;
    int     j = 0;
            printf("\033[1;35m\t(Double quotes treatment)\033[0m\n");
        printf("Start on the str: %c\n", main->input_prompt[main->quotes.start]);
        printf("End on the str: %c\n", main->input_prompt[main->quotes.end]);
    out = ft_substr(main->input_prompt, start, (main->quotes.start - start));
    str = ft_substr(main->input_prompt, main->quotes.start + 1, (main->quotes.end - main->quotes.start) - 1);
    while (str[j] != '\0')
    {
        if (ft_strchr("$", str[j]))
        {
            str = expand(main, str);
            break ;
        }
        j++;
    }
        printf("str: %s\n", str);
    out = ft_strjoin(out, str);
        printf("out: %s\n", out);
    add_token(main, STRING, i, out);
    (*i) = main->quotes.end;    
        
        printf("\033[1;35m\t(End double quotes treatment)\033[0m\n");
}

void    quotes_treatment(t_main *main, int *i, int start)
{
            printf("\033[1;35m\t\t(Quotes treatment)\033[0m\n");
        printf("Type: %c\n", (char)main->quotes.type);
        printf("Type: %i\n", main->quotes.start);
        printf("Type: %i\n", main->quotes.end);
        if (main->quotes.start == (*i) && main->quotes.type == '\'')
            single_quotes(main, i, start);
        else
            double_quotes(main, i, start);
        
        printf("\033[1;35m\t\t(End quotes treatment)\033[0m\n");
}