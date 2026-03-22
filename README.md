<p align="center">
  <a href="https://42.fr/en/homepage/" target="blank">
    <img src="https://upload.wikimedia.org/wikipedia/commons/8/8d/42_Logo.svg" width="150" alt="42 Logo" />
  </a>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Campus-Paris-000000?style=for-the-badge&logo=target" />
  <img src="https://img.shields.io/badge/Project-Minishell-success?style=for-the-badge&logo=gnubash&logoColor=white" />
  <img src="https://img.shields.io/badge/Language-C-A8B9CC?style=for-the-badge&logo=c&logoColor=white" />
</p>

<p align="center">
  <b>As beautiful as a shell.</b><br>
  A minimal bash-like shell implementation focusing on process management and command execution.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Process-Management-orange?style=flat-square">
  <img src="https://img.shields.io/badge/Lexing-Parsing-blue?style=flat-square">
  <img src="https://img.shields.io/badge/Built--ins-Implemented-yellow?style=flat-square">
  <img src="https://img.shields.io/badge/Signals-Handled-red?style=flat-square">
</p>

---

## 🐚 Project Overview
The **Minishell** project is a 42 school assignment that requires recreating a simplified version of the Bash shell. It involves a deep understanding of system calls, process creation (`fork`), and inter-process communication (`pipe`).

### Core Features
- **Prompt Display**: A working command prompt with history (via `readline`).
- **Command Execution**: Searching and launching executables using the `PATH` variable.
- **Built-ins**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- **Redirections**: `<`, `>`, `>>`, `<<` (heredoc).
- **Pipes**: `|` to connect the output of one command to the input of another.
- **Environment Variables**: Expansion of `$VAR` and `$?`.
- **Signals**: Proper handling of `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`.

---

## 🏗️ Architecture Flow
The shell operates in a continuous loop through four main stages:

1. **Read**: Get input from the user using `readline`.
2. **Lexer/Parser**: Tokenize the input and build an Abstract Syntax Tree (AST) or a Command List.
3. **Expander**: Handle environment variables and quotes.
4. **Executor**: Create processes, set up pipes/redirections, and execute commands.



---

## 🛠️ Usage & Compilation
This project requires the `readline` library.

### Compilation
```bash
make
