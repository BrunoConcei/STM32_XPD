/**
  ******************************************************************************
  * @file    usbd_rndis.c
  * @author  Benedek Kupper
  * @version V0.1
  * @date    2017-08-17
  * @brief   This file provides the high layer firmware functions to manage the
  *          following functionalities of the USB RNDIS Class:
  *           - Initialization and Configuration of high and low layer
  *           - Enumeration as CDC Device (and enumeration for each implemented memory interface)
  *           - OUT/IN data transfer
  *           - Notification IN transfer
  *
  *  @verbatim
  *
  *          ===================================================================
  *                              RNDIS Class Driver Description
  *          ===================================================================
  *           This driver manages the "Universal Serial Bus Class Definitions for Communications Devices
  *           Revision 1.2 November 16, 2007" and the sub-protocol specification of "Universal Serial Bus
  *           Communications Class Subclass Specification for PSTN Devices Revision 1.2 February 9, 2007"
  *           This driver implements the following aspects of the specification:
  *             - Device descriptor management
  *             - Configuration descriptor management
  *             - Enumeration as CDC device with 2 data endpoints (IN and OUT) and 1 command endpoint (IN)
  *             - Vendor specific implementation (Microsoft Remote Network Driver Interface Specification)
  *
  *           These aspects may be enriched or modified for a specific user application.
  *
  *  @endverbatim
  *
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
#include "usbd_rndis.h"
#include "usbd_ctlreq.h"

#include <string.h>

/** @addtogroup STM32_USB_DEVICE_LIBRARY
 * @{ */

/** @defgroup USBD_RNDIS
 * @brief USB Remote Network Driver Interface Specification module
 * @{ */

static uint8_t USBD_RNDIS_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx);

static uint8_t USBD_RNDIS_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx);

static uint8_t USBD_RNDIS_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req);

static uint8_t USBD_RNDIS_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t USBD_RNDIS_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t USBD_RNDIS_EP0_RxReady(USBD_HandleTypeDef *pdev);

static uint8_t *USBD_RNDIS_GetFSCfgDesc(uint16_t *length);

#ifdef DEVICE_HS
static uint8_t *USBD_RNDIS_GetHSCfgDesc(uint16_t *length);
#endif

static uint8_t *USBD_RNDIS_GetDeviceQualifierDesc(uint16_t *length);

/** @defgroup USBD_RNDIS_Private_Variables
 * @{ */

/* USB Standard Device Descriptor */
__ALIGN_BEGIN static const uint8_t USBD_RNDIS_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END =
{
    USB_LEN_DEV_QUALIFIER_DESC,     /* bLength */
    USB_DESC_TYPE_DEVICE_QUALIFIER, /* bDescriptorType */
    0x00, 0x02,                     /* bcdUSB */
    0x02,                           /* bDeviceClass */
    0x00,                           /* bDeviceSubClass */
    0x00,                           /* bDeviceProtocol */
    0x40,                           /* bMaxPacketSize */
    0x01,                           /* bNumConfigurations */
    0x00,                           /* bReserved */
};

/* RNDIS interface class callbacks structure */
const USBD_ClassTypeDef USBD_RNDIS = {
    USBD_RNDIS_Init,
    USBD_RNDIS_DeInit,
    USBD_RNDIS_Setup,
    NULL, /* EP0_TxSent */
    USBD_RNDIS_EP0_RxReady,
    USBD_RNDIS_DataIn,
    USBD_RNDIS_DataOut,
    NULL,
    NULL,
    NULL,
#ifdef DEVICE_HS
    USBD_RNDIS_GetHSCfgDesc,
#else
    NULL,
#endif
    USBD_RNDIS_GetFSCfgDesc,
    NULL,
    USBD_RNDIS_GetDeviceQualifierDesc
};

