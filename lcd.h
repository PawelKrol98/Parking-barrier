/******************************************************************************
 * This file is a part of the SM2 Tutorial (C).                               *                                                 *
 ******************************************************************************/

/**
 * @file lcd1602.h
 * @author Koryciak
 * @date Sep 2020
 * @brief File containing enums, structures and declarations for LCD 2x16.
 * @ver 0.1
 */
#ifndef LCD_H
#define LCD_H

#include "i2c.h"
#include "utils.h"

/**
 * @brief LCD1602 initialization.
 */
void LCD1602_Init(void);
/**
 * @brief Print on the display.
 *
 * @param String to display.
 */
void LCD1602_Print(const char *str);
/**
 * @brief Clear whole display.
 */
void LCD1602_ClearAll(void);
/**
 * @brief Set cursor on display.
 *
 * @param Column.
 * @param Row.
 */
void LCD1602_SetCursor(uint8_t col, uint8_t row);
/**
 * @brief Backlight turn on/off.
 *
 * @param State of the backlight.
 */
void LCD1602_Backlight(uint8_t state);

#endif  /* LCD_H */
