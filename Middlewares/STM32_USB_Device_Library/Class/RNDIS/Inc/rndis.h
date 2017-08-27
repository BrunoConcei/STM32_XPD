/**
  ******************************************************************************
  * @file    rndis.h
  * @author  Benedek Kupper
  * @version V0.1
  * @date    2017-08-17
  * @brief   Remote Network Driver Interface Specification header
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
#ifndef __RNDIS_H_
#define __RNDIS_H_
#include <stddef.h>

/* Version administration */
#define RNDIS_MAJOR_VERSION             1
#define RNDIS_MINOR_VERSION             0


/* Object Identifier definitions */
typedef uint32_t RNDIS_OidType;
#include <rndis_oid.h>

/* RNDIS Message Types */
typedef enum
{
    REMOTE_NDIS_PACKET_MSG          = 0x00000001U, /* The host and device use this to send network data to one another. */
    REMOTE_NDIS_INITIALIZE_MSG      = 0x00000002U, /* Sent by the host to initialize the device. */
    REMOTE_NDIS_INITIALIZE_CMPLT    = 0x80000002U, /* Device response to an initialize message. */
    REMOTE_NDIS_HALT_MSG            = 0x00000003U, /* Sent by the host to halt the device. */
    REMOTE_NDIS_QUERY_MSG           = 0x00000004U, /* Sent by the host to send a query OID. */
    REMOTE_NDIS_QUERY_CMPLT         = 0x80000004U, /* Device response to a query OID. */
    REMOTE_NDIS_SET_MSG             = 0x00000005U, /* Sent by the host to send a set OID. */
    REMOTE_NDIS_SET_CMPLT           = 0x80000005U, /* Device response to a set OID. */
    REMOTE_NDIS_RESET_MSG           = 0x00000006U, /* Sent by the host to perform a soft reset on the device. */
    REMOTE_NDIS_RESET_CMPLT         = 0x80000006U, /* Device response to reset message. */
    REMOTE_NDIS_INDICATE_STATUS_MSG = 0x00000007U, /* Sent by the device to indicate its status or an error when an unrecognized message is received. */
    REMOTE_NDIS_KEEPALIVE_MSG       = 0x00000008U, /* During idle periods, sent every few seconds by the host to check that the device is still responsive. */
    REMOTE_NDIS_KEEPALIVE_CMPLT     = 0x80000008U, /* The device response to a keepalive message. */
}RNDIS_MsgType;

/* Common Status Values */
typedef enum
{
    RNDIS_STATUS_SUCCESS            = 0x00000000U, /* Success */
    RNDIS_STATUS_FAILURE            = 0xC0000001U, /* Unspecified error */
    RNDIS_STATUS_INVALID_DATA       = 0xC0010015U, /* Invalid data error */
    RNDIS_STATUS_NOT_SUPPORTED      = 0xC00000BBU, /* Unsupported request error */
    RNDIS_STATUS_MEDIA_CONNECT      = 0x4001000BU, /* Device is connected to a network medium */
    RNDIS_STATUS_MEDIA_DISCONNECT   = 0x4001000CU, /* Device is disconnected from the medium */
}RNDIS_StatusType;

/* RNDIS device status */
typedef enum
{
    RNDIS_UNINITIALIZED     = 0,   /* The device is connected to the host on a bus but is not yet configured. */
    RNDIS_BUS_INITIALIZED   = 1,   /* The RNDIS Protocol data and control channels are appropriately mapped
                                      and initialized on the device over the bus transport. */
    RNDIS_INITIALIZED       = 2,   /* The device is ready to receive any of the RNDIS control messages for suitably configuring or querying the device,
                                      to indicate device status to the host, or to reset the protocol or tear down the communication. */
    RNDIS_DATA_INITIALIZED  = 3,   /* This state is entered after the device has successfully processed all the REMOTE_NDIS_SET_MSG messages
                                      sent by the host with all the OIDs required to configure the device for data transfer,
                                      and has responded to the host with the appropriate REMOTE_NDIS_SET_CMPLT message.
                                      The device can now exchange any message allowed on the control channel,
                                      as well as the REMOTE_NDIS_PACKET_MSG messages for network data transfer on the data channel. */
}RNDIS_DeviceStatusType;

