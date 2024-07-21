/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:54:29 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/21 16:54:43 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_data(t_exec *data)
{
	if (data->redir_ptr->here_doc)
		ft_delete_file_heredoc();
	if (data->outfile)
		free(data->outfile);
}

// Free a double pointer and set it to NULL
void	ft_free_d_ptr(void ***ptr)
{
	int	i;
	int	count;

	i = 0;
	count = ft_count_index((char **)*ptr);
	while (i < count)
	{
		free((*ptr)[i]);
		(*ptr)[i] = NULL;
		i++;
	}
	free(*ptr);
	*ptr = NULL;
	return ;
}

// verify_operations function commands free
void	ft_end_verify(t_parsing *parsing)
{
	ft_free_d_ptr((void ***)&parsing->tkn);
	free(parsing->tkn_value);
	parsing->tkn_value = NULL;
}

void	ft_free_and_compact(char **str, int index, int size)
{
	int	i;

	i = index;
	free(str[index]);
	while (i < size - 1)
	{
		str[i] = str[i + 1];
		i++;
	}
	str[size - 1] = NULL;
}
