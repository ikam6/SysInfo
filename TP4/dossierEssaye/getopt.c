#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    int flags, opt;
    int nsecs, fsecs, tfnd;

    nsecs = 0;
    fsecs = 0;
    tfnd = 0;
    flags = 0;
    while ((opt = getopt(argc, argv, "f:t:")) != -1) {
        switch (opt) {
            case 'f':
            flags = 1;
            fsecs = atoi(optarg);
            break;
            case 't':
            nsecs = atoi(optarg);
            tfnd = 1;
            break;
            default: /* '?' */
            fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
            argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    printf("flags=%d; tfnd=%d; nsecs=%d; optind=%d; fsecs=%d\n",
    flags, tfnd, nsecs, optind, fsecs);

    // if (optind >= argc) {
    //     fprintf(stderr, "Expected argument after options\n");
    //     exit(EXIT_FAILURE);
    // }

    printf("name argument f = %s\n", argv[fsecs]);
    printf("name argument t = %s\n", argv[nsecs]);


    /* Other code omitted */

    exit(EXIT_SUCCESS);
}
