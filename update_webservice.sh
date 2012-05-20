#! /bin/sh

cd `dirname "$0"`

PATH="$HOME/bin:$HOME/.cabal/bin:$PATH"
export PATH

git pull

cd grammar

make && cp -vf Mountaineering.pgf ~/.cabal/share/gf-3.3.3/www/grammars/


cd "$HOME/public_html/mscthesis/src"
git pull

