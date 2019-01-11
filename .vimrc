" Misc
set mouse=a
set number
set tabstop=4
set listchars=tab:\|\ 
set list

" Theme
syntax enable
set background=dark
colorscheme gruvbox
let g:lightline = { 'colorscheme': 'gruvbox' }

highlight Normal ctermbg=NONE

" File Explorer
let g:netrw_banner = 0
let g:netrw_liststyle = 3
let g:netrw_browse_split = 4
let g:netrw_altv = 1
let g:netrw_winsize = 15

" Autostart explorer
augroup ProjectDrawer
autocmd!
	autocmd VimEnter * :Vexplore
	autocmd TabNew * call feedkeys(":Vexplore\<CR>", 'n')
augroup END

" File Search
set path+=**
set wildmenu

" Word Search
let g:side_search_prg = 'ag --word-regexp'
	\. " --ignore='*.js.map'"
	\. " --heading --stats -B 1 -A 4"
let g:side_search_splitter = 'vnew'
let g:side_search_split_pct = 0.4
nnoremap <Leader>ss :SideSearch <C-r><C-w><CR> | wincmd p
command! -complete=file -nargs=+ SS execute 'SideSearch

" Vundle
set nocompatible              " be iMproved, required
filetype off                  " required
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'VundleVim/Vundle.vim'
Plugin 'itchyny/lightline.vim'
Plugin 'shinchu/lightline-gruvbox.vim'
Plugin 'rking/ag.vim'
Plugin 'airblade/vim-gitgutter'
Plugin 'w0rp/ale'
Plugin 'mattn/emmet-vim'
Plugin 'ddrscott/vim-side-search'

call vundle#end()            " required
filetype plugin indent on    " required
