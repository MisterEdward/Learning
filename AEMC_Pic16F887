#include <xc.h>
#include <stdio.h>

// Configuration bits
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = ON
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 4000000
#define LM35_PIN     RA0        // LM35 on RA0/AN0
#define HIH_PIN      RA1        // HIH-5030 on RA1/AN1
#define LDR_PIN      RA2        // LDR on RA2/AN2
#define LM35_CHANNEL 0          // Channel 0 for AN0
#define HIH_CHANNEL  1          // Channel 1 for AN1
#define LDR_CHANNEL  2          // Channel 2 for AN2

// New pins for buzzer and button
#define BUZZER_PIN  RA3         // Buzzer on RA3
#define BUTTON_PIN  RA4         // Button on RA4 with pull-up resistor

// SHT11 pins - Move from RB0/RB1 to RC2/RC3
#define SHT_DATA_PIN     RC3           // Data on RC3
#define SHT_SCK_PIN      RC2           // Clock on RC2
#define SHT_DATA_DIR     TRISC3
#define SHT_SCK_DIR      TRISC2

// SHT11 commands
#define SHT_CMD_MEASURE_TEMP     0x03
#define SHT_CMD_MEASURE_HUMID    0x05
#define SHT_CMD_READ_STATUS      0x07
#define SHT_CMD_WRITE_STATUS     0x06
#define SHT_CMD_RESET            0x1E

// LCD pins
#define RS RC0    // Register Select on RC0
#define EN RC1    // Enable on RC1
// D4-D7 are connected to RD4-RD7

// Function prototypes
void setupPins(void);
void LCD_Command(unsigned char cmd);
void LCD_Init(void);
void LCD_Char(unsigned char data);
void LCD_String(const char *str);
unsigned int readADC(unsigned char channel);
void setupADC(void);
void LCD_WriteTemp(float temp);
void LCD_WriteDebug(unsigned int value);
void SHT_Init(void);
void SHT_ConnectionReset(void);
void SHT_TransmissionStart(void);
unsigned char SHT_SendByte(unsigned char value);
unsigned char SHT_ReadByte(unsigned char sendAck);
unsigned char SHT_Measure(unsigned char cmd, unsigned int *value);
float SHT_CalcTemperature(unsigned int rawValue);
float SHT_CalcHumidity(unsigned int rawValue, float temperature);
float getLM35Temperature(void);
float getHIH5030Humidity(void);
float getLDRValue(void);  // Add prototype for LDR function

// New function prototypes for alarm functionality
unsigned char isButtonPressed(void);
void soundBuzzer(unsigned int duration_ms);
void displayAlarmCountdown(unsigned int seconds);

// New function prototype for loading bar
void displayLoadingBar(unsigned int duration_ms);

void setupPins() {
    TRISC0 = 0;    // RS pin as output
    TRISC1 = 0;    // EN pin as output
    TRISC2 = 0;    // SHT SCK as output
    TRISC3 = 1;    // SHT DATA as input initially
    TRISD = 0x0F;  // Upper nibble as output, lower as input
    
    TRISA3 = 0;    // Buzzer as output
    TRISA4 = 1;    // Button as input
    
    PORTA &= ~(1 << 3);  // Buzzer off initially
    
    PORTC = 0;     // Clear port C
    PORTD = 0;     // Clear port D
}

void LCD_Command(unsigned char cmd) {
    RS = 0;                    // Command mode
    PORTD &= 0x0F;            // Clear upper nibble
    PORTD |= (cmd & 0xF0);    // Send upper nibble
    
    EN = 1;                   // Enable pulse
    __delay_us(5);
    EN = 0;
    __delay_us(5);
    
    PORTD &= 0x0F;            // Clear upper nibble
    PORTD |= ((cmd << 4) & 0xF0); // Send lower nibble
    
    EN = 1;                   // Enable pulse
    __delay_us(5);
    EN = 0;
    __delay_us(5);
    
    __delay_ms(2);            // Wait for command to execute
}

void LCD_Init() {
    __delay_ms(20);           // Wait for power up
    
    RS = 0;
    PORTD &= 0x0F;
    PORTD |= 0x30;           // Function set
    EN = 1;
    __delay_us(5);
    EN = 0;
    __delay_ms(5);
    
    PORTD &= 0x0F;
    PORTD |= 0x30;           // Function set
    EN = 1;
    __delay_us(5);
    EN = 0;
    __delay_ms(1);
    
    PORTD &= 0x0F;
    PORTD |= 0x30;           // Function set
    EN = 1;
    __delay_us(5);
    EN = 0;
    __delay_ms(1);
    
    PORTD &= 0x0F;
    PORTD |= 0x20;           // Set 4-bit mode
    EN = 1;
    __delay_us(5);
    EN = 0;
    __delay_ms(1);
    
    LCD_Command(0x28);        // 2 lines, 5x7 matrix
    LCD_Command(0x0C);        // Display ON, cursor OFF
    LCD_Command(0x01);        // Clear display
    LCD_Command(0x06);        // Increment cursor
}

