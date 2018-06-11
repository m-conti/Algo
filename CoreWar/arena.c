
int		option(char *opt)
{

}

char	*read_champ(int fd)
{
	int		ret;
	char	buf[2048];

	if ((ret = read(fd, buf, 4) < 4))
		return (NULL); //error
	if (!cmp_magic(buf))
		return (NULL); //error
	if ((ret = read(fd, buf, 128) < 128))
		return (NULL);
	
}

int		main(int ac, char **av)
{
	if (ac < 3)
}