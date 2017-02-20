#ifndef __LSM9DS1__
#define __LSM9DS1__

#include "includeall.h"

#define LSM9DS1_I2C_FREQ_KHZ             100
#define LSM9DS1_I2C_FAST_FREQ_KHZ        400

#define LSM9DS1_I2C_SDA_SETUP_NS         250
#define LSM9DS1_I2C_SDA_FAST_SETUP_NS    100F

#define LSM9DS1_ACCELGYRO_ADDR           0xD6

#define LSM9DS1_MAG_ADDR                 0x38

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

typedef union
{
   struct
   {
      uint8_t ACT_THS            : 7; // Inactivity threshold
      uint8_t SLEEP_ON_INACT_EN  : 1; // Gyroscope operating mode during inactivity
   } b;
   uint8_t B;
} LSM9DS1_ACT_THS_t; // Activity threshold event register.

typedef union
{
   struct
   {
      uint8_t XLIE_XL : 1; // x-axis low event
      uint8_t XHIE_XL : 1; // x-axis high event
      uint8_t YLIE_XL : 1; // y-axis low event
      uint8_t YHIE_XL : 1; // y-axis high event
      uint8_t ZLIE_XL : 1; // z-axis low event
      uint8_t ZHIE_XL : 1; // z-axis high event
      uint8_t _6D     : 1; // 6-direction detection function for interrupt.
      uint8_t AOI_XL  : 1; // AND/OR combination of accelerometer's interrupt events.
   } b;
   uint8_t B;
} LSM9DS1_INT_GEN_CFG_XL_t; // Linear accerleration sensor interrupt generator configuration register.

typedef union
{
   struct
   {
      uint8_t DUR_XL  : 6; // Enter/exit interrupt duration value.
      uint8_t WAIT_XL : 1; // Wait function enabled on duration counter.
   } b;
   uint8_t B; // Linear acceleration sensor interrupt duration register
} LSM9DS1_INT_GEN_DUR_XL_t;

typedef union
{
   struct
   {
      uint8_t INT1_DRDY_XL : 1; // Accelerometer data ready
      uint8_t INT1_DRDY_G  : 1; // Gyroscope data ready
      uint8_t INT1_BOOT    : 1; // Boot status available
      uint8_t INT1_FTH     : 1; // FIFO Threshold
      uint8_t INT1_OVR     : 1; // overrun
      uint8_t INT1_FSS5    : 1; // FSS5
      uint8_t INT1_IG_XL   : 1; // Accelerotermeter
      uint8_t INT1_IG_G    : 1; // Gyroscope
   } b;
   uint8_t B;
} LSM9DS1_INT1_CTRL_t; // Interupts enable on INT1_A/G pin

typedef union
{
   struct
   {
      uint8_t INT2_DRDY_XL   : 1; // Accelerometer data ready
      uint8_t INT2_DRDY_G    : 1; // Gyroscope data ready
      uint8_t INT2_DRDY_TEMP : 1; // Temperature data ready
      uint8_t INT2_FTH       : 1; // FIFO Threshold
      uint8_t INT2_OVR       : 1; // Overrun interrupt
      uint8_t INT2_FSS5      : 1; // FSS5 interrupt enable
      uint8_t RESERVED       : 1; // 
      uint8_t INT2_INACT     : 1; // Inactivity interrupt output signal 
   } b;
   uint8_t B;
} LSM9DS1_INT2_CTRL_t; //  interrupts on INT2_A/G pin

typedef union
{
   struct
   {
      uint8_t BW_G  : 2; // Gyroscope bandwidth selection
      uint8_t FS_G  : 2; // Gyroscope full-scale selection
      uint8_t ODR_G : 3; // Gyroscope output data rate selection
   } b;
   uint8_t B;
} LSM9DS1_CTRL_REG1_G_t;

typedef enum
{
   POWER_DOWN = 0,
   _14_9,
   _59_5,
   _119,
   _238,
   _476,
   _952,
   NA,
} LSM9DS1_ODR_e;

