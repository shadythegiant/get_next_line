#include "get_next_line.h"

static void *ft_cleanup(char **buffer) { 
	if(*buffer != NULL)
		free(*buffer); 
	*buffer = NULL; 
	return (NULL); 	
}


// get line function 

static char *ft_get_line(char **buffer, size_t end) { 
	char *tmp; 
	char *buf_copy; 
	size_t i; 

	buf_copy = *buffer; 
	tmp = ft_strndup(buf_copy, end);
	if(!tmp)
		return(ft_cleanup(buffer)); 
	i = 0; 	
	while(buf_copy[end])
		buf_copy[i++] = buf_copy[end++]; 
	while(buf_copy[i])
		buf_copy[i++] = '\0';
	return(tmp); 	
}


// expand buffer 

/* expand_buf to reallocate the buffer to a larger size (buf_size + BUFFER_SIZE + 1).*/

static char *ft_expand_buffer(char **buffer , size_t buffer_size) { 
	char 			*new_buffer; 
	size_t 			i; 
	unsigned long 	read_buffer_size;

	i = 0; 
	read_buffer_size = (unsigned long)BUFFER_SIZE; 
	new_buffer =(char *) malloc(read_buffer_size + buffer_size + 1); 
	if(!new_buffer)
		return (ft_cleanup(buffer));
	while((*buffer)[i]) {
		new_buffer[i] = *buffer[i]; 
		i++; 
	}	 
	new_buffer[i] = '\0'; 
	free(*buffer); 
	*buffer = new_buffer; 
	return(new_buffer); 
}

// read_until_newline 

static char *ft_read_until_newline(int fd, char **buffer, int bytes) { 
	// an unsigned int to temp store the length of buffer before reading new
	// content
	size_t	buffer_size; 
	ssize_t newline_position; 

	newline_position = ft_strchr(*buffer, '\n'); 
	/*
	This while loop runs as long as the entire line has not been found in the current buffer (i.e., newline_position is $-1$). This means more data must be read from the file.
	*/
	while(newline_position == -1) { 
		// no '\n' is found
		buffer_size = ft_strlen(*buffer); 
		//calling expandbufffer function to allocate more in the buffer 
		if(!ft_expand_buffer(buffer, buffer_size))
			return(ft_cleanup(buffer)); 
		// reading new data 
		bytes = read(fd, *buffer + buffer_size, BUFFER_SIZE); 
		(*buffer)[buffer_size + bytes] = '\0'; 
		if(bytes == 0) 
			return(ft_get_line(buffer, buffer_size)); 
		if(bytes == -1) 
			return (ft_cleanup(buffer)); 
		newline_position = ft_strchr(*buffer, '\n')	; 
	}
	return (ft_get_line(buffer, newline_position + 1)); 
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
	// initial buffer allocation 
	// first call only 

	if(!buffer) { 
		// check if buffer is NULL in the first call or after a cleanup
		buffer = (char *)malloc(read_buf_size + 1); 
		if(!buffer)
			return (NULL); 
		buffer[0] = '\0'; 	
	} 
	if(!buffer[0]) 
	{ 
		bytes = read(fd, buffer, BUFFER_SIZE ); 
		// checks if bytes == 0 (EOF)
		// bytes == -1 (error in read call)
		if(bytes == 0 || bytes == -1) 
			return(ft_cleanup(&buffer)); 
		buffer[bytes] = '\0'; 
	}

	return (ft_read_until_newline(fd, &buffer, bytes)); 
}