#include <mike/tty/tty.h>

void _kernel_init() {

}

void _kernel_main(void* info_table) {
    tty_set_theme(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
    tty_put_str("Hello kernel world!\n");
}
