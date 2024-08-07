/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:38:35 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/22 14:12:29 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_tkn(t_cmd_list *list, t_exec *data, char *tkn)
{
	char	*path;

	path = find_cmd_path(list, data, tkn);
	if (path && list->is_cmd)
	{
		list->cmd_found = TRUE;
		return (path);
	}
	else
	{
		if (path)
			free(path);
		path = NULL;
		return (ft_strdup(tkn));
	}
}

t_cmd_list	*create_node(t_exec *data, char *tkn, int tkn_value)
{
	t_cmd_list	*new;

	new = (t_cmd_list *)ft_calloc(1, sizeof(t_cmd_list));
	if (tkn_value == PIPE)
		new->pipe = TRUE;
	else if (tkn_value == CMD)
		new->is_cmd = TRUE;
	else if (tkn_value == ARG)
		new->arg = TRUE;
	else if (tkn_value == OUT || tkn_value == APPEND)
		new->redir_out = TRUE;
	new->index = 0;
	malloc_error_ptr(new, "malloc : create_node");
	new->elem = extract_tkn(new, data, tkn);
	new->next = NULL;
	return (new);
}

void	link_new_node(t_cmd_list **lst, t_cmd_list *new)
{
	t_cmd_list	*temp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

t_cmd_list	*set_cmd_list(t_exec *data, char **tkn, int *tkn_value)
{
	t_cmd_list	*list;
	t_cmd_list	*new_node;
	int			i;

	i = -1;
	list = NULL;
	while (tkn[++i])
	{
		new_node = create_node(data, tkn[i], tkn_value[i]);
		link_new_node(&list, new_node);
	}
	return (list);
}