#ifdef DEVICE_HS
/* USB RNDIS device Configuration Descriptor */
__ALIGN_BEGIN static const uint8_t USBD_RNDIS_CfgHSDesc[USB_RNDIS_CONFIG_DESC_SIZ] __ALIGN_END =
{
    /* Configuration Descriptor */
    0x09,                           /* bLength: Configuration Descriptor size */
    USB_DESC_TYPE_CONFIGURATION,    /* bDescriptorType: Configuration */
    USB_RNDIS_CONFIG_DESC_SIZ,0x00, /* wTotalLength:no of returned bytes */
    0x02,                           /* bNumInterfaces: 2 interface */
    0x01,                           /* bConfigurationValue: Configuration value */
    0x00,                           /* iConfiguration: Index of string descriptor describing the configuration */
    0x80 | (USBD_SELF_POWERED << 6),/* bmAttributes: self powered */
    USBD_MAX_POWER_mA / 2,          /* MaxPower x mA */

    /* Interface Descriptor */
    0x09,                       /* bLength: Interface Descriptor size */
    USB_DESC_TYPE_INTERFACE,    /* bDescriptorType: Interface */
    /* Interface descriptor type */
    0x00,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x01,   /* bNumEndpoints: One endpoints used */
    0x02,   /* bInterfaceClass: Communication Interface Class */
    0x02,   /* bInterfaceSubClass: Abstract Control Model */
    0xFF,   /* bInterfaceProtocol: Vendor specific */
    0x00,   /* iInterface: */

    /* Header Functional Descriptor */
    0x05,   /* bLength: Endpoint Descriptor size */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x00,   /* bDescriptorSubtype: Header Func Desc */
    0x10,   /* bcdCDC: spec release number */
    0x01,

    /* Call Management Functional Descriptor */
    0x05,   /* bFunctionLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x01,   /* bDescriptorSubtype: Call Management Func Desc */
    0x00,   /* bmCapabilities: D0+D1 */
    0x01,   /* bDataInterface: 1 */

    /* ACM Functional Descriptor */
    0x04,   /* bFunctionLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
    0x02,   /* bmCapabilities */

    /* Union Functional Descriptor */
    0x05,   /* bFunctionLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x06,   /* bDescriptorSubtype: Union func desc */
    0x00,   /* bMasterInterface: Communication class interface */
    0x01,   /* bSlaveInterface0: Data Class Interface */

    /* Endpoint 2 Descriptor */
    0x07,                           /* bLength: Endpoint Descriptor size */
    USB_DESC_TYPE_ENDPOINT,         /* bDescriptorType: Endpoint */
    RNDIS_CMD_EP,                   /* bEndpointAddress */
    0x03,                           /* bmAttributes: Interrupt */
    LOBYTE(RNDIS_CMD_PACKET_SIZE),  /* wMaxPacketSize: */
    HIBYTE(RNDIS_CMD_PACKET_SIZE),
#ifdef RNDIS_CMD_INTR_INTERVAL
    RNDIS_CMD_INTR_INTERVAL,        /* bInterval: */
#else
    0x80,                           /* bInterval: */
#endif /* RNDIS_CMD_INTR_INTERVAL */

    /* Data class interface descriptor */
    0x09,   /* bLength: Endpoint Descriptor size */
    USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
    0x01,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x02,   /* bNumEndpoints: Two endpoints used */
    0x0A,   /* bInterfaceClass: CDC */
    0x00,   /* bInterfaceSubClass: */
    0x00,   /* bInterfaceProtocol: */
    0x00,   /* iInterface: */

    /* Endpoint OUT Descriptor */
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType: Endpoint */
    RNDIS_OUT_EP,                           /* bEndpointAddress */
    0x02,                                   /* bmAttributes: Bulk */
    LOBYTE(RNDIS_DATA_HS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
    HIBYTE(RNDIS_DATA_HS_MAX_PACKET_SIZE),
    0x00,                                   /* bInterval: ignore for Bulk transfer */

    /* Endpoint IN Descriptor */
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType: Endpoint */
    RNDIS_IN_EP,                            /* bEndpointAddress */
    0x02,                                   /* bmAttributes: Bulk */
    LOBYTE(RNDIS_DATA_HS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
    HIBYTE(RNDIS_DATA_HS_MAX_PACKET_SIZE),
    0x00                                    /* bInterval: ignore for Bulk transfer */
};
#endif

/* USB RNDIS device Configuration Descriptor */
__ALIGN_BEGIN static const uint8_t USBD_RNDIS_CfgFSDesc[USB_RNDIS_CONFIG_DESC_SIZ] __ALIGN_END =
{
    /* Configuration Descriptor */
    0x09,                           /* bLength: Configuration Descriptor size */
    USB_DESC_TYPE_CONFIGURATION,    /* bDescriptorType: Configuration */
    USB_RNDIS_CONFIG_DESC_SIZ,0x00, /* wTotalLength:no of returned bytes */
    0x02,                           /* bNumInterfaces: 2 interface */
    0x01,                           /* bConfigurationValue: Configuration value */
    0x00,                           /* iConfiguration: Index of string descriptor describing the configuration */
    0x80 | (USBD_SELF_POWERED << 6),/* bmAttributes: self powered */
    USBD_MAX_POWER_mA / 2,          /* MaxPower x mA */

    /* Interface Descriptor */
    0x09,                       /* bLength: Interface Descriptor size */
    USB_DESC_TYPE_INTERFACE,    /* bDescriptorType: Interface */
    /* Interface descriptor type */
    0x00,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x01,   /* bNumEndpoints: One endpoints used */
    0x02,   /* bInterfaceClass: Communication Interface Class */
    0x02,   /* bInterfaceSubClass: Abstract Control Model */
    0xFF,   /* bInterfaceProtocol: Vendor specific */
    0x00,   /* iInterface: */

    /* Header Functional Descriptor */
    0x05,   /* bLength: Endpoint Descriptor size */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x00,   /* bDescriptorSubtype: Header Func Desc */
    0x10,   /* bcdCDC: spec release number */
    0x01,

    /* Call Management Functional Descriptor */
    0x05,   /* bFunctionLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x01,   /* bDescriptorSubtype: Call Management Func Desc */
    0x00,   /* bmCapabilities: D0+D1 */
    0x01,   /* bDataInterface: 1 */

    /* ACM Functional Descriptor */
    0x04,   /* bFunctionLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
    0x02,   /* bmCapabilities */

    /* Union Functional Descriptor */
    0x05,   /* bFunctionLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x06,   /* bDescriptorSubtype: Union func desc */
    0x00,   /* bMasterInterface: Communication class interface */
    0x01,   /* bSlaveInterface0: Data Class Interface */

    /* Endpoint 2 Descriptor */
    0x07,                           /* bLength: Endpoint Descriptor size */
    USB_DESC_TYPE_ENDPOINT,         /* bDescriptorType: Endpoint */
    RNDIS_CMD_EP,                   /* bEndpointAddress */
    0x03,                           /* bmAttributes: Interrupt */
    LOBYTE(RNDIS_CMD_PACKET_SIZE),  /* wMaxPacketSize: */
    HIBYTE(RNDIS_CMD_PACKET_SIZE),
    0x01,                           /* bInterval: */

    /* Data class interface descriptor */
    0x09,                   /* bLength: Endpoint Descriptor size */
    USB_DESC_TYPE_INTERFACE,/* bDescriptorType: */
    0x01,                   /* bInterfaceNumber: Number of Interface */
    0x00,                   /* bAlternateSetting: Alternate setting */
    0x02,                   /* bNumEndpoints: Two endpoints used */
    0x0A,                   /* bInterfaceClass: CDC */
    0x00,                   /* bInterfaceSubClass: */
    0x00,                   /* bInterfaceProtocol: */
    0x00,                   /* iInterface: */

    /* Endpoint OUT Descriptor */
    0x07,                                   /* bLength: Endpoint Descriptor size */
    USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType: Endpoint */
    RNDIS_OUT_EP,                           /* bEndpointAddress */
    0x02,                                   /* bmAttributes: Bulk */
    LOBYTE(RNDIS_DATA_FS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
    HIBYTE(RNDIS_DATA_FS_MAX_PACKET_SIZE),
    0x00,                                   /* bInterval: ignore for Bulk transfer */

    /* Endpoint IN Descriptor */
    0x07,                                   /* bLength: Endpoint Descriptor size */
    USB_DESC_TYPE_ENDPOINT,                 /* bDescriptorType: Endpoint */
    RNDIS_IN_EP,                            /* bEndpointAddress */
    0x02,                                   /* bmAttributes: Bulk */
    LOBYTE(RNDIS_DATA_FS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
    HIBYTE(RNDIS_DATA_FS_MAX_PACKET_SIZE),
    0x00                                    /* bInterval: ignore for Bulk transfer */
};

static const uint8_t RNDIS_ResponseAvailable[] = {1, 0, 0, 0, 0, 0, 0, 0};

static const RNDIS_InitCmpltType RNDIS_InitCmplt = {
        .MessageType   = REMOTE_NDIS_INITIALIZE_CMPLT,
        .MessageLength = sizeof(RNDIS_InitCmpltType),
        .Status        = RNDIS_STATUS_SUCCESS,
        .MajorVersion  = RNDIS_MAJOR_VERSION,
        .MinorVersion  = RNDIS_MINOR_VERSION,
        .DeviceFlags   = 0x000000001,
        .Medium        = 0x000000000,
        .MaxPacketsPerTransfer = 1,
        .MaxTransferSize       = sizeof(RNDIS_PacketMsgType),
        .PacketAlignmentFactor = 0,
};

/** @} */

/** @defgroup USBD_RNDIS_Private_Functions
 * @{ */

/**
 * @brief  Returns the configuration descriptor
 * @param  length: pointer to the data length
 * @return pointer to descriptor buffer
 */
static uint8_t *USBD_RNDIS_GetFSCfgDesc(uint16_t *length)
{
    *length = sizeof(USBD_RNDIS_CfgFSDesc);
    return (uint8_t*)USBD_RNDIS_CfgFSDesc;
}

#ifdef DEVICE_HS
/**
 * @brief  USBD_RNDIS_GetHSCfgDesc
 *         Return configuration descriptor
 * @param  length : pointer data length
 * @return pointer to descriptor buffer
 */
static uint8_t *USBD_RNDIS_GetHSCfgDesc(uint16_t *length)
{
    *length = sizeof(USBD_RNDIS_CfgHSDesc);
    return (uint8_t*)USBD_RNDIS_CfgHSDesc;
}
#endif

/**
 * @brief  Returns the Device Qualifier descriptor
 * @param  length: pointer to the data length
 * @return pointer to descriptor buffer
 */
static uint8_t *USBD_RNDIS_GetDeviceQualifierDesc(uint16_t *length)
{
    *length = sizeof(USBD_RNDIS_DeviceQualifierDesc);
    return (uint8_t*)USBD_RNDIS_DeviceQualifierDesc;
}

/**
 * @brief  (Re)Initialize the RNDIS interface
 * @param  pdev: USB device instance
 * @param  cfgidx: Configuration index
 * @return Result of the operation
 */
static uint8_t USBD_RNDIS_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
    uint16_t in_packet_size, out_packet_size;

#ifdef DEVICE_HS
    if (pdev->dev_speed == USBD_SPEED_HIGH)
    {
        in_packet_size  = RNDIS_DATA_HS_IN_PACKET_SIZE;
        out_packet_size = RNDIS_DATA_HS_OUT_PACKET_SIZE;
    }
    else
#endif
    {
        in_packet_size  = RNDIS_DATA_FS_IN_PACKET_SIZE;
        out_packet_size = RNDIS_DATA_FS_OUT_PACKET_SIZE;
    }

    /* Open EP IN */
    USBD_LL_OpenEP(pdev, RNDIS_IN_EP,  USBD_EP_TYPE_BULK, in_packet_size);

    /* Open EP OUT */
    USBD_LL_OpenEP(pdev, RNDIS_OUT_EP, USBD_EP_TYPE_BULK, out_packet_size);

    /* Open Command IN EP */
    USBD_LL_OpenEP(pdev, RNDIS_CMD_EP, USBD_EP_TYPE_INTR, RNDIS_CMD_PACKET_SIZE);

    pdev->pClassData = USBD_malloc(sizeof(USBD_RNDIS_HandleTypeDef));

    if (pdev->pClassData != NULL)
    {
        USBD_RNDIS_HandleTypeDef *hrndis = (USBD_RNDIS_HandleTypeDef*) pdev->pClassData;

        /* Initialize transfer states */
        hrndis->TxLength = 0;
        hrndis->MaxTransferSize = RNDIS_InitCmplt.MaxTransferSize;
    }

    return USBD_OK;
}

/**
 * @brief  Deinitialize the RNDIS interface
 * @param  pdev: USB device instance
 * @param  cfgidx: Configuration index
 * @return Result of the operation
 */
static uint8_t USBD_RNDIS_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
    /* Close EP IN */
    USBD_LL_CloseEP(pdev, RNDIS_IN_EP);

    /* Close EP OUT */
    USBD_LL_CloseEP(pdev, RNDIS_OUT_EP);

    /* Close Command IN EP */
    USBD_LL_CloseEP(pdev, RNDIS_CMD_EP);

    /* DeInit RNDIS Interface components */
    if (pdev->pClassData != NULL)
    {
        USBD_RNDIS_ItfTypeDef *itf       = (USBD_RNDIS_ItfTypeDef*) pdev->pUserData;

        if (itf->DeInit != NULL)
        {
            itf->DeInit();
        }

        USBD_free(pdev->pClassData);
        pdev->pClassData = NULL;
    }

    return USBD_OK;
}

/**
 * @brief  Handle the RNDIS specific commands
 * @param  pdev: USB device instance
 * @param  req: RNDIS command request
 * @return Result of the operation
 */
static uint8_t USBD_RNDIS_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
    USBD_RNDIS_HandleTypeDef *hrndis = (USBD_RNDIS_HandleTypeDef*) pdev->pClassData;

    switch (req->bmRequest & USB_REQ_TYPE_MASK)
    {
        case USB_REQ_TYPE_CLASS:
        {
            if (req->wLength)
            {
                if (req->bRequest == RNDIS_GET_ENCAPSULATED_RESPONSE)
                {
                    USBD_CtlSendData(pdev, (uint8_t *) hrndis->data,
                            (((RNDIS_GenMsgType*)hrndis->data)->MessageLength));
                }
                else /* SEND_ENCAPSULATED_COMMAND */
                {
                    hrndis->MsgLength = req->wLength;

                    USBD_CtlPrepareRx(pdev, (uint8_t *) hrndis->data, req->wLength);
                }
            }
            break;
        }

        case USB_REQ_TYPE_STANDARD:
        {
            if (req->bRequest == USB_REQ_GET_INTERFACE)
            {
                uint8_t ifalt = 0;
                USBD_CtlSendData(pdev, &ifalt, 1);
            }
            break;
        }

        default:
            break;
    }
    return USBD_OK;
}

/**
 * @brief  Transmits a Response Available notification for the RNDIS host
 * @param  pdev: USB device instance
 */
static void USBD_RNDIS_ResponseReady(USBD_HandleTypeDef *pdev)
{
    (void) USBD_LL_Transmit(pdev, RNDIS_CMD_EP,
            RNDIS_ResponseAvailable, RNDIS_CMD_PACKET_SIZE);
}

/**
 * @brief  Setup endpoint data processing
 * @param  pdev: USB device instance
 * @return Result of the operation
 */
static uint8_t USBD_RNDIS_EP0_RxReady(USBD_HandleTypeDef *pdev)
{
    USBD_RNDIS_HandleTypeDef *hrndis = (USBD_RNDIS_HandleTypeDef*) pdev->pClassData;
    USBD_RNDIS_ItfTypeDef *itf       = (USBD_RNDIS_ItfTypeDef*) pdev->pUserData;

    if ((hrndis != NULL) && (((RNDIS_GenMsgType*)hrndis->data)->MessageLength == hrndis->MsgLength))
    {
        switch (((RNDIS_GenMsgType*)hrndis->data)->MessageType)
        {
            case REMOTE_NDIS_INITIALIZE_MSG:
            {
                RNDIS_InitCmpltType* resp = (RNDIS_InitCmpltType*)hrndis->data;

                /* Copy the cmplt response to the EP0 buffer, with the incoming RequestID */
                uint32_t reqId = ((RNDIS_InitMsgType*)hrndis->data)->RequestID;

                *resp = RNDIS_InitCmplt;

                /* Initialize interface, set message values e.g. Medium, MaxTransferSize */
                if (itf->Init != NULL)
                {
                    itf->Init();
                }
                resp->RequestID = reqId;

                /* Increase the max transfer size if the receive buffer was set */
                if (hrndis->MaxTransferSize > resp->MaxTransferSize)
                {
                    resp->MaxTransferSize = hrndis->MaxTransferSize;
                }

                /* Send notification that the control endpoint has IN data ready */
                USBD_RNDIS_ResponseReady(pdev);
                break;
            }

            case REMOTE_NDIS_QUERY_MSG:
            {
                RNDIS_QueryCmpltType* resp = (RNDIS_QueryCmpltType*)hrndis->data;
                uint32_t* OIDInputBuffer   = RNDIS_MSG_PAYLOAD(RNDIS_QueryCmpltType, resp);
                uint32_t i, oid = ((RNDIS_QueryMsgType*)hrndis->data)->Oid;

                resp->MessageType      = REMOTE_NDIS_QUERY_CMPLT;
                resp->Status           = RNDIS_STATUS_FAILURE;
                resp->InfoBufferLength = 0;
                resp->InfoBufferOffset = sizeof(RNDIS_QueryCmpltType)
                                        - offsetof(RNDIS_QueryCmpltType, RequestID);

                /* The supported OID list query is serviced here */
                if (oid == OID_GEN_SUPPORTED_LIST)
                {
                    /* Copy the Object Identifier list */
                    for (i = 0; i < itf->ObjectInfoCount; i++)
                    {
                        OIDInputBuffer[i] = itf->ObjectInfo[i].Oid;
                    }

                    resp->Status           = RNDIS_STATUS_SUCCESS;
                    resp->InfoBufferLength = itf->ObjectInfoCount * sizeof(uint32_t);
                }
                else
                {
                    /* Try to find the requested query */
                    for (i = 0; i < itf->ObjectInfoCount; i++)
                    {
                        if (itf->ObjectInfo[i].Oid == oid)
                        {
                            RNDIS_ObjectInfoType* query = &itf->ObjectInfo[i];

                            /* Call the query server to fill the output data */
                            resp->Status = itf->ObjectInfo[i].QuerySetServer(
                                    OIDInputBuffer,
                                    &resp->InfoBufferLength);
                            break;
                        }
                    }
                }

                /* Set total length */
                resp->MessageLength = sizeof(RNDIS_QueryCmpltType) + resp->InfoBufferLength;

                /* Send notification that the control endpoint has IN data ready */
                USBD_RNDIS_ResponseReady(pdev);
                break;
            }

            case REMOTE_NDIS_SET_MSG:
            {
                RNDIS_SetMsgType* msg    = (RNDIS_SetMsgType*)hrndis->data;
                RNDIS_SetCmpltType* resp = (RNDIS_SetCmpltType*)hrndis->data;
                uint32_t* OIDInputBuffer = ((void*)&msg->RequestID) + msg->InfoBufferOffset;
                RNDIS_StatusType status  = RNDIS_STATUS_FAILURE;

                /* Verify message correctness */
                if (msg->Reserved == 0)
                {
                    uint32_t i, oid = msg->Oid;

                    /* Try to find the requested query */
                    for (i = 0; i < itf->ObjectInfoCount; i++)
                    {
                        if (itf->ObjectInfo[i].Oid == oid)
                        {
                            /* Call the set server to set the input data */
                            status = itf->ObjectInfo[i].QuerySetServer(
                                    OIDInputBuffer,
                                    &msg->InfoBufferLength);
                            break;
                        }
                    }
                }

                resp->MessageType      = REMOTE_NDIS_SET_CMPLT;
                resp->MessageLength    = sizeof(RNDIS_SetCmpltType);
                resp->Status           = status;

                /* Send notification that the control endpoint has IN data ready */
                USBD_RNDIS_ResponseReady(pdev);
                break;
            }

            case REMOTE_NDIS_RESET_MSG:
            {
                RNDIS_ResetCmpltType* resp = (RNDIS_ResetCmpltType*)hrndis->data;

                /* Reset the device by first deinitializing, then initializing again */
                if (itf->DeInit != NULL)
                {
                    itf->DeInit();
                }

                /* Flush the data endpoints */
                USBD_LL_FlushEP(pdev, RNDIS_IN_EP);
                USBD_LL_FlushEP(pdev, RNDIS_OUT_EP);

                if (itf->Init != NULL)
                {
                    itf->Init();
                }
                hrndis->TxLength = 0;

                resp->MessageType      = REMOTE_NDIS_RESET_CMPLT;
                resp->MessageLength    = sizeof(RNDIS_ResetCmpltType);
                resp->Status           = RNDIS_STATUS_SUCCESS;
                resp->AddressingReset  = 1;

                /* Send notification that the control endpoint has IN data ready */
                USBD_RNDIS_ResponseReady(pdev);
                break;
            }

            case REMOTE_NDIS_KEEPALIVE_MSG:
            {
                RNDIS_KeepAliveCmpltType* resp = (RNDIS_KeepAliveCmpltType*)hrndis->data;

                /* Always respond positively to keep-alive */
                resp->MessageType      = REMOTE_NDIS_KEEPALIVE_CMPLT;
                resp->MessageLength    = sizeof(RNDIS_KeepAliveCmpltType);
                resp->Status           = RNDIS_STATUS_SUCCESS;

                /* Send notification that the control endpoint has IN data ready */
                USBD_RNDIS_ResponseReady(pdev);
                break;
            }

            default:
                break;
        }
    }

    return USBD_OK;
}

/**
 * @brief  Data sent on non-control IN endpoint
 * @param  pdev: USB device instance
 * @param  epnum: endpoint number
 * @return Result of the operation
 */
static uint8_t USBD_RNDIS_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
    USBD_RNDIS_HandleTypeDef *hrndis = (USBD_RNDIS_HandleTypeDef*) pdev->pClassData;
    USBD_RNDIS_ItfTypeDef *itf       = (USBD_RNDIS_ItfTypeDef*) pdev->pUserData;

    if ((hrndis != NULL) && (epnum == RNDIS_IN_EP))
    {
        {
            /* Set the transmit state to: free to transmit */
            hrndis->TxLength = 0;
        }
    }
    return USBD_OK;
}

