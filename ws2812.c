#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "ws2812.pio.h"

#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7
#define tempo 100
#define botao_pin_a 5
#define botao_pin_b 6
#define led_pin_red 13
#define led_pin_green 11
#define led_pin_blue 12

// Variáveis globais
static volatile uint a = 0;
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)

// Buffer para armazenar quais LEDs estão ligados matriz 5x5
bool led_buffer0[NUM_PIXELS] = {
    0, 1, 1, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0
};
bool led_buffer1[NUM_PIXELS] = {
    0, 0, 1, 0, 0, 
    0, 0, 1, 0, 0, 
    0, 0, 1, 0, 0, 
    0, 1, 1, 0, 0, 
    0, 0, 1, 0, 0
};
bool led_buffer2[NUM_PIXELS] = {
    0, 1, 1, 1, 0, 
    0, 1, 0, 0, 0, 
    0, 0, 1, 0, 0, 
    0, 0, 0, 1, 0, 
    0, 1, 1, 1, 0
};bool led_buffer3[NUM_PIXELS] = {
    0, 1, 1, 1, 0, 
    0, 0, 0, 1, 0, 
    0, 1, 1, 1, 0, 
    0, 0, 0, 1, 0, 
    0, 1, 1, 1, 0
};bool led_buffer4[NUM_PIXELS] = {
    0, 1, 0, 0, 0, 
    0, 0, 0, 1, 0, 
    0, 1, 1, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 0, 1, 0
};bool led_buffer5[NUM_PIXELS] = {
    0, 1, 1, 1, 0, 
    0, 0, 0, 1, 0, 
    0, 1, 1, 1, 0, 
    0, 1, 0, 0, 0, 
    0, 1, 1, 1, 0
};bool led_buffer6[NUM_PIXELS] = {
    0, 1, 1, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0, 
    0, 1, 0, 0, 0, 
    0, 1, 1, 1, 0
};bool led_buffer7[NUM_PIXELS] = {
    0, 1, 0, 0, 0, 
    0, 0, 0, 1, 0, 
    0, 1, 0, 0, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0
};bool led_buffer8[NUM_PIXELS] = {
    0, 1, 1, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0
};bool led_buffer9[NUM_PIXELS] = {
    0, 1, 0, 0, 0, 
    0, 0, 0, 1, 0, 
    0, 1, 1, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0
};

static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}


void set_one_led(uint8_t r, uint8_t g, uint8_t b, bool led_buffer[NUM_PIXELS])
{
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);

    // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (led_buffer[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
}

//função para ligar o led de acordo com o valor de a
void ligar_led(void)
{
    switch (a)
    {
    case 0:
        set_one_led(100, 0, 0, led_buffer0);
        break;
    case 1:
        set_one_led(0, 100, 0, led_buffer1);
        break;
    case 2:
        set_one_led(0, 0, 100, led_buffer2);
        break;
    case 3:
        set_one_led(0, 100, 100, led_buffer3);
        break;
    case 4:
        set_one_led(100, 100, 0, led_buffer4);
        break;
    case 5:
        set_one_led(100, 0, 100, led_buffer5);
        break;
    case 6:
        set_one_led(100, 100, 100, led_buffer6);
        break;
    case 7:
        set_one_led(100, 0, 0, led_buffer7);
        break;
    case 8:
        set_one_led(0, 100, 0, led_buffer8);
        break;
    case 9:
        set_one_led(0, 0, 100, led_buffer9);
        break;
    default:
        break;
    }
}

//evento de interrupção para decrementar o valor do led
void gpio_irq_handler1(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    // Verifica se passou tempo suficiente desde o último evento
    if (current_time - last_time > 200000) // 200 ms de debouncing
    {
        last_time = current_time; // Atualiza o tempo do último evento
        
        if (a>0)
        {
            printf("A = %d\n", a);
            a--;
            printf("Mudanca de Estado do Led. A = %d\n", a);
        }
    }
    ligar_led();
}

//evento de interrupção para incrementar o valor do led
void gpio_irq_handler2(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    // Verifica se passou tempo suficiente desde o último evento
    if (current_time - last_time > 200000) // 200 ms de debouncing
    {
        last_time = current_time; // Atualiza o tempo do último evento
        
        if (a<9)
        {
            printf("A = %d\n", a);
            a++;
            printf("Mudanca de Estado do Led. A = %d\n", a);
        }
    }
    
    ligar_led();
}

void gpio_callback(uint gpio, uint32_t events) {
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    if (current_time - last_time > 200000) { // Debounce de 200ms
        last_time = current_time;
        // Verifica qual pino disparou a interrupção
        if (gpio == botao_pin_a) {
            // Incrementa
            if (a < 9) {
                printf("A = %d\n", a);
                a++;
                printf("Mudanca de Estado do Led. A = %d\n", a);
            }
        } else if (gpio == botao_pin_b) {
            // Decrementa
            if (a > 0) {
                printf("A = %d\n", a);
                a--;
                printf("Mudanca de Estado do Led. A = %d\n", a);
            }
        }
        ligar_led();
    }
}


int main()
{
    // inicializações  
    stdio_init_all();

    gpio_init(botao_pin_a);
    gpio_set_dir(botao_pin_a, GPIO_IN);
    gpio_pull_up(botao_pin_a);

    gpio_init(botao_pin_b);
    gpio_set_dir(botao_pin_b, GPIO_IN);
    gpio_pull_up(botao_pin_b);

    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);

    gpio_init(led_pin_green);
    gpio_set_dir(led_pin_green, GPIO_OUT);

    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    ligar_led();

    //configuração de interrupção
     gpio_set_irq_enabled_with_callback(botao_pin_a, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
     gpio_set_irq_enabled_with_callback(botao_pin_b, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    
    while (true)
    {
       gpio_put(led_pin_red, true);
       sleep_ms(tempo);
       gpio_put(led_pin_red, false);
       sleep_ms(tempo);
       gpio_put(led_pin_red, true);
       sleep_ms(tempo);
       gpio_put(led_pin_red, false);
       sleep_ms(tempo);
       gpio_put(led_pin_red, true);
       sleep_ms(tempo);
       gpio_put(led_pin_red, false);
       sleep_ms(tempo);
       gpio_put(led_pin_red, true);
       sleep_ms(tempo);
       gpio_put(led_pin_red, false);
       sleep_ms(tempo);
       gpio_put(led_pin_red, true);
       sleep_ms(tempo);
       gpio_put(led_pin_red, false);
       sleep_ms(tempo);
    }

    return 0;
}
