#!/bin/zsh
# crear claves pub ssh en local. Copiar a github -> settings -> ssh gpg
#git remote set-url origin git@github.com:capedrazab/capedrazab.github.io.git
git commit -m "first commit"
git branch -M main 
git push -u origin main
git add --all