/**
 * @brief  Data received on non-control OUT endpoint
 * @param  pdev: USB device instance
 * @param  epnum: endpoint number
 * @return Result of the operation
 */
static uint8_t USBD_RNDIS_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
    USBD_RNDIS_HandleTypeDef *hrndis = (USBD_RNDIS_HandleTypeDef*) pdev->pClassData;
    USBD_RNDIS_ItfTypeDef *itf       = (USBD_RNDIS_ItfTypeDef*) pdev->pUserData;

    if ((itf->PacketReceived != NULL) && (hrndis != NULL))
    {
        RNDIS_PacketMsgType * msg = (RNDIS_PacketMsgType*)hrndis->RxMsg;
        uint32_t rxLength = USBD_LL_GetRxDataSize(pdev, epnum);

        /* Verify protocol format */
        if (RNDIS_VALID_PACKET_MSG(msg, rxLength))
        {
            /* Provide callback on successful reception */
            itf->PacketReceived(((uint8_t*)&msg->DataOffset) + msg->DataOffset, msg->DataLength);
        }
    }
    return USBD_OK;
}

/**
 * @brief  Transmits packet message through the RNDIS IN endpoint
 * @param  pdev: USB device instance
 * @param  msg: Packet
 * @return USBD_BUSY if IN transfer is already ongoing, otherwise USBD_OK
 */