typedef union
{
   struct
   {
      uint8_t OUT_SEL  : 2; // Out selection configuration
      uint8_t INT_SEL  : 2; // INT selection configuration
      uint8_t RESERVED : 4; 
   } b;
   uint8_t B;
} LSM9DS1_CTRL_REG2_G; // Angular rate sensor control register 2.

typedef union
{
   struct
   {
      uint8_t HPCF_G   : 4; // Gyroscope high-pass filter cutoff frequency selection.
      uint8_t RESERVED : 2;
      uint8_t HP_EN    : 1; // High-pass filter enable
      uint8_t LP_EN    : 1; // Low-pass filter enable
   } b;
   uint8_t B;
} LSM9DS1_CTRL_REG3_G_t; // Angular rate sensor control register 3.

typedef union
{
   struct
   {
      uint8_t Orient  : 3; // Directional user orientation selection.
      uint8_t SignZ_G : 1; // Yaw axis ( Z ) angular rate sign, 1 is negative
      uint8_t SignY_G : 1; // Yaw axis ( Y ) angular rate sign.
      uint8_t SignX_G : 1; // Yaw axis ( X ) angular rate sign.
      uint8_t RESERVED: 2;
   } b;
   uint8_t B;
} LSM9DS1_CFG_G_t; // Angular rate sensor sign and orientation register

typedef union
{
   struct
   {
      uint8_t XL_G : 1; // Pitch X low
      uint8_t XH_G : 1; // Pitch X high
      uint8_t YL_G : 1; // Pitch Y low
      uint8_t YH_G : 1; // Pitch Y high
      uint8_t ZL_G : 1; // Pitch Z low
      uint8_t ZH_G : 1; // Pitch Z high
      uint8_t IA_G : 1; // Interrupt active
      uint8_t RESERVED : 1;
   } b;
   uint8_t B;
} LSM9DS1_INT_GEN_SRC_G_t; // Angular rate sensor interupt source register

typedef union
{
   struct
   {
      uint8_t XLDA        : 1; // Accelerometer new data available
      uint8_t GDA         : 1; // Gyroscope new data available
      uint8_t TDA         : 1; // Tempearture sensor new data available
      uint8_t BOOT_STATUS : 1; // Boot running flag signal
      uint8_t INACT       : 1; // Inactivity interrupt output signal
      uint8_t IG_G        : 1; // Gyroscope interrupt output signal
      uint8_t IG_XL       : 1; // Acceleromter interrupt output signal
   } b;
   uint8_t B;
} LSM9DS1_STATUS_REG_t; 

typedef union
{
   struct
   {
      uint8_t 4D_XL1   : 1; // 4D option enabled on interrupt
      uint8_t LIR_XL1  : 1; // Latched interrupt
      uint8_t RESERVED : 1; 
      uint8_t XEN_G    : 1; // Gyroscope's pitch axis
      uint8_t YEN_G    : 1; // Gyroscope's roll axis 
      uint8_t ZEN_G    : 1; // Gyroscope's yaw axis
      uint8_t RESERVED1: 1;
   } b;
   uint8_t B;
} LSM9DS1_CTRL_REG4_t;

typedef union
{
   struct
   {
      uint8_t RESERVED : 3;
      uint8_t XEN_XL   : 1; // Accelerometer's X-axis output enbale
      uint8_t YEN_XL   : 1; // Accelerometer's Y-axis output enable
      uint8_t ZEN_XL   : 1; // Accelerometer's Z-axis output enable
      uint8_t DEC      : 2; // Decimation of acceleration data on OUT REG and FIFO
   } b;
   uint8_t B;
} LSM9DS1_CTRL_REG5_XL_t;

typedef enum
{
   NO_DECIMATION = 0,
   TWO_SAMPLES,
   FOUR_SAMPLES,
   EIGHT_SAMPLES,
} LSM9DS1_CTRL_REG5_XL_DECIMATION_e;

