#include "functions.h"


void twi_master_init(void)
{
    ret_code_t err_code;
    const nrf_drv_twi_config_t config =
    {
       .scl                = MBED_SCL,
       .sda                = MBED_SDA,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH
    };

    err_code = nrf_drv_twi_init(&m_twi_master, &config, NULL, NULL);
    APP_ERROR_CHECK(err_code);
    
    nrf_drv_twi_enable(&m_twi_master);
}

 ret_code_t register_write(uint8_t device_addr ,uint8_t reg_addr, uint8_t * p_tx_data, uint8_t bytes)
{
    ret_code_t ret_code;
    
    uint8_t tx_data[bytes+1];
    
    for(uint8_t i = 0 ; i<bytes ; i++) 
    {
        tx_data[i+1] = p_tx_data[i];
    }   
 //   memcpy(tx_data+1,p_data,bytes);
    tx_data[0] = reg_addr;
    
    ret_code = nrf_drv_twi_tx(&m_twi_master, device_addr, tx_data, sizeof(tx_data), false);
    
    return ret_code;
}

 ret_code_t register_read( uint8_t device_addr, uint8_t reg_addr,  uint8_t * p_rx_data, uint32_t bytes)
{   
    ret_code_t ret_code;
    
    ret_code = nrf_drv_twi_tx(&m_twi_master,device_addr, &reg_addr,1,false);
    
    if(ret_code != NRF_SUCCESS)
    {
        return ret_code;
    }
    
    ret_code = nrf_drv_twi_rx(&m_twi_master, device_addr, p_rx_data, bytes);
    
    return ret_code;
}

void MMA7660_set_mode()
{
    uint32_t err_code;
    uint8_t tx_data[1] = {0x01};
    
    err_code = register_write(MMA7660_ADDR,0x07U,tx_data,0x01);
    APP_ERROR_CHECK(err_code);
}

/**
 * @brief Function for casting 6 bit uint to 6 bit int.
 *
 */
__STATIC_INLINE void int_to_uint(int8_t * put, uint8_t data)
{
    if (!(data & MMA7660_FAILURE_FLAG))     //6th bit is failure flag - we cannot read sample
    {
        *put = (int8_t)(data << 2) / 4;
    }
}

void MMA7660_read_acc_data(int8_t * x, int8_t * y ,int8_t * z)
{
    uint32_t err_code;
    uint8_t rx_data[3] = {0,0,0};
        
    err_code = register_read(MMA7660_ADDR,0x00,rx_data,3);
    APP_ERROR_CHECK(err_code);
    
    int_to_uint(x,rx_data[0]);
    int_to_uint(y,rx_data[1]);
    int_to_uint(z,rx_data[2]);
}

