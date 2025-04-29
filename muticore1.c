#include <stdio.h>
#include "pico/stdlib.h"

// Bibliotecas principais
#include "pico/multicore.h"
#include "hardware/irq.h"

// Pinos GPIO
#define LED_R 13
#define BTN_A 5


void core1_loop(){
    while(1){
        gpio_put(LED_R, button_state);
        printf("[CORE 1]: controlando LED...\n");
        sleep_ms(30);
    }
}

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
    setup();
    int button_read_state = 0;

    while (true) {
        button_read_state = !gpio_get(BTN_A);
        multicore_fifo_push_blocking(button_read_state);
        printf("[CORE 0]: Enviando estado do botão...\n");
        sleep_ms(30);
    }
}
