#include "get_next_line.h"

char *ft_strndup(const char *s, size_t n) { 

	size_t i; 
	char *dup; 

	dup = (char *)malloc(n + 1);
	if(!dup)
		return (NULL); 
	i = 0;  
	while(i < n ) { 
		dup[i] = s[i]; 
		i++; 
	}
	dup[i] = '\0'; 
	return (dup); 
}

// implementing a ft_strchr that returns a ssize_t 
// ssize_t is the signed version of size_t. It's generally the same width as size_t but uses the most significant bit to store the sign.

// ssize_t  primary purpose is to be the return type for functions, especially POSIX I/O and system calls like read(), write(), and recv()

ssize_t ft_strchr(const char *s, int c) { 
	ssize_t i; 
	i = 0; 

	while(s[i] && s[i] != (char)c) { 
		i++; 
	}
	if(s[i] == (char )c) 
		return (i); 
	return (-1); 	
}

size_t ft_strlen(const char* s) { 
	size_t len; 

	len = 0; 
	while(*s++)
		len++; 
	return (len); 	
}