#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <poll.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>

static struct termios oldtio;
static struct termios curtio;

void
term_setup(void (*sighandler)(int)){
    struct sigaction sa;
    
    tcgetattr(0, &oldtio);

    if(sighandler){
        memset(&sa, 0, sizeof(struct sigaction));
        sa.sa_handler = sighandler;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
        sigaction(SIGTERM, &sa, NULL);
    }

    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = SIG_IGN;
    sigaction(SIGTTOU, &sa, NULL);

    tcgetattr(0, &curtio);
    curtio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &curtio);
}

void
term_restore(){
    tcsetattr(0, TCSANOW, &oldtio);
}

static char get[4]= {0};

bool
kbhit(){
    struct pollfd pfds[1];
    int ret;
    memset(get, 0, sizeof(char) * 4);

    pfds[0].fd = 0;
    pfds[0].events = POLLIN;
    ret = poll(pfds, 1, 0);

    if (ret > 0) {
        read(0, get, 3);
        return strlen(get) > 0;
    }
    return false;
}

bool
keydown(const char* key){
    return !strcmp(get, key);
}
