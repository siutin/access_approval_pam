#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define PAM_SM_AUTH

#include <security/pam_modules.h>
#include <security/pam_appl.h>
#include "src/config.h"

void msleep(uint32_t milisec)
{
    struct timespec req={0};
    time_t sec=(uint32_t)(milisec/1000);
    milisec=milisec-(sec*1000);
    req.tv_sec=sec;
    req.tv_nsec=milisec*1000000L;
    while(nanosleep(&req,&req)==-1)
         continue;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char *argv[]) {
	printf("access_approval_pam (v%d.%d) - authenticate\n", ACCESS_APPROVAL_PAM_VERSION_MAJOR, ACCESS_APPROVAL_PAM_VERSION_MINOR);
	return PAM_SUCCESS;
}


PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	printf("access_approval_pam (v%d.%d) - open_session\n", ACCESS_APPROVAL_PAM_VERSION_MAJOR, ACCESS_APPROVAL_PAM_VERSION_MINOR);
	return PAM_SUCCESS;
}