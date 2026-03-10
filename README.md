
*This project has been created as part of the 42 curriculum by maratojo.*


## Description

**Get Next Line** is a C function that reads and returns a line from a file descriptor, one line at a time. This project introduces the concept of `static variables` in C and teaches efficient file reading and memory management.

The goal is to create `get_next_line()`, which returns a line read from a file descriptor with each call, regardless of the size of BUFFER_SIZE.

**Prototypes:**
```c
char *get_next_line(int fd);
```
For Bonus(multi-FD):
```C
char *get_next_line(int fd);
```

##  Instructions

### Installation
   **cloning the repository:**
```bash
git clone git@vogsphere.42antananarivo.mg:vogsphere/intra-uuid-9411f303-5053-4291-a2bc-e17f5b24883c-7300210-maratojo
```

### Compilation
To compile this project, use the following flag:

- Standard compilation (BUFFER_SIZE = 42)
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```
- for bonus (multi-FD)
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```
### Execution
To run the program, use:
```bash
./a.out
```

Memory leak check, use:
```bash
valgrind ./a.out
```

### Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("file.txt", O_RDONLY);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```
### Auxiliary Functions

**String operations:**
- `ft_strlen` - Calculate string length
- `ft_strchr` - Locate character in string (finds `\n`)
- `ft_strdup` - Duplicate a string
- `ft_strjoin` - Concatenate two strings
- `ft_substr` - Extract substring from string

## Algorithm and Data Structure

### Implementation Strategy

The project uses a **static variable approach** to preserve data between function calls, combined with **dynamic buffer reading**.

**Key Design Decisions:**

1. **Static Variable for State Preservation**
   - Uses `static char *stock` to store unprocessed data
   - Persists between function calls
   - Enables resuming from previous position


2. **Dynamic Buffer Allocation**
   - Allocates `BUFFER_SIZE + 1` bytes for each read operation
   - Flexible: works with any BUFFER_SIZE
   - Trade-off: Multiple allocations vs fixed memory usage

3. **Line Extraction Strategy**
   - Search for `\n` , using `ft_strchr()`
   - If found: extract line up to `\n`, save remainder in `stock`
   - If not found: return entire `stock`, set stock to `NULL`

### Data Structures

- `static char *stock` - Preserves unread data between calls (mandatory)
- `static char *stock[1024]` - Array for multiple file descriptors (bonus)
- `char buffer[BUFFER_SIZE + 1]` - Temporary read buffer
- Local string pointers - Manage dynamic allocations

## Resources

### Documentation
- 42 Subject (Get_next_line)
- [read Man Page](https://man7.org/linux/man-pages/man2/read.2.html)
- [open Man Page](https://man7.org/linux/man-pages/man2/open.2.html)
- [Static Variables in C](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File Descriptors Explained](https://www.bottomupcs.com/file_descriptors.xhtml)

### AI Usage
AI was used for the following tasks:

**Documentation Assistance:**
- Help to structure this README and translate content from French to English.

**Research and learning:**
- explain static variables and their persistence between function calls.
- Learned about file descriptors and how the `read()` system call works.
- Understanding Valgrind output for memory validation.

## Technical Notes

### Important Considerations

- All functions compile with flags: `-Wall -Wextra -Werror`
- Must work with `-D BUFFER_SIZE=n` flag at compilation
- Must compile both WITH and WITHOUT the `-D BUFFER_SIZE` flag
- No global variables used (only static variables allowed)
- No use of libft (all helper functions must be recoded)
- Functions handle all edge cases properly

### Memory Leak Note

If you read only part of a file and close the file descriptor:

```c
fd = open("file.txt", O_RDONLY);
line = get_next_line(fd);  // Read only first line
free(line);
close(fd);
```

**Valgrind will show:** `still reachable: X bytes`

**This is ACCEPTABLE** because:
- It's a "still reachable" leak (not "definitely lost")
- Caused by the static variable design requirement
- OS automatically frees this memory at program exit
- To avoid: read entire file with a loop

**Solution:**

In main, insert :
```c
while ((line = get_next_line(fd)) != NULL)
    free(line);
```

##  Project Structure

```
get_next_line/
├── get_next_line.c           # Main function
├── get_next_line_utils.c     # Helper functions
├── get_next_line.h           # Header file
├── get_next_line_bonus.c     # Bonus: multi-FD support
├── get_next_line_utils_bonus.c
├── get_next_line_bonus.h
└── README.md                 # This file
```

---

This project is part of the 42 School curriculum.

---
