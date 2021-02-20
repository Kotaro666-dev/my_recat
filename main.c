#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

static ssize_t	my_strlen(char *str)
{
	int len = 0;
	while (str[len])
	{
		len++;
	}
	return (len);
}

static void		my_putstr(char *str)
{
	write(STDOUT_FILENO, str, my_strlen(str));
}

static ssize_t	get_file_size(char *filename)
{
	struct	stat st;
	ssize_t	result;

	stat(filename, &st);
	result = st.st_size;
	return (result);
}

static void		my_recat(char *line, ssize_t file_size)
{
	int i = file_size;
	while (i >= 0)
	{
		write(STDOUT_FILENO, &line[i], 1);
		i--;
	}
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	ssize_t	file_size;

	if (argc != 2)
	{
		my_putstr("ERROR: NO FILE GIVEN.\n");
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		my_putstr("ERROR: CANNNOT READ FILE.\n");
		return (0);
	}
	file_size = get_file_size(argv[1]);
	if (!(line = (char *)calloc(sizeof(char), file_size + 1)))
	{
		return (1);
	}
	if (read(fd, line, file_size) == -1)
	{
		my_putstr("ERROR: FAILED TO READ FILE.\n");
		return (0);
	}
	my_recat(line, file_size);
	free(line);
	line = NULL;
	return (0);
}
