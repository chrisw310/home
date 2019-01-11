#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "Inconsolata, Symbola 12";
static const char normbordercolor[] = "#ffffff";
static const char normbgcolor[]     = "#3c3836";
static const char normfgcolor[]     = "#ebdbb2";
static const char selbordercolor[]  = "#ffffff";
static const char selbgcolor[]      = "#282828";
static const char selfgcolor[]      = "#ebdbb2";
static const unsigned int borderpx  = 15;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool statusmarkup = True; /* Pango support */

static const unsigned int gappx     = 60;        /* gap pixel between windows */

/* tagging */
static const char *tags[] = { "", "", "", "", "" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.5; /* factor of master area size [0.05..0.95] */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", "Inconsolata", "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *terminal[]  = { "tabbed", "st", "-w", NULL };
static const char *browser[]  = { "tabbed", "surf", "-pe", NULL };
static const char *volumeUp[] = { "amixer", "-q", "sset", "Master", "5%+", NULL };
static const char *volumeDown[] = { "amixer", "-q", "sset", "Master", "5%-", NULL };
static const char *volumeMute[] = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *brightnessUp[] = { "xbacklight", "-ctrl", "gmux_backlight", "-inc", "10", NULL };
static const char *brightnessDown[] = { "xbacklight", "-ctrl", "gmux_backlight", "-dec", "10", NULL };
static const char *keyUp[] = { "kbdlight", "up", "10", NULL };
static const char *keyDown[] = { "kbdlight", "down", "10", NULL };


static Key keys[] = {
	/* function row */
	/* modifier  key                           function        argument */
	{ 0,         XF86XK_AudioRaiseVolume,      spawn,          {.v = volumeUp } },
	{ 0,         XF86XK_AudioLowerVolume,      spawn,          {.v = volumeDown } },
	{ 0,         XF86XK_AudioMute,             spawn,          {.v = volumeMute } },
	{ 0,         XF86XK_LaunchA,               spawn,          {.v = browser } },
	{ 0,         XF86XK_LaunchB,               spawn,          {.v = terminal } },
	{ 0,         XF86XK_MonBrightnessUp,       spawn,          {.v = brightnessUp } },
	{ 0,         XF86XK_MonBrightnessDown,     spawn,          {.v = brightnessDown } },
	{ 0,         XF86XK_KbdBrightnessUp,       spawn,          {.v = keyUp } },
	{ 0,         XF86XK_KbdBrightnessDown,     spawn,          {.v = keyDown } },
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = terminal } },
	{ MODKEY|ShiftMask,             XK_apostrophe,  spawn,          {.v = browser } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = terminal } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