void LCD_Char(unsigned char data) {
    RS = 1;                    // Data mode
    PORTD &= 0x0F;            // Clear upper nibble
    PORTD |= (data & 0xF0);   // Send upper nibble
    
    EN = 1;
    __delay_us(5);
    EN = 0;
    __delay_us(5);
    
    PORTD &= 0x0F;
    PORTD |= ((data << 4) & 0xF0);
    
    EN = 1;
    __delay_us(5);
    EN = 0;
    __delay_us(5);
    
    __delay_ms(2);
}

void LCD_String(const char *str) {
    while(*str) LCD_Char(*str++);
}

// Function to read LM35
unsigned int readADC(unsigned char channel) {
    // Proper channel selection
    ADCON0 &= 0b11000011;       // Clear channel selection bits (bits 2-5)
    ADCON0 |= (channel << 2);   // Select desired channel
    __delay_us(20);             // Acquisition time
    
    // Debug - make sure we're setting channels correctly
    if(channel == LM35_CHANNEL)
        ADCON0bits.CHS = 0;     // Force channel 0 for LM35
    else if(channel == HIH_CHANNEL)
        ADCON0bits.CHS = 1;     // Force channel 1 for HIH
    
    ADCON0bits.GO = 1;          // Start conversion
    while(ADCON0bits.GO);       // Wait for conversion
    return ((ADRESH << 8) + ADRESL);   // Return result
}

// Basic ADC setup for LM35
void setupADC() {
    // Configure analog pins properly
    TRISA |= 0x07;              // Set RA0, RA1, and RA2 as inputs
    ANSEL |= 0x07;              // Set AN0, AN1, and AN2 as analog
    ANSELH = 0x00;              // No additional analog pins needed
    
    ADCON1 = 0x80;              // Right justified, Vref is VDD
    ADCON0 = 0x01;              // Enable ADC, select channel 0
    __delay_us(100);            // Wait for ADC to stabilize
}

// Add this new function for number conversion
void LCD_WriteTemp(float temp) {
    char buffer[8];
    int integer = (int)temp;
    int decimal = (int)((temp - integer) * 10);
    sprintf(buffer, "%d.%d C", integer, decimal);
    LCD_String(buffer);
}

// Add debug function
void LCD_WriteDebug(unsigned int value) {
    char buffer[10];
    sprintf(buffer, "0x%04X", value);
    LCD_String(buffer);
}

// SHT11 functions
void SHT_Init(void) {
    // Configure pins
    SHT_SCK_DIR = 0;           // Clock as output
    SHT_DATA_DIR = 1;          // Data as input initially
    
    // Set initial states
    SHT_SCK_PIN = 0;           // Clock low
    
    // Add a stronger external pull-up by briefly setting pin high
    SHT_DATA_DIR = 0;          // Make DATA an output
    SHT_DATA_PIN = 1;          // Set DATA high
    __delay_ms(10);            // Brief delay
    SHT_DATA_DIR = 1;          // Make DATA an input again
    
    __delay_ms(100);           // Stabilization delay
    
    // Connection reset and soft reset
    SHT_ConnectionReset();
    SHT_TransmissionStart();
    SHT_SendByte(SHT_CMD_RESET);
    __delay_ms(20);
    
    // Check if communication is working with a STATUS command
    SHT_TransmissionStart();
    if(!SHT_SendByte(SHT_CMD_READ_STATUS)) {
        // If we can't communicate, try again with longer delays
        __delay_ms(50);
        SHT_ConnectionReset();
        __delay_ms(50);
    }
}

void SHT_ConnectionReset(void) {
    // Set DATA as output momentarily
    SHT_DATA_DIR = 0;
    SHT_DATA_PIN = 1;
    
    // Toggle SCK 9+ times with DATA high to reset interface
    for(unsigned char i = 0; i < 12; i++) {  // Extra toggles for safety
        SHT_SCK_PIN = 0;
        __delay_us(10);
        SHT_SCK_PIN = 1;
        __delay_us(10);
    }
    
    SHT_SCK_PIN = 0;
    __delay_ms(10);  // Extra delay
}

