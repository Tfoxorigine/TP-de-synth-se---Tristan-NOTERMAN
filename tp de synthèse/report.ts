const report = `

# Report

## File Structure

- **\`main.c\`**: Contains the main loop and manages the general flow of the shell.
- **\`prompt.c\`**: Contains functions related to displaying and retrieving user commands.
- **\`execution.c\`**: Manages the execution of user commands.

---
## Technical Details

- **\`STDOUT_FILENO\`**:
  - A constant defined in <unistd.h> that represents the standard output (usually the terminal).

- **\`calloc\`**:
  - Dynamically allocates memory (here 1024 bytes) and initializes each byte to \`0\`.

- **\`free\`**:
  - Frees the memory previously allocated with \`calloc\`. This prevents memory leaks.

---
## Behavior of the \`read\` function

- **Reading data**:  
  The \`read\` function reads the data entered by the user (from the standard input, here the keyboard) and stores it in a buffer, for example \`input\`.

- **Handling end of input**:  
  If the user presses **\`<Ctrl+D>\`**, the \`read\` function returns \`0\`, indicating the end of input (**EOF**).

- **Pressing "Enter"**:  
  If the user presses **Enter**, the string will contain a newline character (**\`\\n\`**) at the end.  
  This character is replaced by **\`\\0\`** so that the string is properly terminated.

---

## Code
\`\`\`c
// (Include your code snippets here)
\`\`\`

`;

// Use the native Deno.writeTextFile function to write to a file
await Deno.writeTextFile("README.md", report);

console.log("Report generated as README.md");