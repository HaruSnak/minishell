
#include "../../includes/minishell.h"

char	*extract_tkn(t_cmd_list *list, t_exec *data, char *tkn)
{
	char *path;

	// set the bultins flag, strcmp tkn
	path = find_cmd_path(list, data, tkn);
	if (path)
		return (path);
	else
		return (tkn);
}

t_cmd_list	*create_node(t_exec *data, char *tkn, int tkn_value)
{
	t_cmd_list	*new;

	new = malloc(sizeof(t_cmd_list));
	if (!new)
		malloc_error();
	new->builtin = FALSE;
	new->elem = extract_tkn(new, data, tkn);
	new->index = 0;
	new->pipe = FALSE;
	new->cmd = FALSE;
	new->arg = FALSE;
	if (tkn_value == PIPE)
		new->pipe = TRUE;
	else if (tkn_value == CMD)
		new->cmd = TRUE;
	else if (tkn_value == ARG)
		new->arg = TRUE;
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
	t_cmd_list	*cmd;
	t_cmd_list	*new_node;
	int			i;

	i = -1;
	cmd = NULL;
	while (tkn[++i])
	{
		new_node = create_node(data, tkn[i], tkn_value[i]);
		link_new_node(&cmd, new_node);
	}
	return (cmd);
}
