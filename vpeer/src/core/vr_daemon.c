#include "vr_config.h"
#include "vr_core.h"

static vr_int_t
check_pid(const char *pidfile) {
	vr_int_t pid = 0;
	FILE *f = fopen(pidfile, "r");
	if (f == NULL)
		return 0;
	vr_int_t n = fscanf(f,"%d", &pid);
	fclose(f);

	if (n !=1 || pid == 0 || pid == getpid()) {
		return 0;
	}

	vr_int_t err = kill(pid, 0);
	
	if (err && errno == ESRCH)
		return 0;

	return pid;
}

static vr_int_t 
write_pid(const char *pidfile) {
	FILE *f;
	vr_int_t pid = 0;
	vr_int_t fd = open(pidfile, O_RDWR|O_CREAT, 0644);
	if (fd == -1) {
		fprintf(stderr, "Can't create %s.\n", pidfile);
		return 0;
	}
	f = fdopen(fd, "r+");
	if (f == NULL) {
		fprintf(stderr, "Can't open %s.\n", pidfile);
		return 0;
	}

	if (flock(fd, LOCK_EX|LOCK_NB) == -1) {
		vr_int_t n = fscanf(f, "%d", &pid);
		fclose(f);
		if (n != 1) {
			fprintf(stderr, "Can't lock and read pidfile.\n");
		} else {
			fprintf(stderr, "Can't lock pidfile, lock is held by pid %d.\n", pid);
		}
		return 0;
	}
	
	pid = getpid();
	if (!fprintf(f,"%d\n", pid)) {
		fprintf(stderr, "Can't write pid.\n");
		close(fd);
		return 0;
	}
	fflush(f);

	return pid;
}

vr_int_t
vr_daemon_init(const char *pidfile) {
	vr_int_t pid = check_pid(pidfile);

	if (pid) {
		fprintf(stderr, "Vpeer is already running, pid = %d.\n", pid);
		return VR_ERROR;
	}

#ifdef __APPLE__
	fprintf(stderr, "'daemon' is deprecated: first deprecated in OS X 10.5 , use launchd instead.\n");
#else
	if (daemon(1,0)) {
		fprintf(stderr, "Can't daemonize.\n");
		return VR_ERROR;
	}
#endif

	pid = write_pid(pidfile);
	if (pid == 0) {
		return VR_ERROR;
	}

	return VR_OK;
}

vr_int_t 
vr_daemon_exit(const char *pidfile) {
	return unlink(pidfile);
}
