set path=.,,libs/include/**,libs/src/**

set smartindent
set autoindent

set number

autocmd FileType cpp,c setlocal tabstop=4 shiftwidth=4 expandtab path+=/usr/include/c++/**1 path+=/usr/include/c++/**2 path+=/usr/include/x86_64-linux-gnu/c++/** path+=/usr/include
autocmd FileType cpp,c :compiler gcc
