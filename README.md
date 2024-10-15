# Unix Shell Implementation

## Overview
This project is a simple Unix shell implementation written in C. It consists of two parts that handle basic shell functionalities, including executing commands and maintaining a command history.

## Project Structure
- **part1.c**: A basic shell implementation that allows users to enter and execute commands, including support for background execution using `&`.
- **part2.c**: Extends the shell to include a history feature, allowing users to see and re-execute past commands.

## Features
- **Command Execution**: Supports executing user commands, including running them in the foreground or background.
- **History Feature (part2.c)**: Maintains a history of the last 10 commands entered, allowing users to re-run commands using `!N` (for a specific command) or `!!` (for the most recent command).
- **Basic Shell Prompts**: Displays a simple prompt that indicates the current shell.

## Usage
1. **Compile the Shell**: Compile both parts of the shell using the following commands:
   ```sh
   gcc part1.c -o part1
   gcc part2.c -o part2
   ```
2. **Run the Shell**: To run the shell, use the following commands:
   ```sh
   ./part1   # For basic shell functionality
   ./part2   # For shell with history feature
   ```

## How It Works
- **part1.c**: Implements a basic Unix shell that reads user input, tokenizes the command, and uses `fork()` and `execvp()` to execute it. It also supports background execution if a command ends with `&`.
- **part2.c**: Extends the functionality to include a command history. Users can type `history` to see the last 10 commands, `!!` to repeat the most recent command, or `!N` to execute a specific command from history.
