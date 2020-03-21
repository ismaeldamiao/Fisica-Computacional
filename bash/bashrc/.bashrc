# ~/.bashrc: executed by bash for non-login shells.
# Por Ismael Damião http://ismaeldamiao.blogspot.com/

# Para ignorar comandos duplicados
HISTCONTROL=ignoreboth
# Quantidades de comandos que serão lembrados
HISTSIZE=1000
HISTFILESIZE=2000
shopt -s histappend
# aliases
alias ls='ls --color=auto'
alias grep='grep --color=auto'
alias fgrep='fgrep --color=auto'
alias egrep='egrep --color=auto'
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'
alias clear='clear && clear'
alias ps='ps arxu'
alias cp='cp -R' # ↓ aliases recursivos
alias rm='rm -R' # Cuidado, perigoso!!
alias mkdir='mkdir -p'
alias scp='scp -rp'
# Paleta de cores
BLACK='\[\e[0;30m\]' # ↓ Normal
RED='\[\e[0;31m\]'
GREEN='\[\e[0;32m\]'
YELLOW='\[\e[0;33m\]'
BLUE='\[\e[0;34m\]'
PURPLE='\[\e[0;35m\]'
CYAN='\[\e[0;36m\]'
WHITE='\[\e[0m\]'
BLACKB='\[\e[01;30m\]' # ↓ Negrito
REDB='\[\e[01;31m\]'
GREENB='\[\e[01;32m\]'
YELLOWB='\[\e[01;33m\]'
BLUEB='\[\e[01;34m\]'
PURPLEB='\[\e[01;35m\]'
CYANB='\[\e[01;36m\]'
WHITE='\[\e[0m\]'

if [ "$PREFIX" == "/data/data/com.termux/files/usr" ]; then
   # Execute o screenfetch ou, em caso dele não existir, deixe-o fácil de instalar
   if [ -x $PREFIX/bin/screenfetch ]; then
      bash $PREFIX/bin/screenfetch
   else
      alias screenfetch='wget -O $PREFIX/bin/screenfetch https://git.io/vaHfR && chmod 777 $PREFIX/bin/screenfetch'
   fi
   # Verificar se é termux antes de colorir o PS1
   USER='user'
   HOSTNAME='termux'
   PS1FINAL='\n\$ '
   # Facilitar acesso ao diretório do ubuntu
   UBUNTU=$HOME/ubuntu/ubuntu-fs/root
   # aliases Termux
   alias termux-open='termux-open --chooser'
else
   # Execute o screenfetch ou, em caso dele não existir, deixe-o fácil de instalar
   if [ -x $HOME/bin/screenfetch ]; then
      bash $HOME/bin/screenfetch
   else
      if [ ! -d $HOME/bin ]; then mkdir $HOME/bin; fi
      alias screenfetch='wget -O $HOME/bin/screenfetch https://git.io/vaHfR && chmod 777 $HOME/bin/screenfetch'
   fi
   PS1FINAL='\$ '
   # aliases distros
   alias sshd='sudo service ssh restart'
fi
# Mude aqui as cores ou outras coisas do PS1 se quiser
PS1="$GREENB$USER@$HOSTNAME$WHITE:$BLUEB\w$WHITE$PS1FINAL"
