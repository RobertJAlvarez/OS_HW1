set nocompatible 	" Disable compatibility with vi which can cause unexpected issues
set viminfo='100,<500,s100,h
set showcmd     	" show partial command you type in the last line of the screen
set showmode 			" Show the mode you are on the last line
set showmatch			" Show matching words during a search
set wildmode=list:longest	" Make wildmenu behave like similar to Bash completion

"Indent options:
set expandtab    	" Use space characters instead of tabs
set shiftwidth=2 	" When shifting, indent using four spaces
set tabstop=2    	" Set tab width to 2 columns
set autoindent    " New lines inherit the indentation of previous lines
set smartindent   " Even better autoindent (e.g. add indent after '{')

"Search options:
set incsearch    	" While searching though a file incrementally highlight matching characters as you type
set ignorecase   	" Ignore capital letters during search
set smartcase     " Automatically switch search to case-sensitive when search query contains an uppercase letter

"Rendering options:
set scrolloff=5  	" Do not let cursor scroll bellow or above 5 number of lines when scrolling
set linebreak     " Avoid wrapping a line in the middle of a word
set nowrap        " Turn off word wrapping
syntax enable     " Enable syntax highlighting
colorscheme pablo " Set color of syntax

"Interface options
set statusline=   " Clear status line when vimrc is reloaded
"%F - Display full path of current file, %M - Modified flag shows if file is unsaved, %Y - Type of file in buffer, %R - Displays the read-only flag
set statusline+=\ %F\ %M\ %Y\ %R  " Status line left side
set statusline+=%=  " Use a divider to separate the left side from the right side
set statusline+=\ row:\ %l\ col:\ %c\ percent:\ %p%%  " Display row, column, and percentage
set laststatus=2  " Show the status on the second to last line
set wildmenu			" Enable auto completion menu after pressing TAB
set cursorline   	" Highlight cursor line underneath the cursor horizontally
set cursorcolumn 	" Highlight cursor line underneath the cursor vertically
set number       	" Add numbers to each line on the left-hand side
set title         " Set the window's title, reflecting the file currently being edited

"Miscellaneous options
set backspace=indent,eol,start  "Allow backspacing over indentation, line breaks and insertion start
set history=100   " Set the commands to save in history, default number is 20
set spell         " Enable spellchecking
" There are certain files that we would never want to edit with Vim. Wildmenu will ignore files with these extensions
set wildignore=*.docx,*.jpg,*.png,*.gif,*.pdf,*.pyc,*.exe,*.flv,*.img,*.xlsx
set autoread      " Autoreload the file in Vim if it has been changed outside of Vim

