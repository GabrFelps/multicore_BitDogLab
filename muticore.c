#include <stdio.h>
#include "pico/stdlib.h"

//BIBLIOTECAS PRINCIPAIS
#include "pico/multicore.h"

//pinos gpio
#define LED_R 13
#define BTN_A 5

int button_state = 0;

void core1_loop(){}

void setup(){
    stdio_init_all();
    gpio_init(LED_R);
    gpio_init(BTN_A);

    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_set_dir(BTN_A, GPIO_IN);

    gpio_pull_up(BTN_A);

    multicore_reset_core1();
    multicore_launch_core1(core1_loop);
    
}
int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
