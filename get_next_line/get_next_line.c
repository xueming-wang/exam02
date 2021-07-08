//#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
static int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return (i);
}

static char *ft_strjoin(char *s1, char *s2)
{
    int i = 0;
    int j = 0;
    int size1 = 0;
    int size2 ;
    char *tab;

if (!s1 || !s2)
		return 0;
    size1 = ft_strlen(s1);
    size2 = ft_strlen(s2);

    tab = malloc(sizeof(char*) * (size1+size2) + 1);
    if (!tab)
        return (NULL);
    while (i < size1)
    {
        tab[i] = s1[i];
        i++;
    }
    while (j< size2)
    {
        tab[i] = s2[j];
        i++;
        j++;
        
    }
    tab[i] = '\0';
    return (tab);
}

static char *ft_strdup(char *str)
{
    int i  = 0;
    char *tab;
    int size = ft_strlen(str);

    tab = malloc(sizeof(char *) * size + 1);
    if (!tab)
        return (NULL);
    while (i < size)
    {
        tab[i] = str[i];
        i++;
    }
    tab[i] = '\0';
    return (tab);
}

int get_next_line(char **line)
{
    char buf[2];
    int r;
    char *tmp;

    if (!line)
        return (-1);
    *line = ft_strdup("");
    while((r = read(0, buf, 1)) > 0)
    {
        buf[r]= '\0';
        if (buf[0] == '\n')
            return (1);
        tmp = *line;
        *line = ft_strjoin(tmp, buf);
        free(tmp);
    }
    // if (r < 0)
    //     return (-1);
    // if (r == 0)
    //     return (0);
    // return (0);
    return (r == 0? 0 : -1);
}

// int     get_next_line(char **line)
// {
//     char *buf;
//     int i = 0;
//     int r;

//     buf = malloc(sizeof(char*) * 100000);
//     if (!line || !buf)
//         return (-1);
//     while ((r = read(0, &buf[i], 1)) > 0 && buf[i]!='\n')
//         i++;
//     buf[i] = '\0';
//     if (r == -1)
//     {
//         free(buf);
//         return (-1);
//     }
//     *line = buf;
//     if (r < 0)
//         return (-1);
//     if (r == 0)
//         return (0);
//     return (1);
// }



// int get_next_line(char **line)
// {
// 	char	*buf;
// 	int		res;
// 	int		i;

// 	i = 0;
// 	buf = 0;
// 	if (read(0, buf, 0) < 0 || !line || !(buf = malloc(100000)))
// 		return (-1);
// 	while ((res = read(0, &buf[i], 1)) > 0 && buf[i] != '\n')
// 		i++;
// 	buf[i] = '\0';
// 	res != -1 ? *line = buf : free(buf);
// 	return (res);
// }
int main(void)
{
	int		r;
	char	*line;

	line = NULL;
	while ((r = get_next_line(&line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s", line);
	free(line);
	line = NULL;
}
