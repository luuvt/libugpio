/*
 * Copyright © 2012-2014 Michael Heimpold <mhei@heimpold.de>
 *
 * SPDX-License-Identifier: LGPL-2.1+
 */

#ifndef _UGPIO_INTERNAL_H_
#define _UGPIO_INTERNAL_H_

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#endif

#define GPIO_ROOT "/sys/class/gpio"
#define GPIO_EXPORT    GPIO_ROOT "/export"
#define GPIO_UNEXPORT  GPIO_ROOT "/unexport"
#define GPIO_DIRECTION GPIO_ROOT "/gpio%d/direction"
#define GPIO_ACTIVELOW GPIO_ROOT "/gpio%d/active_low"
#define GPIO_VALUE     GPIO_ROOT "/gpio%d/value"
#define GPIO_EDGE      GPIO_ROOT "/gpio%d/edge"

/**
 * A structure describing a GPIO with configuration.
 */
struct gpio {
	/* the GPIO number */
	unsigned int gpio;
	/* GPIO configuration as specified by GPIOF_* */
	unsigned int flags;
	/* file descriptor of /sys/class/gpio/gpioXY/value */
	int fd_value;
	/* file descriptor of /sys/class/gpio/gpioXY/active_low */
	int fd_active_low;
	/* file descriptor of /sys/class/gpio/gpioXY/direction */
	int fd_direction;
	/* file descriptor of /sys/class/gpio/gpioXY/edge */
	int fd_edge;
	/* a literal description string of this GPIO */
	const char *label;
};

/**
 * Internal helpers
 */
int gpio_fd_open(const char *format, unsigned int gpio, int flags);
ssize_t gpio_fd_read(int fd, void *buf, size_t count);
ssize_t gpio_fd_write(int fd, const void *buf, size_t count);
int ugpio_fd_close(int fd);

ssize_t gpio_read(unsigned int gpio, const char *key, char *buf, size_t count);
int gpio_write(unsigned int gpio, const char *key, const char *buf, size_t count);
int gpio_check(unsigned int gpio, const char *key);

#endif  /* _UGPIO_INTERNAL_H_ */
