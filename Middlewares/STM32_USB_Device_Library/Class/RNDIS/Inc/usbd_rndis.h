/**
  ******************************************************************************
  * @file    usbd_rndis.h
  * @author  Benedek Kupper
  * @version V0.1
  * @date    2017-08-17
  * @brief   header file for the usbd_rndis.c file.
  ******************************************************************************
  *
  *  This file is part of STM32_XPD.
  *
  *  STM32_XPD is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  STM32_XPD is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with STM32_XPD.  If not, see <http://www.gnu.org/licenses/>.
  */
#ifndef __USB_RNDIS_H
#define __USB_RNDIS_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_ioreq.h"
#include "rndis.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
 * @{
 */

/** @addtogroup USBD_RNDIS
 * @{
 */

/** @defgroup USBD_RNDIS_Exported_Defines
 * @{
 */
#define RNDIS_IN_EP                                 0x82  /* EP2 for data IN */
#define RNDIS_OUT_EP                                0x03  /* EP3 for data OUT */
#define RNDIS_CMD_EP                                0x81  /* EP1 for RNDIS commands */

#define RNDIS_DATA_HS_MAX_PACKET_SIZE               (USB_HS_MAX_PACKET_SIZE)
#define RNDIS_DATA_FS_MAX_PACKET_SIZE               (USB_FS_MAX_PACKET_SIZE)
#define RNDIS_CMD_PACKET_SIZE                       8  /* Control Endpoint Packet size */

#define USB_RNDIS_CONFIG_DESC_SIZ                   67

#define RNDIS_DATA_HS_IN_PACKET_SIZE                (RNDIS_DATA_HS_MAX_PACKET_SIZE)
#define RNDIS_DATA_HS_OUT_PACKET_SIZE               (RNDIS_DATA_HS_MAX_PACKET_SIZE)

#define RNDIS_DATA_FS_IN_PACKET_SIZE                (RNDIS_DATA_FS_MAX_PACKET_SIZE)
#define RNDIS_DATA_FS_OUT_PACKET_SIZE               (RNDIS_DATA_FS_MAX_PACKET_SIZE)

#define RNDIS_SEND_ENCAPSULATED_COMMAND             0x00
#define RNDIS_GET_ENCAPSULATED_RESPONSE             0x01

#ifndef RNDIS_EP0_RESERVED_SIZE
#define RNDIS_EP0_RESERVED_SIZE                     13 /* Overrideable in usbd_conf.h */
#endif

/**
 * @}
 */

/** @defgroup USBD_CORE_Exported_TypesDefinitions
 * @{
 */

/** @brief RNDIS object query and set definition */
typedef struct
{
    RNDIS_OidType Oid; /*!< Object Identifier */
    RNDIS_StatusType (*QuerySetServer)(uint32_t *, uint32_t *); /*!< Object info setter-getter
                         @arg param1: pointer to the input/output data
                         @arg param2: pointer to the data length (0 means query, it has to be overwritten)
                         @arg return: result of the operation */
}RNDIS_ObjectInfoType;

typedef struct
{
    void (*Init)(void);
    void (*DeInit)(void);
    void (*PacketReceived)(uint8_t *, uint32_t);
    const RNDIS_ObjectInfoType * ObjectInfo;
    uint32_t ObjectInfoCount;
} USBD_RNDIS_ItfTypeDef;

typedef struct
{
    uint32_t data[RNDIS_EP0_RESERVED_SIZE + (RNDIS_DATA_HS_MAX_PACKET_SIZE / 4)];
    void * TxMsg;
    void *RxMsg;
    uint16_t TxLength;
    uint16_t MsgLength;
    uint16_t MaxTransferSize;
} USBD_RNDIS_HandleTypeDef;

/**
 * @}
 */

/** @defgroup USBD_CORE_Exported_Variables
 * @{
 */

extern const USBD_ClassTypeDef USBD_RNDIS;
#define USBD_RNDIS_CLASS    &USBD_RNDIS

/**
 * @}
 */

/** @defgroup USB_CORE_Exported_Functions
 * @{
 */

uint8_t USBD_RNDIS_RegisterInterface(USBD_HandleTypeDef *pdev,
        const USBD_RNDIS_ItfTypeDef *fops);

uint8_t USBD_RNDIS_TransmitMessage(USBD_HandleTypeDef *pdev, RNDIS_PacketMsgType *msg);

uint8_t USBD_RNDIS_SetReceiveBuffer(USBD_HandleTypeDef *pdev, RNDIS_PacketMsgType *buffer, uint16_t size);

uint8_t USBD_RNDIS_SendStatus(USBD_HandleTypeDef *pdev, RNDIS_StatusType status);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __USB_RNDIS_H */