void SHT_TransmissionStart(void) {
    // Initial state
    SHT_DATA_DIR = 0;          // DATA as output
    SHT_SCK_PIN = 0;           // SCK low
    SHT_DATA_PIN = 1;          // DATA high
    __delay_us(10);
    
    SHT_SCK_PIN = 1;           // SCK high
    __delay_us(10);
    SHT_DATA_PIN = 0;          // DATA low while SCK high
    __delay_us(10);
    SHT_SCK_PIN = 0;           // SCK low
    __delay_us(10);
    SHT_SCK_PIN = 1;           // SCK high
    __delay_us(10);
    SHT_DATA_PIN = 1;          // DATA high while SCK high
    __delay_us(10);
    SHT_SCK_PIN = 0;           // SCK low
    __delay_us(40);            // Extended delay
}

unsigned char SHT_SendByte(unsigned char value) {
    unsigned char ack;
    
    SHT_DATA_DIR = 0;          // DATA as output
    
    // Send 8 bits MSB first
    for(unsigned char i = 0; i < 8; i++) {
        SHT_DATA_PIN = (value & 0x80) ? 1 : 0;  // Set bit
        value <<= 1;
        __delay_us(2);
        
        SHT_SCK_PIN = 1;       // SCK high - data valid
        __delay_us(5);
        SHT_SCK_PIN = 0;       // SCK low
        __delay_us(2);
    }
    
    // Read ACK
    SHT_DATA_DIR = 1;          // DATA as input
    __delay_us(2);
    SHT_SCK_PIN = 1;           // SCK high
    __delay_us(5);
    ack = !SHT_DATA_PIN;       // ACK is low
    SHT_SCK_PIN = 0;           // SCK low
    
    return ack;
}

unsigned char SHT_ReadByte(unsigned char sendAck) {
    unsigned char value = 0;
    
    SHT_DATA_DIR = 1;          // DATA as input
    
    // Read 8 bits
    for(unsigned char i = 0; i < 8; i++) {
        value <<= 1;
        __delay_us(1);
        
        SHT_SCK_PIN = 1;       // SCK high - read data
        __delay_us(2);
        
        if(SHT_DATA_PIN)       // Read bit
            value |= 0x01;
        
        SHT_SCK_PIN = 0;       // SCK low
        __delay_us(2);
    }
    
    // Send ACK/NACK
    SHT_DATA_DIR = 0;          // DATA as output
    SHT_DATA_PIN = !sendAck;   // ACK: DATA low, NACK: DATA high
    __delay_us(2);
    
    SHT_SCK_PIN = 1;           // SCK high
    __delay_us(5);
    SHT_SCK_PIN = 0;           // SCK low
    __delay_us(2);
    
    SHT_DATA_DIR = 1;          // DATA as input
    return value;
}

unsigned char SHT_Measure(unsigned char cmd, unsigned int *value) {
    unsigned char msb, lsb;
    unsigned char error = 0;
    unsigned char timeout = 0;
    
    // Start transmission
    SHT_TransmissionStart();
    
    // Send command
    if(!SHT_SendByte(cmd))
        return 1;      // Error: no ACK
    
    // Wait for measurement to complete (DATA line goes low)
    SHT_DATA_DIR = 1;  // DATA as input
    while(SHT_DATA_PIN && ++timeout < 100)
        __delay_ms(10);
    
    if(timeout >= 100)
        return 2;      // Error: timeout
    
    // Read MSB
    msb = SHT_ReadByte(1);     // ACK
    
    // Read LSB
    lsb = SHT_ReadByte(0);     // NACK
    
    // Combine bytes
    *value = (msb << 8) | lsb;
    
    return 0;  // Success
}

float SHT_CalcTemperature(unsigned int rawValue) {
    // T = d1 + d2 * rawValue
    // For 5V: d1 = -40.1, d2 = 0.01
    return -40.1f + 0.01f * rawValue;
}

float SHT_CalcHumidity(unsigned int rawValue, float temperature) {
    float rh_linear;
    float rh_true;
    
    // For 12-bit resolution: RH = -4 + 0.0405*rawValue - 0.0000028*(rawValue^2)
    rh_linear = -4.0f + 0.0405f * rawValue - 0.0000028f * rawValue * rawValue;
    
    // Temperature compensation: RHtrue = (T-25)*(0.01+0.00008*rawValue) + RHlinear
    rh_true = (temperature - 25.0f) * (0.01f + 0.00008f * rawValue) + rh_linear;
    
    // Clamp to valid range
    if(rh_true > 100.0f) rh_true = 100.0f;
    if(rh_true < 0.0f) rh_true = 0.0f;
    
    return rh_true - 2;
}