typedef union
{
   struct
   {
      uint8_t BW_XL       : 2; // Anit-Aliasing filter bandwidth selection
      uint8_t BW_SCAL_ODR : 1; // Bandwidth selection
      uint8_t FS_XL       : 2; // Accelerometer full-scale selection
      uint8_t ODR_XL      : 3; // OUtput data rate and power mode selection
   } b;
   uint8_t B;
} LSM9DS1_CTRL_REG6_XL_t;

typedef enum
{
   AAFILTER_408HZ = 0,
   AAFILTER_211HZ,
   AAFILTER_105HZ,
   AAFILTER_50HZ,
} LSM9DS1_ANTI_ALIASING_FILTER_e;

typedef enum
{
   ODR_XL_POWERDOWN = 0,
   ODR_XL_10HZ,
   ODR_XL_50HZ,
   ODR_XL_119HZ,
   ODR_XL_238HZ,
   ODR_XL_476HZ,
   ODR_XL_952HZ,
} LSM9DS1_ODR_XL_e;

typedef union
{
   struct
   {
      uint8_t HPIS1     : 1; // High-pass filter enabled for acceleration sensor interrupt function on interrupt
      uint8_t RESERVED0 : 1;
      uint8_t FDS       : 1; // Filtered data selection
      uint8_t RESERVED1 : 2;
      uint8_t DCF       : 2; // Accelerometer digital high/low filter cutoff frequency selection.
                             // The BW of the high-pass filter depends ont he selected ODR.
      uint8_t HR        : 1; // High resolution mode for accelerometer enable.
   } b;
   uint8_t B;
} LSM9DS1_CTRL_REG7_XL_t; 

typedef union
{
   struct
   {
      uint8_t SW_RESET   : 1;
      uint8_t BLE        : 1; // Big/Little Endian data selection
      uint8_t IF_ADD_INC : 1; // Register address automatically incremented during a multiple byte access with a serial interface.
      uint8_t SIM        : 1; // SPI serial interface mode selection
      uint8_t PP_OD      : 1; // Push-pull/open-drain selection on the INT1/2_A/G pin
      uint8_t H_LACTIVE  : 1; // Interrupt activation level
      uint8_t BDU        : 1; // Block data update
      uint8_t BOOT       : 1; // Reboot memory content 
   } b;
   uint8_t B;
} LSM9DS1_CTRL_REG8_t;

typedef union
{
   struct
   {
      uint8_t STOP_ON_FTH   : 1; // Enable FIFO threshold level use
      uint8_t FIFO_EN       : 1; // FIFO memory enable
      uint8_t I2C_DISABLE   : 1;
      uint8_t DRDY_MASK_BIT : 1; // Data availab enable bit
      uint8_t FIFO_TEMP_EN  : 1; // Temperature data storage in FIFO enable
      uint8_t RESERVED0     : 1;
      uint8_t SLEEP_G       : 1; // Gyroscope sleep mode enable
      uint8_t RESERVED1     : 1;
   } b;
   uint8_t B;
} LSM9DS1_CTRL_REG9_t;

typedef union
{
   struct
   {
      uint8_t ST_XL     : 1; // Linear acceleration sensor self-test enable
      uint8_t RESERVED0 : 1;
      uint8_t ST_G      : 1; // Angular rate sensor self-test enable
      uint8_t RESERVED1 : 5;
   } b;
   uint8_t B;
} LSM9DS1_CTRL_REG10_t;

typedef union
{
   struct
   {
      uint8_t XL_XL : 1;
      uint8_t XH_XL : 1;
      uint8_t YL_XL : 1;
      uint8_t YH_XL : 1;
      uint8_t ZL_XL : 1;
      uint8_t ZH_XL : 1;
      uint8_t IA_XL : 1; // Interrupt active
   } b;
   uint8_t B;
} LSM9DS1_INT_GEN_SRC_XL_t;

