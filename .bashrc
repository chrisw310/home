#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias yt='youtube-viewer'
alias ls='ls --color=auto'
alias mem="sudo python ~/ps_mem/ps_mem.py"

pgen() { pwgen -1 -y -r "\'\"\`" 100 | tpm insert $1; }
pstore() { echo "$2" | tpm insert "$1"; } 
pget() { tpm show "$1" | tr -d '\n' | xclip -selection clipboard; }

function parse_git_dirty {
  [[ $(git status -uno 2> /dev/null | tail -n1) != "nothing to commit (use -u to show untracked files)" ]] && echo "*"
}

#PS1='\n\[\033[7m\]\[\033[1m\] [\w]$(parse_git_dirty) \[\033[0m\] '
PS1='\n\[\033[1m\][\w$(parse_git_dirty)]\[\033[0m\] '
