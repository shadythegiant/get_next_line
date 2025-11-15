#include "get_next_line.h"

static void *ft_cleanup(char **buffer) { 
	if(*buffer != NULL)
		free(*buffer); 
	*buffer = NULL; 
	return (NULL); 	
}













// MAIN FUNCTION 


char *get_next_line(int fd) { 
	static char	 	*buffer; 
	int				bytes; 
	unsigned long	read_buf_size;

	// check if fd or buffer size is valid
	if(fd < 0 || BUFFER_SIZE <= 0) 
		return (NULL); 
	
	read_buf_size = (unsigned long)BUFFER_SIZE; 
	bytes = 0; 
	
}