typedef union
{
   struct
   {
      uint8_t FTH   : 5; // FIFO threshold level setting.
      uint8_t FMODE : 3; // FIFO mode selection bits
   } b;
   uint8_t B;
} LSM9DS1_FIFO_CTRL_t;

typedef enum
{
   FIFO_Bypass = 0,
   FIFO_StopWhenFifoFull,
   FIFO_Reserved,
   FIFO_ContinuousUntillTrigger,
   FIFO_BypassUntilTrigger,
   FIFO_Continuous,
} LSM9DS1_FIFO_CTRL_FMODE_e;

typedef union
{
   struct
   {
      uint8_t FSS  : 6; // Number of unread samples stored into FIFO
      uint8_t OVRN : 1; // FIFO Overrun status
      uint8_t FTH  : 1; // FIFO Threshold status 
   } b;
   uint8_t B;
} LSM9DS1_FIFO_SRC_t;

typedef union
{
   struct
   {
      XLIE_G : 1; // Interrupt enable on gyroscope's pitch X axis low event
      XHIE_G : 1; //             ""                               high ""
      YLIE_G : 1; //             ""                        Y axis low  ""
      YHIE_G : 1; //             ""                               high ""
      ZLIE_G : 1; //             ""                        Z axis low  ""
      ZHIE_G : 1; //             ""                               high ""
      LIR_G  : 1; // Latch gyroscope interrupt request
      AOI_G  : 1; // AND/OR combination of gyroscope's interrupt events
   } b;
   uint8_t B;
} LSM9DS1_INT_GEN_CFG_G_t;

typedef union
{
   struct
   {
      uint16_t THS_G_X : 15; // Angular rate sensor interrupt threshold on pitch X
      uint16_t DCRM_G  : 1;  // Decrement or reset counter mode selection. 0 == reset
   } b;
   uint16_t W;
} LSM9DS1_INT_GEN_THS_X_G_t;

typedef union
{
   struct
   {
      uint16_t THS_G_Y   : 15; // Angular rate sensor interrupt threshold on pitch X
      uint16_t RESERVED  : 1; 
   } b;
   uint16_t W;
} LSM9DS1_INT_GEN_THS_Y_G_t;

typedef union
{
   struct
   {
      uint16_t THS_G_Z  : 15; // Angular rate sensor interrupt threshold on pitch X
      uint16_t RESERVED : 1;  
   } b;
   uint16_t W;
} LSM9DS1_INT_GEN_THS_Z_G_t;

typedef union
{
   struct
   {
      uint8_t DUR_G  : 7; // Enter/exit interrupt duration value
      uint8_t WAIT_G : 1; // Exit from interrupt wait function enable.
   } b;
   uint8_t B;
} LSM9DS1_INT_GEN_DUR_G_t; // Angular rate sensor itnerupt generator duration register

typedef union
{
   struct
   {
      uint8_t ST       : 1; // Self-test enable
      uint8_t FAST_ODR : 1; // enables data register higher than 80 Hz
      uint8_t DO       : 3; // Output data rate selection
      uint8_t OM       : 2; // X and Y axes operative mode selection
      uint8_t TEMP_COMP: 1; // Temperature compenstiaon enable.
   } b;
   uint8_t B;
}LSM9DS1_CTRL_REG1_M;

typedef enum
{
   LOW_POWER_MODE = 0,
   MEDIUM_ERFORMANCE_MODE,
   HIGH_PERFORMANCE_MODE,
   ULTRA_HIGH_PERFORMANCE_MODE,
} LSM9DS1_MAGNOMETER_OPERATIVE_MODES_e;

typedef enum
{
   MAG_ODR_0_625_HZ = 0,
   MAG_ODR_1_25_HZ,
   MAG_ODR_2_5_HZ,
   MAG_ODR_5_HZ,
   MAG_ODR_10_HZ,
   MAG_ODR_40_HZ,
   MAG_ODR_80_HZ,
} LSM9DS1_MAG_ODR_DATA_RATE_e;