/* Generic RNDIS message format */
typedef struct
{
    RNDIS_MsgType MessageType;      /* Identifies the type of the RNDIS message */
    uint32_t MessageLength;         /* The length of this message, in bytes */
}RNDIS_GenMsgType;

/* REMOTE_NDIS_PACKET_MSG */
typedef struct
{
    RNDIS_MsgType MessageType;      /* Identifies the type of the RNDIS message and MUST be set to 0x00000001. */
    uint32_t MessageLength;         /* The total length of this RNDIS message including the header, payload, and padding. */
    uint32_t DataOffset;            /* The offset, in bytes, from the start of the DataOffset field of this message to the start of the packet data portion
                                       of the PayLoad field. This MUST be an integer multiple of 4. */
    uint32_t DataLength;            /* Specifies the number of bytes in the packet data of the PayLoad field of this message. */
    uint32_t OutOfBandDataOffset;   /* Specifies the offset, in bytes, of the first out-of-band data record in the PayLoad field,
                                       counting from the start of the DataOffset field in this message. MUST be an integer multiple of 4
                                       when out-of-band data is present or set to 0x00000000 otherwise. When there are multiple out-of-band data records,
                                       each subsequent record MUST immediately follow the previous out-of-band data record. */
    uint32_t OutOfBandDataLength;   /* Specifies, in bytes, the total length of the out-of-band data. */
    uint32_t NumOutOfBandDataElements; /* Specifies the number of out-of-band records in this message. */
    uint32_t PerPacketInfoOffset;   /* Specifies the offset, in bytes, of the start of per-packet-info data record in the PayLoad field,
                                       counting from the start of the DataOffset field in this message. MUST be an integer multiple of 4
                                       when per-packet-info data record is present or MUST be set to 0x00000000 otherwise.
                                       When there are multiple per-packet-info data records, each subsequent record MUST immediately follow the previous record. */
    uint32_t PerPacketInfoLength;   /* Specifies, in bytes, the total length of per-packet-information contained in this message. */
    uint32_t Reserved[2];           /* Reserved for future and MUST be set to zero. The host and the device MUST treat it as an error otherwise. */
#if RNDIS_DEF_OPTIONAL_FIELDS
    uint32_t Payload[0x1000];       /* Network data contained in this message. Specifically, the field consists of DataLength bytes of packet data,
                                       OutOfBandDataLength bytes of out-of-band data, and PerPacketInfoLength bytes of per-packet information,
                                       although those three sections can occur in any order. */
#endif
}RNDIS_PacketMsgType;

/* REMOTE_NDIS_INITIALIZE_MSG */
typedef struct
{
    RNDIS_MsgType MessageType;      /* Identifies the type of the RNDIS message and MUST be set to 0x00000002. */
    uint32_t MessageLength;         /* The length of this message, in bytes. MUST be set to 0x00000018. */
    uint32_t RequestID;             /* A value, generated by the host, used to match the host's sent request to the response from the device.
                                       It is the responsibility of the host to ensure the uniqueness of this value
                                       among all outstanding request messages sent to the device. */
    uint32_t MajorVersion;          /* The major version of the RNDIS protocol implemented by the host. It MUST be set to 0x00000001. */
    uint32_t MinorVersion;          /* The minor version of the RNDIS protocol implemented by the host. It MUST be set to 0x00000000. */
    uint32_t MaxTransferSize;       /* The maximum size, in bytes, of any single bus data transfer that the host expects to receive from the device.
                                       It SHOULD be set to 0x00004000. */
}RNDIS_InitMsgType;

