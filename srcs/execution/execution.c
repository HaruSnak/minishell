
#include "../../includes/minishell.h"

void	parent_exec(t_exec **data)
{
	close((*data)->fds[1]);
	close((*data)->prevpipe);
	dup2((*data)->fds[0], (*data)->prevpipe);
	close((*data)->fds[0]);
}

void	command_found(t_exec **data, char **path, char **envp, int i)
{
	(*data)->pidz[i] = fork();
	check_err_fork((*data)->pidz[i]);
	if ((*data)->pidz[i] == 0)
		child_exec(envp, data, i, *path);
	else
		parent_exec(data);
	free(*path);
}

void	command_not_found(t_exec **data, int i)
{
	ft_printf("minishlag: %s: command not found\n",
		(*data)->parsing_ptr->tkn[i]);
	close((*data)->prevpipe);
	(*data)->prevpipe = dup((*data)->fds[0]);
	close((*data)->fds[1]);
	close((*data)->fds[0]);
}
/*
void	cmds_execution(t_exec **data, char **envp)
{
	char	**path;
	int		i;

	i = -1;
	while ((*data)->parsing_ptr->tkn[++i]
		&& (*data)->parsing_ptr->tkn_value[i] == 6)
	{
		path = find_cmd_path(&data, i);
		if (pipe((*data)->fds) == -1)
		{
			perror("pipe");
			exit(errno);
		}
		if (path == NULL)
			command_not_found(&data, i);
		else
			command_found(&data, &path, envp, i);
	}
}*/

void	execution(char *tkn[], char **envp, struct s_parsing *parsing)
{
	t_exec	*data;
	t_redir	*s_redir;

	(void)envp;
	init_data(&data, &s_redir, parsing);
	redirection(tkn, parsing->tkn_value, &data, &s_redir);
	
	// cmds_execution(data, envp);
	// close(data->prevpipe);
	// wait_pidz(parsing);
}

// < in ls | wc -w > out

	// printf("in: %d; out: %d\n", s_redir->redir_in, s_redir->redir_out);
	// printf("in: %s; out: %s\n", data->infile, data->outfile);
	// printf("infile: %s\n", (*data)->infile);
	// if ((*data)->infile)
		// (*data)->prevpipe = open((*data)->infile, O_RDONLY);
	// if (((*data)->prevpipe) == -1)
	// {
		// perror("infile");
		// exit(0);
	// }