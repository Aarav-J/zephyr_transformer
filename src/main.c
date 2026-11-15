/*
 * zephyr_transformer
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>

int main(void)
{
	printf("zephyr_transformer booted on %s\n", CONFIG_BOARD_TARGET);

	return 0;
}