/* REMOTE_NDIS_INITIALIZE_CMPLT */
typedef struct
{
    RNDIS_MsgType MessageType;      /* Identifies the type of the RNDIS message and MUST be set to 0x80000002. */
    uint32_t MessageLength;         /* The length of this message, in bytes. MUST be set to 0x00000030. */
    uint32_t RequestID;             /* The RequestID field of the REMOTE_NDIS_INITIALIZE_MSG message to which this message is a response. */
    RNDIS_StatusType Status;        /* The initialization status of the device. MUST be set to RNDIS_STATUS_SUCCESS (0x00000000)
                                       upon successful initialization or upon failure, and set to an appropriate error status value. */
    uint32_t MajorVersion;          /* Together with MinorVersion, the highest-numbered RNDIS Protocol version supported by the device. It MUST be set to 0x00000001. */
    uint32_t MinorVersion;          /* Together with MajorVersion, the highest-numbered RNDIS Protocol version supported by the device. It MUST be set to 0x00000000. */
    uint32_t DeviceFlags;           /* MUST be set to 0x000000010. Other values are reserved for future use. */
    uint32_t Medium;                /* Identifies the physical medium type. MUST be set to 0x000000000, which represents IEEE 802.3 wired Ethernet.
                                       Other values are reserved for future use. */
    uint32_t MaxPacketsPerTransfer; /* The maximum number of concatenated REMOTE_NDIS_PACKET_MSG messages that the device can handle
                                       in a single bus transfer to it. This value MUST be at least 1. */
    uint32_t MaxTransferSize;       /* The maximum size, in bytes, of any single bus data transfer that the device expects to receive from the host.
                                       The value MUST be at least 0x0000002C (44 bytes) for the protocol to be operational with a PacketAlignmentFactor of 4. */
    uint32_t PacketAlignmentFactor; /* The byte alignment the device expects for each RNDIS message that is part of a multimessage transfer to it.
                                       The value is specified as an exponent of 2; the host uses 2{PacketAlignmentFactor} as the alignment value. */
    uint32_t Reserved[2];           /* Reserved for future use and MUST be set to zero. It SHOULD be treated as an error otherwise. */
}RNDIS_InitCmpltType;

/* REMOTE_NDIS_HALT_MSG */
typedef struct
{
    RNDIS_MsgType MessageType;      /* Identifies the type of the RNDIS message and MUST be set to 0x00000003. */
    uint32_t MessageLength;         /* The length of this message, in bytes. MUST be set to 0x0000000C. */
    uint32_t RequestID;             /* A value generated uniquely per device by the host to track this message. */
}RNDIS_HaltMsgType;

/* REMOTE_NDIS_QUERY_MSG */
typedef struct
{
    RNDIS_MsgType MessageType;      /* Identifies the type of the RNDIS message and MUST be set to 0x00000004. */
    uint32_t MessageLength;         /* The total length, in bytes, of this message, including the header and the OIDInputBuffer. */
    uint32_t RequestID;             /* A value, generated by the host, used to match the host's sent request to the response from the device.
                                       It is the responsibility of the host to ensure the uniqueness of this value
                                       among all outstanding request messages sent to the device. */
    RNDIS_OidType Oid;              /* The integer value of the OID, for the parameter of the device being queried for.
                                       Its value is defined by the higher-layer protocol or application. */
    uint32_t InfoBufferLength;      /* The length, in bytes, of the input data required for the OID query.
                                       This MUST be set to 0 when there is no input data associated with the OID. */
    uint32_t InfoBufferOffset;      /* The offset, in bytes, from the beginning of RequestID field where the input data for the query is located in the message.
                                       This value MUST be set to 0 when there is no input data associated with the OID. */
    uint32_t Reserved;              /* Reserved for future use and MUST be set to 0. */
#if RNDIS_DEF_OPTIONAL_FIELDS
    uint32_t OIDInputBuffer[0x1000];/* The input data supplied by the host, required for the OID query request processing by the device,
                                       as per the host NDIS specification. */
#endif
}RNDIS_QueryMsgType;

