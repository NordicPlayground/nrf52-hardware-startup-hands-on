#Hardware Startup London – Hands On

1.	Download the example zip.
2.	Extract the example zip to <SKD-folder>/examples/peripheral. 
3.	Open the project found in ble_app_uart/pca10040/s132/arm5_no_packs in Keil 
4.	Edit the DEVICE_NAME from “Nordic_UART” to a name of your choosing, but with the same length. 
5.	Build the application.
6.	Flash the S132 SoftDevice and the application to your nRF52 DK.
7.	Open the nRF Toolbox App, click the UART Tool and then connect. Your device should show up under “Available Devices” with the name you gave it earlier.  

##TASK 1 – RGB LED 

**Scope:** In this task we will send commands to the nRF52 DK over the Nordic UART Service(NUS) and based on these commands turn on and off the RGB LED on the mBED Application Shield.  

1.	Find the uart_command_t enum in the functions.h header files and edit “COMMAND_1” to “RED_ON” and “COMMAND_2” to “RED_OFF”.
2.	In the nus_data_handler(), edit the “COMMAND1” to “REDON”. This is the string that will be compared to the string received from the NUS service.
3.	Set command equal to RED_ON, i.e. command = RED_ON;
4.	In the uart_command_handler, edit the “COMMAND_1” case in the switch-case to “RED_ON” and call the function rgb_led_set( RED).
5.	In the uart_command_handler, edit the “COMMAND_2” case in the switch-case to “RED_OFF” and call the function rgb_led_clear( RED).
6.	Build and download the code to the nRF52 DK Board
7.	Open the nRF Toolbox App, click the UART Tool and then connect. Your device should show up under “Available Devices” with the name you gave it earlier.  
8.	Check the log and verify that your smartphone connected to the device and that service discovery has been performed. 
9.	Hit “EDIT” in the upper right corner of the app and then hit one of the square buttons to configure it. 
10.	Enter “REDON” as command, choose a suitable icon and press OK. Press another button, enter “REDOFF” as a command, choose a suitable icon and then hit OK. Press “DONE” in the upper right corner to complete the configuration. 
11.	Pressing the button configured as “REDON”, should turn on the red LED in the RGB LED and pressing the “REDOFF” button should turn it off. 
12.	Add similar commands for the Blue and Green LED.



##TASK 2 – POTENTIOMETER & SAADC

**Scope:** In this task we’ll set up an application timer to trigger the Single Approximation ADC (SAADC) of the nRF52 to sample the analog input of potentiometer 1 on the mBED application shield and send the value to your smartphone using the NUS service. 

1.	Add the “START_ADC” and “STOP_ADC” commands to the uart_command_t enum. 
2.	Add two else if-statements in nus_data_handler() to check for the “ADCON” and “ADCOFF” commands in the uart string, and set the corresponding command.
3.	Add APP_TIMER_DEF(m_adc_timer_id); to the top of main.c to create a timer ID.
4.	In init_timers() use the app_timer_create() - function to create an application timer instance with the ID from step 5. Hint: See the Application Timer API on Infocenter, found here. You can also take a look at the Application Timer tutorial on DevZone, found here.
5.	Call nrf_drv_saadc_sample() in the timeout_handler specified in app_timer_create()  to trigger the SAADC to sample the analog input connected to the potentiometer. 
6.	Initialize the SAADC driver by adding the saadc_init() function in main().
7.	Use the ble_nus_string_send() function in saadc_callback() to send the ADC measurement to your smartphone. Hint: Use sprintf() 
8.	In uart_command_handler() , add the two commands from step 1 to the switch case and use the app_timer_start() and app_timer_stop() to start and stop the application timer from triggering the SAADC to sample the analog input.
9.	Build and download the application to the nRF52 DK.
10.	Configure the buttons in the nRF Toolbox app to send the commands from step 2 to the nRF52 DK the same way as in Task 1. 
11.	The nRF52 should start sending the ADC measurements to the smartphone after pressing the button configured to send the “ADCON” command.







##TASK 3 – TWI & ACCELEROMETER (OPTIONAL)
 
**Scope:** In this optional task we’ll use the TWI interface of the nRF52 to communicate with the MMA7660 accelerometer on the mBED Application Shield and send the accelerometer data to your smartphone using the NUS service.

1.	Add “START_ACC” and “STOP_ACC” commands to the uart_command_t enum.
2.	Add two else if-statements in nus_data_handler() to check for the “ACCON” and “ACCOFF” commands in the uart string, and set the corresponding commands.
3.	Add APP_TIMER_DEF(m_acc_timer_id); add the top of main.c to create a timer ID.
4.	In init_timers() use the app_timer_create() - function to create another application timer instance with the ID from step 5. 
5.	Call MMA7660_read_acc_data() in the timeout_handler specified in app_timer_create()  to read the accelerometer data. 
6.	Use the ble_nus_string_send() function in the timeout_handler to send the ADC measurement to your smartphone. Hint: Use sprintf() 
7.	In main(),  call twi_master_init() and MMA7660_set_mode() to initialize the TWI driver and set the MMA7660 in active mode. 
8.	Build and download the application to nRF52 DK
9.	Configure the buttons in the nRF Toolbox app to send the commands from step 2 to the nRF52 DK. 
10.	The nRF52 should start sending the ACC measurements to the smartphone after pressing the button configured to send the “ACCON” command.



