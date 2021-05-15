#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include "keyboard.h"

static sig_atomic_t end = 0;

static void
sighandler(int signo) {
    end = 1;
}

int
main() {
    term_setup(sighandler);

    while (!end) {
        if (kbhit()) {
            if (keydown(UP))
                printf("This is \"UP\" button!\n");
            if (keydown(DOWN))
                printf("This is \"DOWN\" button!\n");
            if (keydown(LEFT))
                printf("This is \"LEFT\" button!\n");
            if (keydown(RIGHT))
                printf("This is \"RIGHT\" button!\n");
            if (keydown(W))
                printf("This is \"W\" button!\n");
			if (keydown(S))
				printf("This is \"S\" button!\n");
			if (keydown(A))
				printf("This is \"A\" button!\n");
			if (keydown(D))
				printf("This is \"D\" button!\n");
        }
    }

    term_restore();

    return 0;
}