/* REMOTE_NDIS_QUERY_CMPLT */
typedef struct
{
    RNDIS_MsgType MessageType;      /* Identifies the type of the RNDIS message and MUST be set to 0x80000004. */
    uint32_t MessageLength;         /* The total length of this message, in bytes, including the OIDInputBuffer, if any. */
    uint32_t RequestID;             /* The value in the RequestID field of the REMOTE_NDIS_QUERY_MSG message, to which this is a response. */
    RNDIS_StatusType Status;        /* The status of processing for the query request. */
    uint32_t InfoBufferLength;      /* The length, in bytes, of the data in the response to the query.
                                       This MUST be set to 0x00000000 when there is no OIDInputBuffer. */
    uint32_t InfoBufferOffset;      /* The offset, in bytes, from the beginning of RequestID field
                                       where the response data for the query is located in the message.
                                       This MUST be set to 0x00000000 when there is no OIDInputBuffer. */
#if RNDIS_DEF_OPTIONAL_FIELDS
    uint32_t OIDInputBuffer[0x1000];/* The response data to the OID query request as specified by the host.
                                       OIDInputBuffer is not required when the OID specification does not require any information
                                       associated with the Oid field in REMOTE_NDIS_QUERY_MSG to which this is the response. */
#endif
}RNDIS_QueryCmpltType;

/* REMOTE_NDIS_SET_MSG */
typedef struct
{
    RNDIS_MsgType MessageType;      /* Identifies the type of the RNDIS message and MUST be set to 0x00000005. */
    uint32_t MessageLength;         /* The total length, in bytes, of this message, including the header and the OIDInputBuffer. */
    uint32_t RequestID;             /* A value generated by the host and used to match the host's sent request to the response from the device.
                                       When responding to this message from the host, the device MUST use this value in the RequestID field of the response message.
                                       It is the responsibility of the host to ensure the uniqueness of this value
                                       among all outstanding request messages sent to the device. */
    RNDIS_OidType Oid;              /* The integer value of the OID, uniquely identifying a parameter of the device that is being set.
                                       Its values are defined by the higher-layer application or protocol. */
    uint32_t InfoBufferLength;      /* The length, in bytes, of the input data required for the OID query.
                                       This must be set to 0x00000014 when there is input data associated with the OID,
                                       and MUST be set to 0 when there is no input data associated with the OID. */
    uint32_t InfoBufferOffset;      /* The offset, in bytes, from the beginning of the RequestID field, where the input data for the query is located in the message.
                                       This MUST be set to 0 when there is no input data associated with the OID. */
    uint32_t Reserved;              /* Reserved for future use and MUST be set to 0. The device MUST treat it as an error otherwise. */
#if RNDIS_DEF_OPTIONAL_FIELDS
    uint32_t OIDInputBuffer[0x1000];/* The input data required for the OID set request to be processed by the device. */
#endif
}RNDIS_SetMsgType;

/* REMOTE_NDIS_SET_CMPLT */
typedef struct
{
    RNDIS_MsgType MessageType;      /* Identifies the type of the RNDIS message and MUST be set to 0x80000005. */
    uint32_t MessageLength;         /* The total length of this message, in bytes. MUST be set to 0x00000010. */
    uint32_t RequestID;             /* The value in the RequestID field of the REMOTE_NDIS_SET_MSG message, to which this is a response. */
    RNDIS_StatusType Status;        /* The status of processing for the REMOTE_NDIS_SET_MSG message request. */
}RNDIS_SetCmpltType;

/* REMOTE_NDIS_RESET_MSG */
typedef struct
{
    RNDIS_MsgType MessageType;      /* Identifies the type of the RNDIS message and MUST be set to 0x00000006. */
    uint32_t MessageLength;         /* The total length of this message in bytes. MUST be set to 0x0000000C. */
    uint32_t Reserved;              /* Reserved for future use. MUST be set to zero. */
}RNDIS_ResetMsgType;

