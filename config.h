/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 15;       /* gaps between windows  */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "-*-notosans nerd fonts-*-*-*-*-*-*-*-*-*-*-*-*-*:size=12" };
//static const char dmenufont[]       = "monospace:size=10"; // using rofia script, no need to have this
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "\uf120", "\uf121", "\uf1d8", "\uf269", "\uf7ca", "\uf212", "\ue5fe", "\uf0ca", "\uf30c"};
// steam icon \uf1b6
// f8a1 f8a4 f8a7 f8aa f8ad f8b0 f8b3 f8b6 f8b9 f8bc  0 1 2 3 4 5 6 7 8 9 in unicode
// fa1a time on | fa1d time off | f462 settings(plans for audio)

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "qutebrowser",  NULL,   NULL,       1 << 3,       0,           -1 },
	{ "Telegram", NULL,       NULL,       1 << 2,       0,           -1 },
	{ "URxvt",    NULL,       NULL,       0,            1,           -1 },
	{ "Anki",     NULL,       NULL,       1 << 5,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "\uf168",   NULL },    /* no layout function means floating behavior */
	{ "\ufad7",   monocle },
	{ "##",       horizgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ KeyPress, MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ KeyPress, MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ KeyPress, MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ KeyPress, MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
//static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[]  = { "rofia",   NULL }; // using a script to spawn rofi with desired args
static const char *termcmd[]  = { "st",      NULL };
static const char *anki[]     = { "anki",    NULL };
static const char *URdraw[]   = { "urdraw",  NULL }; // script to draw urxvt
static const char *slock[]    = { "slock",   NULL };
static const char *qutebrowser[]  = { "qutebrowser",  NULL };
static const char *telegram[] = { "telegram-desktop", NULL };

static Key keys[] = {
	/* modifier             key    function        argument              use "xev | grep key" to find out the keys */
	{ KeyPress, MODKEY,               40,    spawn,          {.v = roficmd    } }, // d
	{ KeyPress, Mod1Mask,             56,    spawn,          {.v = qutebrowser} }, // b
	{ KeyPress, Mod1Mask,             28,    spawn,          {.v = telegram   } }, // t
	{ KeyPress, MODKEY,               36,    spawn,          {.v = termcmd    } }, // return
	{ KeyPress, Mod1Mask,             36,    spawn,          {.v = URdraw     } }, // return
	{ KeyPress, Mod1Mask,             38,    spawn,          {.v = anki       } }, // a
	{ KeyPress, Mod1Mask,             66,    spawn,          {.v = slock      } }, // caps_lock
	{ KeyPress, MODKEY,               20,    setgaps,        {.i = -1 } },         // - gaps
	{ KeyPress, MODKEY,               21,    setgaps,        {.i = 0  } },         // = reset gaps
	{ KeyPress, MODKEY|ShiftMask,     21,    setgaps,        {.i = +1 } },         // + gaps
	{ KeyPress, MODKEY,               44,    focusstack,     {.i = +1 } },         // j
	{ KeyPress, MODKEY,               45,    focusstack,     {.i = -1 } },         // k
	{ KeyPress, MODKEY,               31,    incnmaster,     {.i = +1 } },         // i
	{ KeyPress, MODKEY,               19,    view,           {.ui = ~0} },         // 0
	{ KeyPress, MODKEY|ShiftMask,     19,    tag,            {.ui = ~0} },         // 0
	{ KeyPress, MODKEY,               59,    focusmon,       {.i = -1 } },         // comma
	{ KeyPress, MODKEY,               60,    focusmon,       {.i = +1 } },         // period
	{ KeyPress, MODKEY|ShiftMask,     59,    tagmon,         {.i = -1 } },         // comma
	{ KeyPress, MODKEY|ShiftMask,     60,    tagmon,         {.i = +1 } },         // period
	{ KeyPress, MODKEY,               40,    incnmaster,     {.i = -1 } },         // d
	{ KeyPress, MODKEY,               43,    setmfact,       {.f = -0.05 } },      // h
	{ KeyPress, MODKEY,               46,    setmfact,       {.f = +0.05 } },      // l
	{ KeyPress, MODKEY,               56,    togglebar,      {0} },                // b
	{ KeyPress, MODKEY,               36,    zoom,           {0} },                // Return
	{ KeyPress, MODKEY,               23,    view,           {0} },                // Tab
	{ KeyPress, MODKEY,               53,    killunsel,      {0} },                // x
	{ KeyPress, Mod1Mask,             45,    killclient,     {0} },                // k
	{ KeyPress, MODKEY,               65,    setlayout,      {0} },                // space
	{ KeyPress, MODKEY|ShiftMask,     65,    togglefloating, {0} },                // space
	{ KeyPress, MODKEY,               28,    setlayout,      {.v = &layouts[0]} }, // [T]ile
	{ KeyPress, MODKEY,               41,    setlayout,      {.v = &layouts[1]} }, // [F]loating
	{ KeyPress, MODKEY,               58,    setlayout,      {.v = &layouts[2]} }, // [M]onocle
	{ KeyPress, MODKEY,               42,    setlayout,      {.v = &layouts[3]} }, // [G]rid
	TAGKEYS(                10,                    0)                    // 1
	TAGKEYS(                11,                    1)                    // 2
	TAGKEYS(                12,                    2)                    // 3
	TAGKEYS(                13,                    3)                    // 4
	TAGKEYS(                14,                    4)                    // 5
	TAGKEYS(                15,                    5)                    // 6
	TAGKEYS(                16,                    6)                    // 7
	TAGKEYS(                17,                    7)                    // 8
	TAGKEYS(                18,                    8)                    // 9
	{ KeyPress, MODKEY,               24,    quit,           {0} },                // q
	{ KeyPress, MODKEY,               27,    quit,           {.i = 1} },           // gonna [R]estart dwm
   					
					/* scripts and others modifications */
    	// audioCtrl set volume up/down 5% and mute/unmute 
	{ KeyPress, Mod1Mask,             123,   spawn,         SHCMD("~/bin/audioCtrl 0")   }, // raise volume buttom
	{ KeyPress, Mod1Mask,             122,   spawn,         SHCMD("~/bin/audioCtrl 1")   }, // lower volume buttom
	{ KeyPress, Mod1Mask,             121,   spawn,         SHCMD("~/bin/audioCtrl 2")   }, // audio mute/unmute
	//  musicCtrl controls mpd via mpc
	{ KeyPress, Mod1Mask,             172,   spawn,         SHCMD("~/bin/musicCtrl 0")   }, // Play buttom
	{ KeyPress, Mod1Mask,             173,   spawn,         SHCMD("~/bin/musicCtrl 2")   }, // previous buttom
	{ KeyPress, Mod1Mask,             171,   spawn,         SHCMD("~/bin/musicCtrl 1")   }, // next buttom 
	{ KeyPress, Mod1Mask,             58,    spawn,         SHCMD("~/bin/musicCtrl 3")   }, // m  notify music playing
	// another nice things
	{ KeyPress, Mod1Mask,             107,   spawn,         SHCMD("~/bin/screeny")  },             // print buttom
	{ KeyPress, Mod1Mask,             27,    spawn,         SHCMD("~/bin/record" )  },             // r
	{ KeyPress, Mod1Mask,             39,    spawn,         SHCMD("~/bin/stoprec")  },             // s
	{ KeyPress, Mod1Mask,             29,    spawn,         SHCMD("~/bin/ytmp3 '($xclip -out)'")}, // y
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