// Function to read LM35 with proper conversion
float getLM35Temperature(void) {
    unsigned int adc_value = readADC(LM35_CHANNEL);
    float voltage = (adc_value * 5.0) / 1024.0;
    return voltage * 100.0;  // Convert to Celsius (10mV/°C)
}

float getHIH5030Humidity(void) {
    unsigned int adc_value = readADC(HIH_CHANNEL);
    float voltage = (adc_value * 5.0) / 1024.0;
    // HIH-5030 formula: RH = (Vout/Vsupply - 0.1515)/0.00636
    float humid = (voltage / 5.0 - 0.1515) / 0.00636;
    
    // Temperature compensation could be added here if needed
    // HIH-5030 true RH = (Sensor RH)/(1.0546 - 0.00216*T), where T is in °C
    
    // Clamp to valid range
    if(humid > 100.0f) humid = 100.0f;
    if(humid < 0.0f) humid = 0.0f;
    
    return humid;
}

// Function to read and process LDR value
float getLDRValue(void) {
    unsigned int adc_value = readADC(LDR_CHANNEL);
    
    // Calculate light level percentage (0-100%)
    // The pull-up configuration means higher ADC = more light
    float light_percent = (adc_value * 100.0) / 1023.0;
    
    return light_percent;
}

// New functions for alarm functionality
unsigned char isButtonPressed(void) {
    static unsigned char previous = 1;  // Start with not pressed
    unsigned char current = BUTTON_PIN;
    unsigned char result = 0;
    
    // Detect falling edge (press) considering pull-up resistor
    if (previous == 1 && current == 0) {
        result = 1;         // Button was just pressed
        __delay_ms(20);     // Debounce delay
    }
    
    previous = current;     // Update state
    return result;
}

void soundBuzzer(unsigned int duration_ms) {
    // Turn buzzer on
    BUZZER_PIN = 1;
    
    // Use fixed delay in loop
    for (unsigned int i = 0; i < duration_ms; i++) {
        __delay_ms(1);  // 1ms constant delay
    }
    
    // Turn buzzer off
    BUZZER_PIN = 0;
}

void displayAlarmCountdown(unsigned int seconds) {
    LCD_Command(0x01);        // Clear display
    LCD_Command(0x80);        // First line
    LCD_String("Alarm: ");
    
    char buffer[10];
    unsigned int mins = seconds / 60;
    unsigned int secs = seconds % 60;
    sprintf(buffer, "%02u:%02u", mins, secs);
    LCD_String(buffer);
    
    LCD_Command(0xC0);        // Second line
    LCD_String("+ Press for 15s");
}

// Function to display loading bar during startup
void displayLoadingBar(unsigned int duration_ms) {
    const unsigned int STEP_MS = 100;  // Constant step time (100ms)
    unsigned int steps = duration_ms / STEP_MS;
    unsigned int current_step = 0;
    unsigned int bar_width = 16;  // 16 character LCD width
    
    LCD_Command(0x01);           // Clear display
    LCD_Command(0x80);           // First line
    LCD_String("Initializing...");
    
    while (current_step < steps) {
        // Calculate progress percentage
        unsigned int progress = (current_step * 100) / steps;
        // Calculate bar characters to show (16 chars max)
        unsigned int chars_to_show = (current_step * bar_width) / steps;
        
        // Position cursor to second line
        LCD_Command(0xC0);
        
        // Display progress bar
        for (unsigned int i = 0; i < chars_to_show; i++) {
            LCD_Char(0xFF);  // Solid block character
        }
        
        // Fill the rest with spaces
        for (unsigned int i = chars_to_show; i < bar_width; i++) {
            LCD_Char(' ');
        }
        
        // Use fixed delay value - 100 iterations of 1ms each
        for(unsigned int i = 0; i < 100; i++) {
            __delay_ms(1);  // 1ms constant delay
        }
        current_step++;
    }
}

