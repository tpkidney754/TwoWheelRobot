#ifndef __LSM9DS1__
#define __LSM9DS1__

#include "includeall.h"

#define LSM9DS1_I2C_FREQ_KHZ             100
#define LSM9DS1_I2C_FAST_FREQ_KHZ        400

#define LSM9DS1_I2C_SDA_SETUP_NS         250
#define LSM9DS1_I2C_SDA_FAST_SETUP_NS    100F

#define LSM9DS1_ACCELGYRO_ADDR           0xD6

#define LSM9DS1_MAG_ADDR                 0x38

// Bus clock is up to 24 Mhz
// OUTDIV4 = 1, therefore the divider is 2. However, I need to make this flexible.
// SDA Max hold time is 3.45 us.

/* ----------------------------------------------------------------------------
   -- Accelerometer/Gyroscope Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Accelerometer/Gyroscope Peripheral Access Layer
 * @{
 */

/** Accelerometer/Gyroscope - Register Layout Typedef */
typedef enum
{
   ACT_THS = 4,
   ACT_DUR,
   INT_GEN_CFG_XL,
   INT_GEN_THS_X_XL,
   INT_GEN_THS_Y_XL,
   INT_GEN_THS_Z_XL,
   INT_GEN_DUR_XL,
   REFERENCE_G,
   INT1_CTRL,
   INT2_CTRL,
   RESERVED0,
   WHO_AM_I,
   CTRL_REG1_G,
   CTRL_REG2_G,
   CTRL_REG3_G,
   ORIENT_CFG_G,
   INT_GEN_SRC_G,
   OUT_TEMP_L,
   OUT_TEMP_H,
   STATUS_REG0,
   OUT_X_L_G,
   OUT_X_H_G,
   OUT_Y_L_G,
   OUT_Y_H_G,
   OUT_Z_L_G,
   OUT_Z_H_G,
   CTRL_REG4,
   CTRL_REG5_XL,
   CTRL_REG6_XL,
   CTRL_REG7_XL,
   CTRL_REG8,
   CTRL_REG9,
   CTRL_REG10,
   RESERVED1,
   INT_GEN_SRC_XL,
   STATUS_REG1,
   OUT_X_L_XL,
   OUT_X_H_XL,
   OUT_Y_L_XL,
   OUT_Y_H_XL,
   OUT_Z_L_XL,
   OUT_Z_H_XL,
   FIFO_CTRL,
   FIFO_SRC,
   INT_GEN_CFG_G,
   INT_GEN_THS_XH_G,
   INT_GEN_THS_XL_G,
   INT_GEN_THS_YH_G,
   INT_GEN_THS_YL_G,
   INT_GEN_THS_ZH_G,
   INT_GEN_THS_ZL_G,
   INT_GEN_DUR_G,
} LSM9DS1_AccelGryoRegisters_e;

typedef enum
{
   OFFSET_X_REG_L_M = 5,
   OFFSET_X_REG_H_M,
   OFFSET_Y_REG_L_M,
   OFFSET_Y_REG_H_M,
   OFFSET_Z_REG_L_M,
   OFFSET_Z_REG_H_M,
   RESERVED0,
   WHO_AM_I,
   RESERVED1,
   CTRL_REG1_M,
   CTRL_REG2_M,
   CTRL_REG3_M,
   CTRL_REG4_M,
   CTRL_REG5_M,
   RESERVED2,
   STATUS_REG_M,
   OUT_X_L_M,
   OUT_X_H_M,
   OUT_Y_L_M,
   OUT_Y_H_M,
   OUT_Z_L_M,
   OUT_Z_H_M,
   RESERVED3,
   INT_CFG_M,
   INT_SRC_M,
   INT_THS_L_M,
   INT_THS_H_M,
} LSM9DS1_MagRegisters_e;

/* ----------------------------------------------------------------------------
   -- I2C - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Accessor_Macros I2C - Register accessor macros
 * @{
 */


/* I2C - Register accessors */
typedef struct
{
   uint8_t ACT_THS
}

#endif //__LSM9DS1__