uint8_t USBD_RNDIS_TransmitMessage(USBD_HandleTypeDef *pdev, RNDIS_PacketMsgType *msg)
{
    USBD_RNDIS_HandleTypeDef *hrndis = (USBD_RNDIS_HandleTypeDef*) pdev->pClassData;
    uint8_t retval = USBD_FAIL;

    if (hrndis != NULL)
    {
        retval = USBD_BUSY;

        /* If the transmit state is: free to transmit */
        if (hrndis->TxLength == 0)
        {
            /* Tx Transfer in progress */
            hrndis->TxMsg    = msg;
            hrndis->TxLength = msg->MessageLength;

            /* Transmit next packet */
            retval = USBD_LL_Transmit(pdev, RNDIS_IN_EP, (uint8_t*)msg, msg->MessageLength);
        }
    }
    return retval;
}

/**
 * @brief  Initiates reception of packet message through the RNDIS OUT endpoint.
 * @param  pdev: USB device instance
 * @param  msgBuffer: Rx Message Buffer
 * @param  size: Total Rx buffer capacity
 * @return Result of the operation
 */
uint8_t USBD_RNDIS_SetReceiveBuffer(USBD_HandleTypeDef *pdev, RNDIS_PacketMsgType *buffer, uint16_t size)
{
    USBD_RNDIS_HandleTypeDef *hrndis = (USBD_RNDIS_HandleTypeDef*) pdev->pClassData;
    uint8_t retval = USBD_FAIL;

    if (hrndis != NULL)
    {
        hrndis->RxMsg = buffer;

        /* Record the buffer capacity for the init msg parameter */
        if (hrndis->MaxTransferSize < size)
        {
            hrndis->MaxTransferSize = size;
        }

        /* Prepare Out endpoint to receive next packet */
        retval = USBD_LL_PrepareReceive(pdev, RNDIS_OUT_EP, hrndis->RxMsg, size);
    }
    return retval;
}