void main(void) {
    // Set up internal oscillator to 4MHz
    OSCCON = 0x60;
    while(!OSCCONbits.HTS);    // Wait for stable clock
    
    setupPins();
    LCD_Init();
    setupADC();
    SHT_Init();
    
    // Display initializing with loading bar
    displayLoadingBar(5000);  // 5 second loading bar
    
    LCD_Command(0x01);
    LCD_Command(0x80);
    LCD_String("System Ready");
    __delay_ms(1000);
    
    unsigned char display_mode = 0;  // 0 = analog, 1 = digital, 2 = light
    unsigned int alarm_seconds = 0;  // Alarm countdown in seconds
    unsigned char alarm_active = 0;  // Flag for alarm mode
    
    while(1) {
        // Check button
        if(isButtonPressed()) {
            if(alarm_active) {
                // Add 15 seconds if alarm is already running
                alarm_seconds += 15;
            } else {
                // Start alarm with 15 seconds
                alarm_seconds = 15;
                alarm_active = 1;
            }
        }
        
        // Process alarm or display sensors
        if(alarm_active) {
            // Display countdown
            displayAlarmCountdown(alarm_seconds);
            
            // Wait one second
            __delay_ms(1000);
            
            // Decrement counter
            alarm_seconds--;
            
            // Check if alarm is done
            if(alarm_seconds == 0) {
                // Sound buzzer
                soundBuzzer(1000);  // 1 second buzz
                
                // Return to regular display mode
                alarm_active = 0;
            }
        } else {
            // Normal sensor display mode
            // Read all sensor values first
            float temp_lm35 = getLM35Temperature();
            float humid_hih = getHIH5030Humidity();
            float light_ldr = getLDRValue();
            
            // Read SHT11 digital sensor
            unsigned int raw_temp = 0, raw_humid = 0;
            unsigned char error_temp = 0, error_humid = 0;
            float temp_sht = 0.0, humid_sht = 0.0;
            
            error_temp = SHT_Measure(SHT_CMD_MEASURE_TEMP, &raw_temp);
            if(!error_temp) {
                temp_sht = SHT_CalcTemperature(raw_temp);
                
                __delay_ms(100);
                error_humid = SHT_Measure(SHT_CMD_MEASURE_HUMID, &raw_humid);
                if(!error_humid) {
                    humid_sht = SHT_CalcHumidity(raw_humid, temp_sht);
                }
            }
            
            // Display analog or digital sensors based on mode
            if(display_mode == 0) {
                // Show analog sensors
                LCD_Command(0x01);  // Clear display
                __delay_ms(5);      // Short delay after clearing
                
                // First line - LM35 temperature
                LCD_Command(0x80);
                LCD_String("LM35 T: ");
                LCD_WriteTemp(temp_lm35);
                
                // Second line - HIH-5030 humidity
                LCD_Command(0xC0);
                LCD_String("HIH H: ");
                char buffer[6];
                sprintf(buffer, "%d%%", (int)(humid_hih + 0.5f));
                LCD_String(buffer);
                
                __delay_ms(2000);  // Show for 2 seconds
                
                // Clear display and add brief blank period
                LCD_Command(0x01);
                __delay_ms(200);   // Brief blank period for visual separation
                
                display_mode = 1;  // Switch to digital sensors
            } 
            else if(display_mode == 1) {
                // Show digital sensors
                LCD_Command(0x01);  // Clear display
                __delay_ms(5);      // Short delay after clearing
                
                // First line - SHT11 temperature
                LCD_Command(0x80);
                LCD_String("SHT11 T: ");
                if(!error_temp) {
                    LCD_WriteTemp(temp_sht);
                } else {
                    LCD_String("Error");
                }
                
                // Second line - SHT11 humidity
                LCD_Command(0xC0);
                LCD_String("SHT11 H: ");
                if(!error_humid) {
                    char buffer[6];
                    sprintf(buffer, "%d%%", (int)(humid_sht + 0.5f));
                    LCD_String(buffer);
                } else {
                    LCD_String("Error");
                }
                
                __delay_ms(2000);  // Show for 2 seconds
                
                // Clear display and add brief blank period
                LCD_Command(0x01);
                __delay_ms(200);   // Brief blank period for visual separation
                
                display_mode = 2;  // Switch to light sensor
            }
            else {
                // Show LDR light sensor
                LCD_Command(0x01);
                __delay_ms(5);
                
                // First line - Light level
                LCD_Command(0x80);
                LCD_String("Light Level:");
                
                // Second line - Percentage
                LCD_Command(0xC0);
                char buffer[10];
                sprintf(buffer, "%d%%", (int)(light_ldr + 0.5f));
                LCD_String(buffer);
                
                __delay_ms(2000);
                LCD_Command(0x01);
                __delay_ms(200);
                display_mode = 0;  // Back to analog sensors
            }
        }
    }
}
