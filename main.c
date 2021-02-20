#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
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

static char		*my_strjoin(char *str1, char *str2)
{
	ssize_t	len;
	char	*result;
	int		i;
	int		j;

	len = my_strlen(str1) + my_strlen(str2);
	if (!(result = (char *)malloc(sizeof(char) * (len + 1))))
	{
		return (NULL);
	}
	i = 0;
	j = 0;
	while (str1[i])
	{
		result[j] = str1[i];
		i++;
		j++;
	}
	i = 0;
	while (str2[i])
	{
		result[j] = str2[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

static char		*my_strdup(char *str)
{
	char	*result;
	int		i;

	if (!(result = (char *)malloc(sizeof(char) * (my_strlen(str) + 1))))
	{
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static int		store_line(char **line, char *buffer)
{
	char *temp;

	if (!(temp = my_strdup(*line)))
	{
		return (1);
	}
	free(*line);
	if (!(*line = my_strjoin(temp, buffer)))
	{
		return (1);
	}
	free(temp);
	temp = NULL;
	return (0);
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
	char	buffer[2];
	char	*line;
	int		bytes;
	ssize_t	file_size;

	if (argc != 2)
	{
		my_putstr("ERROR: NO FILE GIVEN.\n");
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		my_putstr("ERROR: CANNNOT READ FILE.\n");
	}
	file_size = get_file_size(argv[1]);
	if (!(line = (char *)malloc(sizeof(char) * (file_size + 1))))
	{
		return (1);
	}
	while ((bytes = read(fd, buffer, 1)) > 0)
	{
		store_line(&line, buffer);
	}
	my_recat(line, file_size);
	free(line);
	line = NULL;
	return (0);
}