typedef union
{
   struct
   {
      uint8_t RESERVED0 : 2;
      uint8_t SOFT_RST  : 1; //Configuration registers and user register reset function.
      uint8_t REBOOT    : 1; // Reboot memory content
      uint8_t RESERVED1 : 1;
      uint8_t FS        : 2; // Full-scale configuration
      uint8_t RESERVED2 : 1;
   } b;
   uint8_t B;
} LSM9DS1_CTRL_REG2_M_t;

typedef enum
{
   FOUR_GAUSS = 0,
   EIGHT_GAUSS,
   TWELVE_GAUSS,
   SIXTEEN_GAUSS
} LSM9DS1_FS_CONFIG_e;

typedef union
{
   struct
   {
      uint8_t MD          : 2; // Operating mode selection
      uint8_t SIM         : 1; // SPI Serial Interface mode selection
      uint8_t RESERVED0   : 2;
      uint8_t LP          : 1; // Low poer mode configuartion.
      uint8_t RESERVED1   : 1;
      uint8_t I2C_DISABLE : 1; // Disapble the i2c interface
   } b;
   uint8_t B;
} LSM9DS1_CTRL_REG3_M_t;

typedef enum
{
   MD_CONTINUOUS_CONVERSION_MODE = 0,
   MD_SINGLE_CONVERSION_MODE,
   MD_POWER_DOWN_MODE,
   MD_POWER_DOWN_MODE1,
} LSM9DS1_MD_SYSTEM_OPERATING_MODE_e;

typedef union
{
   struct
   {
      uint8_t RESERVED0 : 1;
      uint8_t BLE       : 1; // Big/Little Endian data selection
      uint8_t OMZ       : 2; // Z-axis operative mode selection
      uint8_t RESERVED1 : 4;
   } b;
   uint8_t B;
} LSM9DS1_CTRL_REG4_M_t;

typedef union
{
   struct
   {
      uint8_t RESERVED  : 6;
      uint8_t BDU       : 1; // Block data update for magnetic data
      uint8_t FAST_READ : 1; // Allows reading the high part of data out only in order to inrease reading efficiency
   } b;
   uint8_t B;
} LSM9DS1_CTRL_REG5_M_t;

typedef union
{
   struct
   {
      uint8_t XDA   : 1; // x-axis new data available
      uint8_t YDA   : 1; // y-axis ""
      uint8_t ZDA   : 1; // z-axis ""
      uint8_t ZYXDA : 1; // x,y,z-axis ""
      uint8_t XOR   : 1; // x-axis data overrun
      uint8_t YOR   : 1; // y-axis ""
      uint8_t ZOR   : 1; // z-axis ""
      uint8_t ZYXOR : 1; // x,y,z-axis ""
   } b;
   uint8_t B;
} LSM9DS1_STATUS_REG_M_t;

typedef union
{
   struct
   {
      IEN      : 1; // Interrupt enable on INT_M pin
      IEL      : 1; // Latch interrupt request
      IEA      : 1; // Intertupt active configuration on INT_MAG
      RESERVED : 2;
      ZIEN     : 1; // Enable interrupt generation on Z-axis 
      YIEN     : 1; //              ""                Y-axis
      XIEN     : 1; //              ""                X-axis
   } b;
   uint8_t B;
} LSM9DS1_INT_CFG_M_t;

typedef union
{
   struct
   {
      INT_  : 1; // Interrupt event occorred
      MROI  : 1; // Internal measurement range overflow on magnetic value
      NTH_Z : 1; // Value on Z-axis exceeds the threshold on the negative side
      NTH_Y : 1; //    ""    Y-axis                  "" 
      NTH_X : 1; //    ""    X-axis                  ""
      PTH_Z : 1; //    ""    Z-axis                  ""          posistive side
      PTH_X : 1; //    ""    Y-axis                  ""
      PTH_Y : 1; //    ""    X-axis                  ""
   } b;
   uint8_t B;
} LSM9DS1_INT_SRC_M_t;

#endif //__LSM9DS1__