/* REMOTE_NDIS_RESET_CMPLT */
typedef struct
{
    RNDIS_MsgType MessageType;      /* Identifies the type of the RNDIS message and MUST be set to 0x80000006. */
    uint32_t MessageLength;         /* The total length of this message in bytes. MUST be set to 0x00000010. */
    RNDIS_StatusType Status;        /* The status of processing for the REMOTE_NDIS_RESET_MSG message request by the device to which this message is the response. */
    uint32_t AddressingReset;       /* This field indicates whether the addressing information, which is the multicast address list or packet filter,
                                       has been lost during the reset operation. This MUST be set to 0x00000001
                                       if the device requires that the host to resend addressing information or MUST be set to zero otherwise. */
}RNDIS_ResetCmpltType;

/* REMOTE_NDIS_INDICATE_STATUS_MSG */
typedef struct
{
    RNDIS_MsgType MessageType;      /* Identifies the type of the RNDIS message and MUST be set to 0x00000007. */
    uint32_t MessageLength;         /* The total length of this message, in bytes, including the StatusBuffer field, if any. */
    RNDIS_StatusType Status;        /* A value indicating a status change on the device, including link state change such as media connect/disconnect,
                                       or an error value when the device receives a malformed message. */
    uint32_t StatusBufferLength;    /* The length of the StatusBuffer field, in bytes. This MUST be set to 0x00000000 when there is no StatusBuffer. */
    uint32_t StatusBufferOffset;    /* When the Status field contains an error code, StatusBufferOffset is the offset, in bytes,
                                       from the beginning of the Status field at which the DiagnosticInfoBuffer field is located in the message.
                                       This buffer contains RNDIS_DIAGNOSTIC_INFO. In this case, the StatusBuffer contains the offending message
                                       that caused the device to send the REMOTE_NDIS_INDICATE_STATUS_MSG message to the host.
                                       It is located immediately following the DiagnosticInfoBuffer. When the Status field represents a device state change
                                       such as a link state change, StatusBufferOffset is the offset, in bytes, from the beginning of the Status field
                                       at which the StatusBuffer is located. MUST be set to 0 if there is no associated status buffer. */
#if RNDIS_DEF_OPTIONAL_FIELDS
    struct {
        uint32_t DiagStatus;        /* Contains additional status information about the error itself. */
        uint32_t ErrorOffset;       /* Specifies the zero-based offset from the beginning of the offending message contained in the StatusBuffer,
                                       in bytes, at which the error was detected.*/
    }DiagInfoBuffer;                /* This field is optional. DiagnosticInfoBuffer (RNDIS_DIAGNOSTIC_INFO) MUST be included in a response
                                       to a malformed message (that is, an unsupported message type) or when a REMOTE_NDIS_PACKET_MSG is received
                                       with inappropriate content, and the device cannot respond with any other RNDIS message. */
    uint32_t StatusBuffer[0x1000];  /* This field is optional. When the Status field contains
                                       NDIS_STATUS_MEDIA_CONNECT, NDIS_STATUS_MEDIA_DISCONNECT, or NDIS_STATUS_LINK_SPEED_CHANGE,
                                       or any upper-layer defined value indicating a device state change, the StatusBuffer MUST contain
                                       any corresponding information for the specific status indication as required by the host */
#endif
}RNDIS_IndStatusMsgType;

/* REMOTE_NDIS_KEEPALIVE_MSG */
typedef struct
{
    RNDIS_MsgType MessageType;      /* Identifies the type of the RNDIS message and MUST be set to 0x00000008. */
    uint32_t MessageLength;         /* The total length of this message in bytes. MUST be set to 0x0000000C. */
    uint32_t RequestID;             /* A value, generated by the host, used to match the host sent request to the response from the device.
                                       It is the responsibility of the host to ensure the uniqueness of this value
                                       among all outstanding request messages sent to the device. */
}RNDIS_KeepAliveMsgType;

/* REMOTE_NDIS_KEEPALIVE_CMPLT */
typedef struct
{
    RNDIS_MsgType MessageType;      /* Identifies the type of the RNDIS message and MUST be set to 0x80000008. */
    uint32_t MessageLength;         /* The total length of this message, in bytes. MUST be set to 0x00000010. */
    uint32_t RequestID;             /* The value in the RequestID field of the REMOTE_NDIS_KEEPALIVE_MSG message, to which this is a response. */
    RNDIS_StatusType Status;        /* The status of processing for the REMOTE_NDIS_KEEPALIVE_MSG message request. */
}RNDIS_KeepAliveCmpltType;

