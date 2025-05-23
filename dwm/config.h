#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] = { "Adwaita Sans:size=11:antialias=true:autohint=true" };
static const char dmenufont[] = "Adwaita Sans:size=11:antialias=true:autohint=true";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_rgb_20[]      = "#141414";
static const char col_rgb_35[]      = "#232323";
static const char col_rgb_75[]      = "#4b4b4b";
static const char col_rgb_128[]     = "#808080";
static const char col_rgb_255[]     = "#ffffff";
static const char col_rgb_0[]       = "#000000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_rgb_128, col_rgb_0, col_rgb_128 },
	[SchemeSel]  = { col_rgb_255, col_rgb_20,  col_rgb_255  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;	 /* 1 means attach after the currently active window */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "T",      tile },    /* first entry is default */
	{ "F",      NULL },    /* no layout function means floating behavior */
	{ "M",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define MOD1 Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_rgb_0, "-nf", col_rgb_128, "-sb", col_rgb_20, "-sf", col_rgb_255, NULL };
static const char *termcmd[]  = { "st", NULL };
/* volume commands */ 
static const char *volup[]    = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *voldown[]  = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *volmute[]  = { "pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle", NULL };
/* brightness commands */
static const char *brightup[]   = {"brightnessctl", "set", "5%+", NULL};
static const char *brightdown[] = {"brightnessctl", "set", "5%-", NULL};
/* screenshot commands */
static const char *screenshot[] = { "scrot","-s", "/home/one/Pictures/Screenshots/%Y-%m-%d-%H-%M-%S-sc.jpg", NULL};
/* custom dmenus */
static const char *misc_launcher[] = { "/home/one/.dwm/misc_launcher.sh", NULL};
static const char *options_launcher[] = { "/home/one/.dwm/options_launcher.sh", NULL};
/* misc */
static const char *lock[] = {"/home/one/.dwm/options/lock.sh", NULL};
static const Key keys[] = {
	/* MODIFIERS                    KEY                             FUNCTION        ARGUMENTS */
  /* vol keys */
  { 0,                            XF86XK_AudioLowerVolume,        spawn,          {.v = voldown } },
  { 0,                            XF86XK_AudioRaiseVolume,        spawn,          {.v = volup   } },
  { 0,                            XF86XK_AudioMute,               spawn,          {.v = volmute } },
  /* brightness keys */
  { 0,                            XF86XK_MonBrightnessUp,         spawn,          {.v = brightup} },
  { 0,                            XF86XK_MonBrightnessDown,       spawn,          {.v = brightdown} },
  /* screenshot keys */
	{ 0,                            XK_Print,                       spawn,          {.v = screenshot} },
  /* additional dmenus */
  { MODKEY|ShiftMask,             XK_m,                           spawn,          {.v = misc_launcher } },
  { MODKEY|ShiftMask,             XK_p,                           spawn,          {.v = options_launcher } },
  /* misc */
  { MOD1,                         XK_l,                           spawn,          {.v = lock} },
	/* from config.def.h */ 
	{ MODKEY,                       XK_p,                           spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,                      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                           togglebar,      {0} },
	{ MODKEY,                       XK_j,                           focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                           focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                           incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                           incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                           setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                           setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,                      zoom,           {0} },
	{ MODKEY,                       XK_Tab,                         view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                           killclient,     {0} },
	{ MODKEY,                       XK_t,                           setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                           setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                           setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                       setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                       togglefloating, {0} },
	{ MODKEY,                       XK_0,                           view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                           tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                       focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                     focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                       tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                      tagmon,         {.i = +1 } },
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
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