/**
 * @brief  Sends an RNDIS specific status indication to the host.
 * @param  pdev: USB device instance
 * @param  status: New RNDIS device status to send
 * @return Result of the operation
 */
uint8_t USBD_RNDIS_SendStatus(USBD_HandleTypeDef *pdev, RNDIS_StatusType status)
{
    USBD_RNDIS_HandleTypeDef *hrndis = (USBD_RNDIS_HandleTypeDef*) pdev->pClassData;
    uint8_t retval = USBD_FAIL;

    if ((hrndis != NULL) && (pdev->ep0_state == USBD_EP0_IDLE))
    {
        RNDIS_IndStatusMsgType* msg = (RNDIS_IndStatusMsgType*) hrndis->data;

        /* Assemble simple status message without additional information */
        msg->MessageType        = REMOTE_NDIS_INDICATE_STATUS_MSG;
        msg->MessageLength      = sizeof(RNDIS_IndStatusMsgType);
        msg->Status             = status;
        msg->StatusBufferLength = 0;
        msg->StatusBufferOffset = 0;

        /* Send notification that the control endpoint has IN data ready */
        USBD_RNDIS_ResponseReady(pdev);
    }
    return retval;
}

/**
 * @brief  Sets the RNDIS user interface to the handler
 * @param  pdev: USB device instance
 * @param  fops: RNDIS Interface callback
 * @return Result of the operation
 */
uint8_t USBD_RNDIS_RegisterInterface(USBD_HandleTypeDef *pdev, const USBD_RNDIS_ItfTypeDef *fops)
{
    uint8_t ret = USBD_FAIL;

    if (fops != NULL)
    {
        pdev->pUserData = fops;
        ret = USBD_OK;
    }

    return ret;
}

/** @} */

/** @} */

/** @} */
