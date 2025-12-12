_This project has been created as part of the 42 curriculum by azahidi._

## Description

**get_next_line** is a project at 42 that challenges students to create a function capable of reading a text file (or any file descriptor) one line at a time. The primary goal is to learn about **static variables** in C and how to manage memory persistence between function calls.

This specific implementation covers the **bonus** requirements, meaning it can manage multiple file descriptors simultaneously without losing the reading thread of any of them.

**Prototype:**

```c
char *get_next_line(int fd);
```

## Algorithm & Technical Choices

The algorithm selected for this project relies on a **dynamic buffer accumulation** strategy backed by a **static array of pointers**.

### 1\. Storage Strategy (Bonus Support)

To handle multiple file descriptors (the Bonus requirement), I utilized a static array of pointers:

```c
static char *buffer[FD_BUFFER_SIZE];
```

Each index in this array corresponds to a file descriptor (`fd`). This ensures that the leftover characters from one file are stored independently of others, allowing the program to switch between reading `fd 3`, `fd 4`, and `fd 5` without data corruption.

### 2\. The Reading Loop (Accumulation)

Unlike a linked-list approach, this implementation uses a linear memory expansion strategy:

1.  **Check Buffer:** The function first checks if the static buffer for the given `fd` contains data.
2.  **Read & Expand:** If no newline (`\n`) is found in the current buffer, the program enters a loop:
    - It reads `BUFFER_SIZE` bytes.
    - It calls `ft_reallocate_buff` to create a new, larger container that holds the old data plus the newly read bytes.
    - It continues this process until a newline is detected or the End of File (EOF) is reached.

### 3\. Line Extraction & Leftover Management

Once a newline is guaranteed to exist (or EOF is hit):

1.  **Extraction:** `ft_extract_line` is called. It uses `ft_strndup` to create a clean string containing the line up to the newline.
2.  **Shifting Data:** Crucially, the function does not free the static buffer immediately. Instead, it shifts the remaining characters (bytes after the `\n`) to the beginning of the buffer. This prepares the static variable for the next function call.
3.  **Cleanup:** If EOF is reached or an error occurs, `ft_cleanup` ensures the pointer is freed and set to NULL to prevent double-free errors or memory leaks.

**Justification for this approach:**
This algorithm was chosen for its cache locality. By keeping the data in a contiguous memory block (array) rather than fragmented nodes (linked list), we reduce cache misses during string parsing (`ft_strchr` and `ft_strlen`). While reallocating memory can be costly, it simplifies the logic significantly compared to managing a complex list of nodes.

## Instructions

### Compilation

To compile the project, you must define the `BUFFER_SIZE` macro. This determines how many bytes are read at a time.

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils.c main.c -o gnl
```

_Note: Replace `main.c` with your own test file._

### Execution

Run the executable with a file as an argument (if your main handles it) or simply run it to read from Standard Input (if implemented).

```bash
./gnl
```

### Integration

To use this in your own project, include the header file:

```c
#include "get_next_line_bonus.h"

int main(void)
{
    int fd = open("text.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Resources

### Documentation

- [man 2 read](https://man7.org/linux/man-pages/man2/read.2.html) - For understanding the `read` system call and return values.
- [man 3 malloc](https://man7.org/linux/man-pages/man3/malloc.3.html) - For memory allocation details.
- [open() system call](https://man7.org/linux/man-pages/man2/open.2.html) - For handling file descriptors.

### AI Usage

This project utilized Artificial Intelligence tools as follows:

- **Documentation:** The structure and content of this `README.md` were generated with the assistance of an AI language model to ensure clarity and adherence to the 42 subject requirements.
- **Code Verification:** AI was used to review the logic of the `ft_reallocate_buff` function to ensure no memory leaks occurred during the expansion process.
