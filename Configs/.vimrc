version 6.0
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
map! <S-Insert> *
vmap  "*d
map Q gq
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(expand((exists("g:netrw_gx")? g:netrw_gx : '<cfile>')),netrw#CheckIfRemote())
vmap <C-Del> "*d
vmap <S-Del> "*d
vmap <C-Insert> "*y
vmap <S-Insert> "-d"*P
nmap <S-Insert> "*P
inoremap  u
let &cpo=s:cpo_save
unlet s:cpo_save
set backspace=indent,eol,start
set display=truncate
set guifont=Consolas:h12:cANSI:qDRAFT
set guioptions=egmrLT
set helplang=En
set history=200
set incsearch
set langnoremap
set nolangremap
set nrformats=bin,hex
set ruler
set scrolloff=5
set ttimeout
set ttimeoutlen=100
set wildmenu
set window=20
set ai
set si
set ts=4
set bs=indent,eol,start
set guioptions-=T
colo solarized
syntax on
set number

" vim: set ft=vim :
