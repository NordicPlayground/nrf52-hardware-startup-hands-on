#include "nrf_drv_twi.h"
#include "app_error.h"
#include "app_util_platform.h"
#include "app_pwm.h"

/* Number of ADC samples in buffer */
#define SAMPLES_IN_BUFFER 1

/* MMA7660 TWI ADDRESS */
#define MMA7660_ADDR (0x98U >> 1)

/*Failure flag for reading from accelerometer. */
#define MMA7660_FAILURE_FLAG (1u << 6)

/* TWI Pins on the MBED Shield */
#define MBED_SCL        27
#define MBED_SDA        26

/* RGB LED Pins on the MBED Shield */
#define RED_LED_PIN     16
#define GREEN_LED_PIN   19
#define BLUE_LED_PIN    20 

/* LED Colors */
#define RED     0
#define BLUE    1
#define GREEN   2


/* Enumeration to hold the commands sent over the Nordic UART Service */
typedef enum {
    COMMAND_1,
    COMMAND_2,
    COMMAND_3,
    NO_COMMAND
} uart_command_t;

static volatile uart_command_t command = NO_COMMAND;

/* Functions */

static const nrf_drv_twi_t m_twi_master = NRF_DRV_TWI_INSTANCE(0);

void MMA7660_read_acc_data(int8_t * x, int8_t * y ,int8_t * z);

void MMA7660_set_mode(void);

 ret_code_t register_read( uint8_t device_addr, uint8_t reg_addr,  uint8_t * p_rx_data, uint32_t bytes);

ret_code_t register_write(uint8_t device_addr ,uint8_t reg_addr, uint8_t * p_tx_data, uint8_t bytes);

void twi_master_init(void);
