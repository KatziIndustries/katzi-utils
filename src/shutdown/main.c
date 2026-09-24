#include <unistd.h>
#include <sys/reboot.h>
#include <linux/reboot.h>
#include <stdio.h>

int main(void)
{
    sync();

    if (reboot(LINUX_REBOOT_CMD_POWER_OFF) == -1) {
        perror("shutdown");
        return 1;
    }

    return 0;
}