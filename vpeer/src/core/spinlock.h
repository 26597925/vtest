#ifndef _VR_SPINLOCK_
#define _VR_SPINLOCK_

#define SPIN_INIT(q) spinlock_init(&(q)->lock);
#define SPIN_LOCK(q) spinlock_lock(&(q)->lock);
#define SPIN_UNLOCK(q) spinlock_unlock(&(q)->lock);
#define SPIN_DESTROY(q) spinlock_destroy(&(q)->lock);

#include "vr_config.h"

#if VR_PTHREAD_LOCK

#include <pthread.h>

// we use mutex instead of spinlock for some reason
// you can also replace to pthread_spinlock

struct spinlock {
	pthread_mutex_t lock;
};

static vr_inline void
spinlock_init(struct spinlock *lock) {
	pthread_mutex_init(&lock->lock, NULL);
}

static vr_inline void
spinlock_lock(struct spinlock *lock) {
	pthread_mutex_lock(&lock->lock);
}

static vr_inline int
spinlock_trylock(struct spinlock *lock) {
	return pthread_mutex_trylock(&lock->lock) == 0;
}

static vr_inline void
spinlock_unlock(struct spinlock *lock) {
	pthread_mutex_unlock(&lock->lock);
}

static vr_inline void
spinlock_destroy(struct spinlock *lock) {
	pthread_mutex_destroy(&lock->lock);
}

#else

struct spinlock {
	int lock;
};

static vr_inline void
spinlock_init(struct spinlock *lock) {
	lock->lock = 0;
}

static vr_inline void
spinlock_lock(struct spinlock *lock) {
	while (__sync_lock_test_and_set(&lock->lock,1)) {}
}

static vr_inline int
spinlock_trylock(struct spinlock *lock) {
	return __sync_lock_test_and_set(&lock->lock,1) == 0;
}

static vr_inline void
spinlock_unlock(struct spinlock *lock) {
	__sync_lock_release(&lock->lock);
}

static vr_inline void
spinlock_destroy(struct spinlock *lock) {
	(void) lock;
}

#endif

#endif
