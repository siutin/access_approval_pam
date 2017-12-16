#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define PAM_SM_AUTH

#include <security/pam_modules.h>
#include <security/pam_appl.h>
#include <sys/inotify.h>
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

// hard coded directory and file to watch. don't do this in production code
#define DIR_TO_WATCH "/tmp/test/notify-dir"
#define FILE_TO_WATCH "/tmp/test/notify-dir/notify-file.txt"

#define EVENT_SIZE (sizeof (struct inotify_event))

// define large enough buffer
#define EVENT_BUFFER_LENGTH (1024 * EVENT_SIZE + NAME_MAX + 1)

void print_event(struct inotify_event *event) {

    if (event->mask & IN_CREATE)
        printf("file created in directory\n");
    if (event->mask & IN_DELETE)
        printf("file deleted in directory\n");
    if (event->mask & IN_ACCESS)
        printf("file accessed\n");
    if (event->mask & IN_CLOSE)
        printf("file closed after reading or writing \n");
    if (event->mask & IN_OPEN)
        printf("file opened\n");

    if (event->len)
        printf("name: %s\n", event->name);

}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char *argv[]) {
	printf("access_approval_pam (v%d.%d) - authenticate\n", ACCESS_APPROVAL_PAM_VERSION_MAJOR, ACCESS_APPROVAL_PAM_VERSION_MINOR);
    int notify_fd;
    int watch_fd;
    long input_len;
    char *ptr;
    char buffer[EVENT_BUFFER_LENGTH];
    struct inotify_event *event;

    notify_fd = inotify_init();
    if (notify_fd < 0) {
        perror("cannot init inotify");
        exit(EXIT_FAILURE);
    }

    watch_fd = inotify_add_watch(notify_fd, DIR_TO_WATCH, IN_CREATE | IN_DELETE);
    if (watch_fd < 0) {
        perror("cannot add directory");
        exit(EXIT_FAILURE);
    }
    watch_fd = inotify_add_watch(notify_fd, FILE_TO_WATCH, IN_ACCESS | IN_CLOSE | IN_OPEN);
    if (watch_fd < 0) {
        perror("cannot add file");
        exit(EXIT_FAILURE);
    }

    while (1) {
        input_len = read(notify_fd, buffer, EVENT_BUFFER_LENGTH);
        if (input_len <= 0) {
            perror("error reading from inotify fd");
            exit(EXIT_FAILURE);
        }

        ptr = buffer;
        while (ptr < buffer + input_len) {
            event = (struct inotify_event *) ptr;
            print_event(event);
            ptr += sizeof (struct inotify_event) +event->len;
        }
    }

	return PAM_SUCCESS;
}


PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	printf("access_approval_pam (v%d.%d) - open_session\n", ACCESS_APPROVAL_PAM_VERSION_MAJOR, ACCESS_APPROVAL_PAM_VERSION_MINOR);
	return PAM_SUCCESS;
}