#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAM_SM_AUTH

#include <security/pam_modules.h>
#include <security/pam_appl.h>

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char *argv[]) {
	printf("pam_demo - authenticate\n");
	return PAM_SUCCESS;
}


PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	printf("pam_demo - open_session\n");
	return PAM_SUCCESS;
}
