#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAM_SM_AUTH

#include <security/pam_modules.h>
#include <security/pam_appl.h>
#include "src/config.h"

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char *argv[]) {
	printf("access_approval_pam (v%d.%d) - authenticate\n", ACCESS_APPROVAL_PAM_VERSION_MAJOR, ACCESS_APPROVAL_PAM_VERSION_MINOR);
	return PAM_SUCCESS;
}


PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	printf("access_approval_pam (v%d.%d) - open_session\n", ACCESS_APPROVAL_PAM_VERSION_MAJOR, ACCESS_APPROVAL_PAM_VERSION_MINOR);
	return PAM_SUCCESS;
}