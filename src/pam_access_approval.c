#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define PAM_SM_AUTH

#include <security/pam_modules.h>
#include <security/pam_appl.h>
#include "src/config.h"
#include <libfswatch/c/libfswatch.h>

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

void session_handler(fsw_cevent const * const events, const unsigned int event_num, void * data) {
  printf("session_handler: %d\n",event_num);
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char *argv[]) {
	printf("access_approval_pam (v%d.%d) - authenticate\n", ACCESS_APPROVAL_PAM_VERSION_MAJOR, ACCESS_APPROVAL_PAM_VERSION_MINOR);
	// Initialize the library
	FSW_STATUS ret = fsw_init_library();
	printf("fsw_init_library: %d\n", ret);

	if (ret != FSW_OK)
	{
		return PAM_SYSTEM_ERR;
	}

	const FSW_HANDLE handle = fsw_init_session(inotify_monitor_type);

	if (FSW_INVALID_HANDLE == handle) {
		fsw_last_error();
		(void)printf("Invalid fswatch handle: %d\n",handle);
	}

	if ( FSW_OK != fsw_add_path(handle, "/tmp/test/notify-dir/notify-file.txt") ) {
		fsw_last_error();
		(void)printf("Fail to fsw_add_path");
	}

	if(FSW_OK != fsw_set_callback(handle, session_handler, NULL)) {
		fsw_last_error();
		(void)printf("Fail to fsw_set_callback");
	}

	fsw_set_allow_overflow(handle,0);

	if(FSW_OK != fsw_start_monitor(handle)) {
  	fsw_last_error();
		(void)printf("Fail to fsw_start_monitor");
	}

	while (1) {
		msleep(1000);
	};
	return PAM_SUCCESS;
}


PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	printf("access_approval_pam (v%d.%d) - open_session\n", ACCESS_APPROVAL_PAM_VERSION_MAJOR, ACCESS_APPROVAL_PAM_VERSION_MINOR);
	return PAM_SUCCESS;
}