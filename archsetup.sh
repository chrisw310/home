#!/bin/bash

# Precondition:
# 	boot to command line
# 	connected to internet with wpa_supplicant
# 	created and su'd to chris
# 	cloned this repo to $HOME

# Base
sudo pacman -S xorg-server xorg-xinit xf86-video-intel vim

# Desktop
sudo pacman -S bspwm sxhkd polybar feh compton

# Suckless deps
sudo pacman -S dmenu webkit2gtk xorg-xsetroot gst-libav

# Install suckless tools
mkdir ~/suckless
cd ~/suckless
git clone https://github.com/chrisw310/st
git clone https://github.com/chrisw310/surf
git clone https://github.com/chrisw310/dwm
git clone https://github.com/chrisw310/tabbed
git clone https://github.com/chrisw310/noice
sh activate.sh
