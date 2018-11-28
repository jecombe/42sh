

# 42sh #
Shell based on bash.

## Shell Command Language ##

- Quoting
  - Escape Character: `\`
  - Single-Quotes: `'`
  - Double-Quotes: `"`
- Redirection
  - Redirecting Input: `[n]<`
  - Redirecting Output: `[n]>`
  - Appending Redirected Output: `[n]>>`
  - Here-Document: `[n]<<`
  - Duplicating Input FD: `[n]<&`
  - Duplicating Output FD: `[n]>&`
  - Moving File Descriptors: `[n]<&[digit]-` and `[n]>&[digit]-`
- Shell Commands
  - Simple Commands: `command1`
  - Pipelines: `command1 [ | command2 ...]`
  - Lists: `&&` and `||`
- Parameters and Variables
  - Special parameters: `*`, `?`, `$`, `0`
  - Shell variables: `ENV`, `HOME`, `IFS`, `PATH`, `PWD`
- Word Expansions
  - Tilde Expansion: `~`
  - Command Substitution: `` `command` ``
- Built-In
  - `env`, `setenv`, `unsetenv`
  - `set`, `export`, `unset`
  - `echo`
  - `exit`
  - `cd`
  - `hash`
  - `read`

## Shell Line Edition ##
- Copy: <kbd>command</kbd> + <kbd>C</kbd>
- Paste: <kbd>command</kbd> + <kbd>V</kbd>
- Dynamic autocompletion: <kbd>Tab</kbd>
- Dynamic history: <kbd>▲</kbd>
- Move cursor: <kbd>◀</kbd> and <kbd>▶</kbd>
- Move by words: <kbd>Alt</kbd> + <kbd>◀</kbd> and <kbd>Alt</kbd> + <kbd>▶</kbd>
- Move by lines: <kbd>Alt</kbd> + <kbd>▲</kbd> and <kbd>Alt</kbd> + <kbd>▼</kbd>
- Go to begin and end: <kbd>home</kbd> and <kbd>end</kbd>
- Delete character: <kbd>backspace</kbd> and <kbd>del</kbd>
