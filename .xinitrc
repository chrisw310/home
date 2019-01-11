#!/bin/sh

userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/etc/X11/xinit/.Xresources
sysmodmap=/etc/X11/xinit/.Xmodmap

export EDITOR=vis
export BROWSER=surf

# airpods
pactl load-module module-bluetooth-discover
pactl load-module module-bluetooth-policy

# merge in defaults and keymaps

if [ -f $sysresources ]; then
    xrdb -merge $sysresources
fi

if [ -f $sysmodmap ]; then
    xmodmap $sysmodmap
fi

if [ -f "$userresources" ]; then
    xrdb -merge "$userresources"

fi

if [ -f "$usermodmap" ]; then
    xmodmap "$usermodmap"
fi

# start some nice programs

if [ -d /etc/X11/xinit/xinitrc.d ] ; then
 for f in /etc/X11/xinit/xinitrc.d/?*.sh ; do
  [ -x "$f" ] && . "$f"
 done
 unset f
fi

# dwm status bar
while true; do
	WIFI="$(iw dev wlp4s0 station dump | awk '{ if (NR==8) {print $2}}')dBm"
	CPU="$(top -bn1 | grep 'Cpu(s)' | sed 's/.*, *\([0-9.]*\)%* id.*/\1/' | awk '{print 100 - $1"%"}')"
	CPUTEMP="$(( `cat /sys/class/thermal/thermal_zone0/temp` / 1000 ))°C"
	MEM="$(free -h |  awk '{if (NR==2) {print $3}}')"
	SSD="$( df -h | grep /dev/sda3 | awk '{print $3}')"
	BATT="$( cat /sys/class/power_supply/BAT0/capacity)%"
	BATTWATT="$((`cat /sys/class/power_supply/BAT0/voltage_now` * `cat /sys/class/power_supply/BAT0/current_now` / (10**12)))W"
	DATETIME="$( date +"%a %b %-d %I:%M%P")"
	
	xsetroot -name "<span fgcolor='#282828'>\
<span bgcolor='#fb4934'> ${WIFI} <span fgcolor='#fe8019'></span></span>\
<span bgcolor='#fe8019'> ${CPU} ${CPUTEMP} <span fgcolor='#fabd2f'></span></span>\
<span bgcolor='#fabd2f'> ${MEM} <span fgcolor='#b8bb26'></span></span>\
<span bgcolor='#b8bb26'> ${SSD} <span fgcolor='#83a598'></span></span>\
<span bgcolor='#83a598'> ${BATT} ${BATTWATT} <span fgcolor='#d3869b'></span></span>\
<span bgcolor='#d3869b'> ${DATETIME} </span>\
</span>"
	sleep 1s
done &

#bgs ~/.config/background.jpg ~/.config/background1080.jpg ~/.config/background1080.jpg &
xsetroot -solid "#ebdbb2" &
xsetroot -cursor_name left_ptr &
tabbed st -w &
tabbed surf -pe &
exec dwm