# get_next_line - Reading Lines from File Descriptors

![42 school](https://img.shields.io/badge/42-School-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)
![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=flat-square)

## 📖 About

**get_next_line** is a project that challenges you to write a function that reads a line from a file descriptor. This function allows you to read from files or standard input one line at a time, regardless of the line length. The function handles multiple file descriptors simultaneously and efficiently manages memory using static variables and linked lists.

Through this project, I developed skills in file I/O operations, static variables, memory management, and working with linked list data structures in C.

## 🎯 Project Goals

- Implement a function that reads and returns one line at a time from a file descriptor
- Handle multiple file descriptors without losing the reading thread on each
- Efficiently manage memory using static variables and dynamic allocation
- Work with variable buffer sizes to optimize performance
- Understand file descriptors and system calls (read)

## 📚 Function Prototype

```c
char *get_next_line(int fd);
```

### Parameters

- **fd** - The file descriptor to read from

### Return Value

- **Read line**: The line that was read (including the terminating `\n` character, except if EOF was reached without a `\n`)
- **NULL**: If there is nothing more to read or if an error occurred

## 🧠 Implementation Strategy

My implementation uses a **linked list-based buffer management system**:

### Data Structure

```c
typedef struct s_list
{
    char            *current;  // String buffer
    struct s_list   *next;     // Next node in the list
} t_list;
```

### Algorithm Flow

1. **Validation**: Check if the file descriptor is valid and BUFFER_SIZE is positive
2. **Buffer Creation**: Read from the file descriptor in chunks of BUFFER_SIZE
3. **List Building**: Store each buffer in a linked list node
4. **Newline Detection**: Continue reading until a newline character is found or EOF is reached
5. **Line Extraction**: Extract the complete line from the linked list
6. **Cleanup**: Free processed nodes and keep remaining data for the next call
7. **Static Variable**: Maintain the list state between function calls for the same fd

### Key Features

- **Static variable management**: Preserves state between function calls
- **Dynamic buffer handling**: Works with any BUFFER_SIZE value
- **Multiple file descriptor support**: Can handle multiple fds simultaneously
- **Memory efficiency**: Only allocates memory as needed
- **Edge case handling**: Properly handles EOF, empty lines, and read errors

## 🛠️ Compilation

### Basic Compilation

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_test
```

### With Custom Buffer Size

You can define the buffer size at compilation time:

```bash
# Small buffer (testing edge cases)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c

# Medium buffer (default)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

# Large buffer (performance)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1024 get_next_line.c get_next_line_utils.c
```

## 🚀 Usage

### Example Code

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    // Open a file
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);

    // Read and print each line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```

### Reading from Standard Input

```c
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    char *line;

    printf("Enter text (Ctrl+D to end):\n");
    while ((line = get_next_line(0)) != NULL)
    {
        printf("You entered: %s", line);
        free(line);
    }
    return (0);
}
```

### Reading from Multiple File Descriptors

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd1, fd2;
    char    *line1, *line2;

    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);

    // Read alternately from two files
    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);

    printf("File 1: %s", line1);
    printf("File 2: %s", line2);

    free(line1);
    free(line2);

    close(fd1);
    close(fd2);
    return (0);
}
```

## 📊 Implementation Structure

The project consists of three main files:

### get_next_line.c

Main function and core logic:

- **get_next_line()** - Main function that orchestrates the reading process
- **create_list()** - Reads from fd and builds the linked list
- **add_buf()** - Adds a new buffer node to the list
- **get_1line()** - Extracts and returns the complete line
- **free_list()** - Cleans up processed nodes and preserves remaining data

### get_next_line_utils.c

Helper functions:

- **find_last()** - Finds the last node in the linked list
- **search_for_newline()** - Checks if a newline character exists in the list
- **len_newline()** - Calculates the length of the line up to the newline
- **strcopy()** - Copies the line from the list to the output string
- **free_all()** - Frees all nodes and handles cleanup

### get_next_line.h

Header file containing:

- Structure definition (t_list)
- Function prototypes
- BUFFER_SIZE definition (default: 10)
- Required includes (stdlib.h, fcntl.h, unistd.h)

## ⚙️ Technical Details

- **Language**: C
- **Compiler**: gcc
- **Flags**: `-Wall -Wextra -Werror`
- **Norm**: 42 Norminette
- **Data Structure**: Singly-linked list
- **Static Variables**: Used to maintain state between function calls
- **System Calls**: read()
- **Buffer Size**: Configurable via BUFFER_SIZE macro

## 🎮 Testing

### Basic Test

Create a test file:

```bash
echo -e "Hello World\nThis is line 2\nLine 3" > test.txt
```

Compile and run:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
./a.out
```

### Test with Different Buffer Sizes

```bash
# Test with BUFFER_SIZE = 1 (each character is read individually)
gcc -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c && ./a.out

# Test with BUFFER_SIZE = 10000 (large buffer)
gcc -D BUFFER_SIZE=10000 get_next_line.c get_next_line_utils.c main.c && ./a.out
```

### Edge Cases to Test

- Empty files
- Files with no newline at the end
- Files with only newlines
- Very long lines
- Reading from standard input
- Multiple file descriptors
- Invalid file descriptors
- BUFFER_SIZE = 1

### Testing with Valgrind

Check for memory leaks:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./a.out
```

## 📝 Notes

- All functions follow the 42 Norminette coding standards
- Memory is properly managed with no leaks
- The function works with any positive BUFFER_SIZE value
- Handles edge cases (empty files, no trailing newline, read errors)
- Uses static variables to maintain state across multiple calls
- Supports reading from multiple file descriptors simultaneously
- Each line returned includes the terminating `\n` (if present)
- The caller is responsible for freeing the returned line
- Returns NULL when reaching EOF or encountering an error

## 🔍 How It Works

1. **First Call**: The static list is NULL, so the function starts reading from the file descriptor
2. **Buffer Reading**: Data is read in chunks of BUFFER_SIZE and stored in linked list nodes
3. **Newline Search**: The function searches for a `\n` character in the accumulated data
4. **Line Extraction**: Once found (or EOF reached), the line is extracted and returned
5. **State Preservation**: Remaining data after the newline is kept in the static list
6. **Subsequent Calls**: The next call continues from where it left off, using the preserved data
7. **Cleanup**: When EOF is reached or an error occurs, all memory is freed and NULL is returned

## 👤 Author

**opopov** - 42 School Student
