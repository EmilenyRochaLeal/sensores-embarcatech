#ifndef _VL53L0X_PLATFORM_H_
#define _VL53L0X_PLATFORM_H_

#include "vl53l0x_def.h"
#include "vl53l0x_platform_log.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    VL53L0X_DevData_t Data; /*!< embed ST Ewok Dev  data as "Data"*/
    uint8_t I2cDevAddr;     /*!< i2c device address */
    uint8_t comms_type;     /*!< Type of comms: VL53L0X_COMMS_I2C */
    uint16_t comms_speed_khz; /*!< Comms speed [kHz]: typically 400kHz for I2C */
    // Removed: TwoWire *i2c; -> we use pico-sdk I2C instance globally
} VL53L0X_Dev_t;

typedef VL53L0X_Dev_t *VL53L0X_DEV;

#define PALDevDataGet(Dev, field) (Dev->Data.field)
#define PALDevDataSet(Dev, field, data) (Dev->Data.field) = (data)

/* Function prototypes */
VL53L0X_Error VL53L0X_LockSequenceAccess(VL53L0X_DEV Dev);
VL53L0X_Error VL53L0X_UnlockSequenceAccess(VL53L0X_DEV Dev);
VL53L0X_Error VL53L0X_WriteMulti(VL53L0X_DEV Dev, uint8_t index, uint8_t *pdata, uint32_t count);
VL53L0X_Error VL53L0X_ReadMulti(VL53L0X_DEV Dev, uint8_t index, uint8_t *pdata, uint32_t count);
VL53L0X_Error VL53L0X_WrByte(VL53L0X_DEV Dev, uint8_t index, uint8_t data);
VL53L0X_Error VL53L0X_WrWord(VL53L0X_DEV Dev, uint8_t index, uint16_t data);
VL53L0X_Error VL53L0X_WrDWord(VL53L0X_DEV Dev, uint8_t index, uint32_t data);
VL53L0X_Error VL53L0X_RdByte(VL53L0X_DEV Dev, uint8_t index, uint8_t *data);
VL53L0X_Error VL53L0X_RdWord(VL53L0X_DEV Dev, uint8_t index, uint16_t *data);
VL53L0X_Error VL53L0X_RdDWord(VL53L0X_DEV Dev, uint8_t index, uint32_t *data);
VL53L0X_Error VL53L0X_UpdateByte(VL53L0X_DEV Dev, uint8_t index, uint8_t AndData, uint8_t OrData);
VL53L0X_Error VL53L0X_PollingDelay(VL53L0X_DEV Dev);

#ifdef __cplusplus
}
#endif

#endif /* _VL53L0X_PLATFORM_H_ */
