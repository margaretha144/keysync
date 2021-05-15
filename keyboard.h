#define     UP      "\033[A"
#define     DOWN    "\033[B"
#define     LEFT    "\033[D"
#define     RIGHT   "\033[C"
#define     W   	"a"
#define		S		"s"
#define		A		"a"
#define 	D		"d"

void
term_setup(void (*sighandler)(int));

void
term_restore();

bool
kbhit();

bool
keydown(const char* key);
