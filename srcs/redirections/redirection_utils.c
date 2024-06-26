
#include "../../includes/minishell.h"

void	reset_outfile(t_exec *data, int i)
{
	if (!ft_strncmp(data->parsing_ptr->tkn[i], ">", 1)
	|| !ft_strncmp(data->parsing_ptr->tkn[i], ">>", 2))
	{
		free(data->outfile);
		data->outfile = NULL;
	}
}

void	print_output(int fd)
{
	char	*line;

	if (!fd)
		return ;
	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	redirect_infile(t_exec *data, int *fd, char *path)
{
	*fd = open(path, O_CREAT | O_RDONLY, 0777);
	if (*fd == -1)
	{
		perror("outfile open");
		return ;// error handling
	}	
	if (dup2(*fd, STDIN_FILENO) == -1)
	{
		data->parsing_ptr->exit_value = PERMISSION_DENY;
		perror("redir_infile");
	}
	close(*fd);
}

void	redirect_output(t_exec *data, t_redir *s_redir)
{
	int		fd_out;

	if (data->outfile && access(data->outfile, F_OK | R_OK) == -1)
	{
		perror("access");
		return ;
	}
	if (s_redir->redir_out == TRUE)
		fd_out = open(data->outfile, O_RDWR | O_TRUNC, 0644);
	else if (s_redir->append == TRUE)
		fd_out = open(data->outfile, O_RDWR | O_APPEND, 0644);
	if (fd_out == -1)
	{
		perror("outfile");
		data->parsing_ptr->exit_value = PERMISSION_DENY;
		return ;// error handling
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror_exit("redir outfile");// error handling
		data->parsing_ptr->exit_value = DUP_FAILURE;
	}
	close(fd_out);
}
