#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/timex.h>
#include <sys/syscall.h>

#define GETTIME50 448

// relevant data structures
/* struct timespec { */
/* 	time_t	tv_sec;		/\* seconds *\/ */
/* 	long	tv_nsec;	/\* and nanoseconds *\/ */
/* }; */

/* struct ntptimeval { */
/*         struct timespec time;	/\* current time (ns) (ro) *\/ */
/*         long maxerror;		/\* maximum error (us) (ro) *\/ */
/*         long esterror;		/\* estimated error (us) (ro) *\/ */
/*         long tai;		/\* TAI offset *\/ */
/*         int time_state;		/\* time status *\/ */
/* }; */
// -> due to alignment the compiler reserves four more bytes at the end of this struct

int main(int argc, char *argv[])
{
        struct ntptimeval  *buf = malloc(sizeof(struct ntptimeval));
        if (buf == NULL) {
                printf("Could allocate memory.");
                exit(1);
        }
        memset(buf, 0x00, sizeof(struct ntptimeval));
        printf("size of struct ntptimeval is %lu bytes.\n", sizeof(struct ntptimeval));


        // syscall prototype:
        // int ntp_gettime(struct ntptimeval *ntvp)
        syscall(GETTIME50, buf);

        // view with "hexdump gettime50_dump.bin"
        FILE *ptr;
        ptr = fopen("gettime50_dump.bin","wb");
        if (ptr == NULL){
                printf("Error while opening file.\n");
                exit(1);
        }

        fwrite(buf, sizeof(struct ntptimeval), 1, ptr);
        fclose(ptr);
        free(buf);

        return 0;
}