#define RNDIS_VALID_PACKET_MSG(PMSG, MSG_LENGTH)                \
    (((PMSG)->MessageLength == (MSG_LENGTH)) &&                 \
     ((PMSG)->MessageType   == REMOTE_NDIS_PACKET_MSG) &&       \
     ((PMSG)->MessageLength == ((PMSG)->DataLength +            \
      (PMSG)->DataOffset + offsetof(RNDIS_PacketMsgType, DataOffset))))

#define RNDIS_CREATE_PACKET_MSG(PMSG, DATA_LENGTH)              \
    do {(PMSG)->MessageType = REMOTE_NDIS_PACKET_MSG;           \
        (PMSG)->DataOffset  = sizeof(RNDIS_PacketMsgType)       \
            - offsetof(RNDIS_PacketMsgType, DataOffset);        \
        (PMSG)->MessageLength = sizeof(RNDIS_PacketMsgType)     \
            + (DATA_LENGTH);                                    \
        (PMSG)->DataLength = (DATA_LENGTH);                     \
        (PMSG)->OutOfBandDataOffset = 0;                        \
        (PMSG)->OutOfBandDataLength = 0;                        \
        (PMSG)->NumOutOfBandDataElements = 0;                   \
        (PMSG)->PerPacketInfoOffset = 0;                        \
        (PMSG)->PerPacketInfoLength = 0;                        \
        (PMSG)->Reserved[0] = (PMSG)->Reserved[1] = 0; } while (0)


#define RNDIS_MSG_PAYLOAD(MSG_TYPE, PMSG)               \
    (((void*)PMSG) + sizeof(MSG_TYPE))

/* NDIS Mediums */
#define NDIS_MEDIUM_802_3                       0x00000000
#define NDIS_MEDIUM_802_5                       0x00000001
#define NDIS_MEDIUM_FDDI                        0x00000002
#define NDIS_MEDIUM_WAN                         0x00000003
#define NDIS_MEDIUM_LOCAL_TALK                  0x00000004
#define NDIS_MEDIUM_DIX                         0x00000005
#define NDIS_MEDIUM_ARCENT_RAW                  0x00000006
#define NDIS_MEDIUM_ARCENT_878_2                0x00000007
#define NDIS_MEDIUM_ATM                         0x00000008
#define NDIS_MEDIUM_WIRELESS_LAN                0x00000009
#define NDIS_MEDIUM_IRDA                        0x0000000A
#define NDIS_MEDIUM_BPC                         0x0000000B
#define NDIS_MEDIUM_CO_WAN                      0x0000000C
#define NDIS_MEDIUM_1394                        0x0000000D

/* NDIS Media States */
#define NDIS_MEDIA_STATE_CONNECTED              0x00000000
#define NDIS_MEDIA_STATE_DISCONNECTED           0x00000001

/* NDIS Packet Filter Flags */
#define NDIS_PACKET_TYPE_DIRECTED               0x00000001
#define NDIS_PACKET_TYPE_MULTICAST              0x00000002
#define NDIS_PACKET_TYPE_ALL_MULTICAST          0x00000004
#define NDIS_PACKET_TYPE_BROADCAST              0x00000008
#define NDIS_PACKET_TYPE_SOURCE_ROUTING         0x00000010
#define NDIS_PACKET_TYPE_PROMISCUOUS            0x00000020
#define NDIS_PACKET_TYPE_SMT                    0x00000040
#define NDIS_PACKET_TYPE_ALL_LOCAL              0x00000080
#define NDIS_PACKET_TYPE_GROUP                  0x00000100
#define NDIS_PACKET_TYPE_ALL_FUNCTIONAL         0x00000200
#define NDIS_PACKET_TYPE_FUNCTIONAL             0x00000400
#define NDIS_PACKET_TYPE_MAC_FRAME              0x00000800

#endif /* __RNDIS_H_ */
