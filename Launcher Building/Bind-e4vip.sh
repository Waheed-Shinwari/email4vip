#!/bin/bash

sudo apt-get install xbindkeys

#xbindkeys --defaults > $HOME/.xbindkeysrc

cat xbindkeysrc >> ~/.xbindkeysrc

xbindkeys
