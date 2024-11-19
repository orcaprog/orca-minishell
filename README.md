### README for GitHub

#### **Minishell**  
A minimal shell implemented in C, inspired by Bash, showcasing fundamental shell features while adhering to strict programming standards.  

---

#### **Features**
- **Interactive Shell Prompt**: Displays a prompt while waiting for user input.  
- **Command Execution**:  
  - Searches for executables using the `PATH` variable or a provided relative/absolute path.  
  - Supports executing multiple commands using pipes (`|`).  
- **Redirections**:  
  - `<`: Redirect input from a file.  
  - `>`: Redirect output to a file.  
  - `<<`: Implements heredoc by reading input until a delimiter is reached.  
  - `>>`: Redirect output in append mode.  
- **Environment Variable Expansion**: Expands `$VARIABLE` to its value and handles `$?` for the exit status of the last executed command.  
- **Built-in Commands**: Implements:  
  - `echo` with `-n` option  
  - `cd` for navigating directories  
  - `pwd` to display the current directory  
  - `export` for setting environment variables  
  - `unset` for removing environment variables  
  - `env` to display the environment  
  - `exit` for exiting the shell  
- **Signal Handling**:  
  - `ctrl-C`: Displays a new prompt.  
  - `ctrl-D`: Exits the shell.  
  - `ctrl-\`: Ignored in interactive mode.  
- **Quoting Support**:  
  - Single quotes (`'`) to prevent interpretation of meta-characters.  
  - Double quotes (`"`) to allow `$` expansion but prevent other interpretations.  

---

#### **Execution Part Contributions**
- Implemented redirection operations (`<`, `>`, `<<`, `>>`).  
- Developed pipe (`|`) handling to enable command chaining.  
- Managed environment variable parsing and expansion.  
- Integrated signal handling for `ctrl-C`, `ctrl-D`, and `ctrl-\`.  

---

#### **Project Constraints**
- Avoids unclosed quotes or unsupported characters like `\` or `;`.  
- Uses no more than one global variable for enhanced modularity.  
- Inspired by Bash with a focus on replicating its behavior in interactive mode.  

---

