/******************************************************************************
 * This file is a part of the SM2 Tutorial (C).                               *                                                 *
 ******************************************************************************/

/**
 * @file i2c.h
 * @author Koryciak
 * @date Sep 2020
 * @brief File containing enums, structures and declarations for I2C.
 * @ver 0.1
 */

#ifndef I2C_H
#define I2C_H
#include "utils.h"

/**
 * @brief I2C initialization.
 */
void I2C_Init(void);
/**
 * @brief I2C write operation.
 *
 * @param Address.
 * @param Data.
 */
uint8_t I2C_Write(uint8_t address, uint8_t data);
	
#endif /* I2C_H */
