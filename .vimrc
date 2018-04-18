set nocompatible              " be iMproved, required
filetype off                  " required
" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

" let Vundle manage Vundle, required
Plugin 'gmarik/Vundle.vim'
Plugin 'altercation/vim-colors-solarized'
Plugin 'Valloric/YouCompleteMe'
call vundle#end()            " required
filetype plugin indent on    " required


syntax on
set background=dark
colorscheme solarized
"set expandtab
set number 
set autoindent
set ruler 
set ignorecase
set smartcase
set hlsearch
set incsearch
set ts=2
set sw=2
set sts=2
set laststatus=2
set mousefocus 
set mouse=a
set backspace=indent,eol,start

"opens a file at the same place I left off at.
if has("autocmd")
  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
endif

au filetype cpp nnoremap <F9> :w <bar> exec '!g++ '.shellescape('%').'&& ./a.out'<CR>

"YouCompleteMe
let g:ycm_extra_conf_globlist = ['~/Training/*']
let g:ycm_autoclose_preview_window_after_completion = 1
let g:ycm_key_list_select_completion = ['<TAB>', '<Down>', '<Enter>']
