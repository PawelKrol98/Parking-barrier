/******************************************************************************
 * This file is a part of the Sysytem Microprocessor Tutorial (C).            *
 ******************************************************************************/

/**
 * @file lcd.c
 * @author Koryciak
 * @date Sep 2020
 * @brief File containing definitions for LCD 2x16.
 * @ver 0.2
 */

#include "lcd.h"
#include "utils.h"

/******************************************************************************\
* Private definitions
\******************************************************************************/
/* LCD functions */
#define LCD_CLEARDISPLAY 		0x01
#define LCD_SETDDRAMADDR 		0x80
#define LCD_FULLLINE				0x40
/* PCF8574 */
#define PCF8574_ADDRESS     0x27 	/* I2C slave device,  PCF8574A=0x3F */ 
/* PCF8574 connections to LCD */
//#define PCF8574_D7 0x80
//#define PCF8574_D6 0x40
//#define PCF8574_D5 0x20
//#define PCF8574_D4 0x10
#define PCF8574_BL 0x08 /* Backlight */
#define PCF8574_EN 0x04 /* Enable bit */
#define PCF8574_RW 0x02 /* Read/Write bit (0 = write) */
#define PCF8574_RS 0x01 /* Register select bit */
/******************************************************************************\
* Private memory declarations
\******************************************************************************/
static uint8_t lcd_backlight = 1;
/******************************************************************************\
* Private prototypes
\******************************************************************************/
void PCF8574_Write(uint8_t data);
void LCD1602_Write4(uint8_t data, uint8_t rs);
void LCD1602_Write8(uint8_t data, uint8_t rs);

void LCD1602_Init(void) {																																		

	I2C_Init();											/* via I2C communication */
	PCF8574_Write(0x00);																										
	DELAY(42);											/* >15ms */
	
	LCD1602_Write8(0x33,0);					/* 4-bit interface */								
	LCD1602_Write8(0x32,0);					/* HD44780U datasheet Figure 24 */
	LCD1602_Write8(0x2C,0);
	LCD1602_Write8(0x08,0);
	LCD1602_Write8(0x01,0);
	LCD1602_Write8(0x0C,0);					/* cursor off, blink off */
}

void LCD1602_SetCursor(uint8_t col, uint8_t row) {
	
	if (row>1) row = 1;   /* prevent from too many rows */
	LCD1602_Write8(LCD_SETDDRAMADDR+col+(LCD_FULLLINE*row),0);
}

void LCD1602_ClearAll(void) {
	
	LCD1602_Write8(LCD_CLEARDISPLAY, 0);
}

void LCD1602_Print(const char *str) {

  uint8_t str_len = 0;

  while (str[str_len] != '\0') {              /* until end of string */
    LCD1602_Write8(str[str_len], 1);
    ++str_len;
  }
}

void LCD1602_Backlight(uint8_t state) {
	
	lcd_backlight = state;				 /* update internal variable */
	PCF8574_Write(0x00);
}
/**
 * @brief Write byte to LCD including backlight info.
 *
 * @param Data to send.
 */
void PCF8574_Write(uint8_t data) {
	
	I2C_Write(PCF8574_ADDRESS, data | (lcd_backlight?PCF8574_BL:0x00));
}
/**
 * @brief Write 4 bits to LCD.
 *
 * @param A lower nibble of the byte.
 * @param Register select.
 */
void LCD1602_Write4(uint8_t data, uint8_t rs) {
	
	PCF8574_Write(((data << 4)&0xF0) | (rs?PCF8574_RS:0x00) | PCF8574_EN);
	PCF8574_Write(((data << 4)&0xF0) | (rs?PCF8574_RS:0x00));
	DELAY(2);
}
/**
 * @brief Write byte to LCD.
 *
 * @param Data to send.
 * @param Register select
 */
void LCD1602_Write8(uint8_t data, uint8_t rs) {
	
	LCD1602_Write4(((data >> 4)&0x0F), rs);
	LCD1602_Write4(( data      &0x0F), rs);
}
