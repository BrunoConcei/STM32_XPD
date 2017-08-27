/**
  ******************************************************************************
  * @file    rndis_oid.h
  * @author  Benedek Kupper
  * @version V0.1
  * @date    2017-08-17
  * @brief   Remote Network Driver Interface Specification Object Identifiers
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
#ifndef __RNDIS_OID_H_
#define __RNDIS_OID_H_

/* Required OIDs */
#define OID_GEN_SUPPORTED_LIST                  0x00010101 /* Implemented in usbd_rndis.c */
#define OID_GEN_HARDWARE_STATUS                 0x00010102
#define OID_GEN_MEDIA_SUPPORTED                 0x00010103
#define OID_GEN_MEDIA_IN_USE                    0x00010104
#define OID_GEN_MAXIMUM_LOOKAHEAD               0x00010105
#define OID_GEN_MAXIMUM_FRAME_SIZE              0x00010106
#define OID_GEN_LINK_SPEED                      0x00010107
#define OID_GEN_TRANSMIT_BUFFER_SPACE           0x00010108
#define OID_GEN_RECEIVE_BUFFER_SPACE            0x00010109
#define OID_GEN_TRANSMIT_BLOCK_SIZE             0x0001010A
#define OID_GEN_RECEIVE_BLOCK_SIZE              0x0001010B
#define OID_GEN_VENDOR_ID                       0x0001010C
#define OID_GEN_VENDOR_DESCRIPTION              0x0001010D
#define OID_GEN_CURRENT_PACKET_FILTER           0x0001010E
#define OID_GEN_CURRENT_LOOKAHEAD               0x0001010F
#define OID_GEN_DRIVER_VERSION                  0x00010110
#define OID_GEN_MAXIMUM_TOTAL_SIZE              0x00010111
#define OID_GEN_PROTOCOL_OPTIONS                0x00010112
#define OID_GEN_MAC_OPTIONS                     0x00010113
#define OID_GEN_MEDIA_CONNECT_STATUS            0x00010114
#define OID_GEN_MAXIMUM_SEND_PACKETS            0x00010115

/* Optional OIDs */
#define OID_GEN_VENDOR_DRIVER_VERSION           0x00010116
#define OID_GEN_SUPPORTED_GUIDS                 0x00010117
#define OID_GEN_NETWORK_LAYER_ADDRESSES         0x00010118  /* Set only */
#define OID_GEN_TRANSPORT_HEADER_OFFSET         0x00010119  /* Set only */
#define OID_GEN_MEDIA_CAPABILITIES              0x00010201
#define OID_GEN_PHYSICAL_MEDIUM                 0x00010202

/* new optional for NDIS 6.0 */
#define OID_GEN_RECEIVE_SCALE_CAPABILITIES      0x00010203  /* Query only */
#define OID_GEN_RECEIVE_SCALE_PARAMETERS        0x00010204

/* new for NDIS 6.0. NDIS will handle on behalf of the miniports */
#define OID_GEN_MAC_ADDRESS                     0x00010205
#define OID_GEN_MAX_LINK_SPEED                  0x00010206  /* Query only */
#define OID_GEN_LINK_STATE                      0x00010207  /* Query only */

/* new and required for NDIS 6 miniports */
#define OID_GEN_LINK_PARAMETERS                 0x00010208  /* Set only */
#define OID_GEN_INTERRUPT_MODERATION            0x00010209
#define OID_GEN_NDIS_RESERVED_3                 0x0001020A
#define OID_GEN_NDIS_RESERVED_4                 0x0001020B
#define OID_GEN_NDIS_RESERVED_5                 0x0001020C


/* Port related OIDs */
#define OID_GEN_ENUMERATE_PORTS                 0x0001020D  /* Query only, handled by NDIS */
#define OID_GEN_PORT_STATE                      0x0001020E  /* Query only, handled by NDIS */
#define OID_GEN_PORT_AUTHENTICATION_PARAMETERS  0x0001020F  /* Set only */

/* optional OID for NDIS 6 miniports */
#define OID_GEN_TIMEOUT_DPC_REQUEST_CAPABILITIES 0x00010210 /* Query only */

/* this OID is handled by NDIS for PCI devices */
#define OID_GEN_PCI_DEVICE_CUSTOM_PROPERTIES    0x00010211  /* Query only */
#define OID_GEN_NDIS_RESERVED_6                 0x00010212
#define OID_GEN_PHYSICAL_MEDIUM_EX              0x00010213  /* Query only */


#define OID_GEN_MACHINE_NAME                    0x0001021A  /* Set only */
#define OID_GEN_RNDIS_CONFIG_PARAMETER          0x0001021B  /* Set only */
#define OID_GEN_VLAN_ID                         0x0001021C

#define OID_GEN_RECEIVE_HASH                    0x0001021F  /* Query and set */
#define OID_GEN_MINIPORT_RESTART_ATTRIBUTES     0x0001021D

/* Optional OID for header data/split */
#define OID_GEN_HD_SPLIT_PARAMETERS             0x0001021E  /* Set only */
#define OID_GEN_HD_SPLIT_CURRENT_CONFIG         0x00010220  /* Query only */

/* the following OIDs are used in querying interfaces */
#define OID_GEN_PROMISCUOUS_MODE                0x00010280  /* used in querying interfaces */
#define OID_GEN_LAST_CHANGE                     0x00010281  /* used in querying interfaces */
#define OID_GEN_DISCONTINUITY_TIME              0x00010282  /* used in querying interfaces */
#define OID_GEN_OPERATIONAL_STATUS              0x00010283  /* used in querying interfaces */
#define OID_GEN_XMIT_LINK_SPEED                 0x00010284  /* used in querying interfaces */
#define OID_GEN_RCV_LINK_SPEED                  0x00010285  /* used in querying interfaces */
#define OID_GEN_UNKNOWN_PROTOS                  0x00010286  /* used in querying interfaces */
#define OID_GEN_INTERFACE_INFO                  0x00010287  /* used in querying interfaces */
#define OID_GEN_ADMIN_STATUS                    0x00010288  /* used in querying interfaces */
#define OID_GEN_ALIAS                           0x00010289  /* used in querying interfaces */
#define OID_GEN_MEDIA_CONNECT_STATUS_EX         0x0001028A  /* used in querying interfaces */
#define OID_GEN_LINK_SPEED_EX                   0x0001028B  /* used in querying interfaces */
#define OID_GEN_MEDIA_DUPLEX_STATE              0x0001028C  /* used in querying interfaces */
#define OID_GEN_IP_OPER_STATUS                  0x0001028D  /* used in querying interfaces */


/*  Required statistics */
#define OID_GEN_XMIT_OK                         0x00020101
#define OID_GEN_RCV_OK                          0x00020102
#define OID_GEN_XMIT_ERROR                      0x00020103
#define OID_GEN_RCV_ERROR                       0x00020104
#define OID_GEN_RCV_NO_BUFFER                   0x00020105

/* mandatory for NDIS 6.0 and higher miniports */
#define OID_GEN_STATISTICS                      0x00020106

/*  Optional statistics */
#define OID_GEN_DIRECTED_BYTES_XMIT             0x00020201
#define OID_GEN_DIRECTED_FRAMES_XMIT            0x00020202
#define OID_GEN_MULTICAST_BYTES_XMIT            0x00020203
#define OID_GEN_MULTICAST_FRAMES_XMIT           0x00020204
#define OID_GEN_BROADCAST_BYTES_XMIT            0x00020205
#define OID_GEN_BROADCAST_FRAMES_XMIT           0x00020206
#define OID_GEN_DIRECTED_BYTES_RCV              0x00020207
#define OID_GEN_DIRECTED_FRAMES_RCV             0x00020208
#define OID_GEN_MULTICAST_BYTES_RCV             0x00020209
#define OID_GEN_MULTICAST_FRAMES_RCV            0x0002020A
#define OID_GEN_BROADCAST_BYTES_RCV             0x0002020B
#define OID_GEN_BROADCAST_FRAMES_RCV            0x0002020C
#define OID_GEN_RCV_CRC_ERROR                   0x0002020D
#define OID_GEN_TRANSMIT_QUEUE_LENGTH           0x0002020E

#define OID_GEN_GET_TIME_CAPS                   0x0002020F
#define OID_GEN_GET_NETCARD_TIME                0x00020210
#define OID_GEN_NETCARD_LOAD                    0x00020211
#define OID_GEN_DEVICE_PROFILE                  0x00020212


/* WWAN specific oids */
#define OID_WWAN_DRIVER_CAPS                    0x0e010100
#define OID_WWAN_DEVICE_CAPS                    0x0e010101
#define OID_WWAN_READY_INFO                     0x0e010102
#define OID_WWAN_RADIO_STATE                    0x0e010103
#define OID_WWAN_PIN                            0x0e010104
#define OID_WWAN_PIN_LIST                       0x0e010105
#define OID_WWAN_HOME_PROVIDER                  0x0e010106
#define OID_WWAN_PREFERRED_PROVIDERS            0x0e010107
#define OID_WWAN_VISIBLE_PROVIDERS              0x0e010108
#define OID_WWAN_REGISTER_STATE                 0x0e010109
#define OID_WWAN_PACKET_SERVICE                 0x0e01010a
#define OID_WWAN_SIGNAL_STATE                   0x0e01010b
#define OID_WWAN_CONNECT                        0x0e01010c
#define OID_WWAN_PROVISIONED_CONTEXTS           0x0e01010d
#define OID_WWAN_SERVICE_ACTIVATION             0x0e01010e
#define OID_WWAN_SMS_CONFIGURATION              0x0e01010f
#define OID_WWAN_SMS_READ                       0x0e010110
#define OID_WWAN_SMS_SEND                       0x0e010111
#define OID_WWAN_SMS_DELETE                     0x0e010112
#define OID_WWAN_SMS_STATUS                     0x0e010113
#define OID_WWAN_VENDOR_SPECIFIC                0x0e010114


#define OID_WWAN_AUTH_CHALLENGE                     0x0e010115
#define OID_WWAN_ENUMERATE_DEVICE_SERVICES          0x0e010116
#define OID_WWAN_SUBSCRIBE_DEVICE_SERVICE_EVENTS    0x0e010117
#define OID_WWAN_DEVICE_SERVICE_COMMAND             0x0e010118
#define OID_WWAN_USSD                               0x0e010119
#define OID_WWAN_PIN_EX                             0x0e010121
#define OID_WWAN_ENUMERATE_DEVICE_SERVICE_COMMANDS  0x0e010122
#define OID_WWAN_DEVICE_SERVICE_SESSION             0x0e010123
#define OID_WWAN_DEVICE_SERVICE_SESSION_WRITE       0x0e010124
#define OID_WWAN_PREFERRED_MULTICARRIER_PROVIDERS   0x0e010125
#define OID_WWAN_CREATE_MAC                         0x0e010126
#define OID_WWAN_DELETE_MAC                         0x0e010127
#define OID_WWAN_UICC_FILE_STATUS                   0x0e010128
#define OID_WWAN_UICC_ACCESS_BINARY                 0x0e010129
#define OID_WWAN_UICC_ACCESS_RECORD                 0x0e01012a
#define OID_WWAN_PIN_EX2                            0x0e01012b
#define OID_WWAN_MBIM_VERSION                       0x0e01012c
#define OID_WWAN_SYS_CAPS                           0x0e01012d
#define OID_WWAN_DEVICE_CAPS_EX                     0x0e01012e
#define OID_WWAN_SYS_SLOTMAPPINGS                   0x0e01012f
#define OID_WWAN_SLOT_INFO_STATUS                   0x0e010130
#define OID_WWAN_DEVICE_BINDINGS                    0x0e010131
#define OID_WWAN_REGISTER_STATE_EX                  0x0e010132
#define OID_WWAN_IMS_VOICE_STATE                    0x0e010133
#define OID_WWAN_SIGNAL_STATE_EX                    0x0e010134
#define OID_WWAN_LOCATION_STATE                     0x0e010135
#define OID_WWAN_NITZ                               0x0e010136
#define OID_WWAN_NETWORK_IDLE_HINT                  0x0e010137


/* The following are exported by NDIS itself and are only queryable. */

/* the time in milliseconds a driver took to initialize. */
#define OID_GEN_INIT_TIME_MS                    0x00020213

/* the number of times the miniport adapter was reset */
#define OID_GEN_RESET_COUNTS                    0x00020214

/* the number of timer the miniport reported a media state change */
#define OID_GEN_MEDIA_SENSE_COUNTS              0x00020215

/* the friendly name of the adapter */
#define OID_GEN_FRIENDLY_NAME                   0x00020216

/* returns miniport information such as whether the driver is serialized or not
 * if it supports sending multiple packets, etc. refer to NDIS_MINIPORT_XXX flags */
#define OID_GEN_NDIS_RESERVED_1                 0x00020217

/* handled by NDIS to reset the test verification parameters on the miniport */
#define OID_GEN_NDIS_RESERVED_2                 0x00020218
#define OID_GEN_NDIS_RESERVED_5                 0x0001020C

/* more optional OIDs new for NDIS 6.0 */
#define OID_GEN_BYTES_RCV                       0x00020219
#define OID_GEN_BYTES_XMIT                      0x0002021A
#define OID_GEN_RCV_DISCARDS                    0x0002021B
#define OID_GEN_XMIT_DISCARDS                   0x0002021C

/* Optional OIDs for NDIS 6.30 */
#define OID_TCP_RSC_STATISTICS                  0x0002021D

#define OID_GEN_NDIS_RESERVED_7                 0x0002021E


/*  These are connection-oriented general OIDs.
 *  These replace the above OIDs for connection-oriented media. */
#define OID_GEN_CO_SUPPORTED_LIST               OID_GEN_SUPPORTED_LIST
#define OID_GEN_CO_HARDWARE_STATUS              OID_GEN_HARDWARE_STATUS
#define OID_GEN_CO_MEDIA_SUPPORTED              OID_GEN_MEDIA_SUPPORTED
#define OID_GEN_CO_MEDIA_IN_USE                 OID_GEN_MEDIA_IN_USE
#define OID_GEN_CO_LINK_SPEED                   OID_GEN_LINK_SPEED
#define OID_GEN_CO_VENDOR_ID                    OID_GEN_VENDOR_ID
#define OID_GEN_CO_VENDOR_DESCRIPTION           OID_GEN_VENDOR_DESCRIPTION
#define OID_GEN_CO_DRIVER_VERSION               OID_GEN_DRIVER_VERSION
#define OID_GEN_CO_PROTOCOL_OPTIONS             OID_GEN_PROTOCOL_OPTIONS
#define OID_GEN_CO_MAC_OPTIONS                  OID_GEN_MAC_OPTIONS
#define OID_GEN_CO_MEDIA_CONNECT_STATUS         OID_GEN_MEDIA_CONNECT_STATUS
#define OID_GEN_CO_VENDOR_DRIVER_VERSION        OID_GEN_VENDOR_DRIVER_VERSION
#define OID_GEN_CO_SUPPORTED_GUIDS              OID_GEN_SUPPORTED_GUIDS
#define OID_GEN_CO_GET_TIME_CAPS                OID_GEN_GET_TIME_CAPS
#define OID_GEN_CO_GET_NETCARD_TIME             OID_GEN_GET_NETCARD_TIME
#define OID_GEN_CO_MINIMUM_LINK_SPEED           0x00020120

/*  These are connection-oriented statistics OIDs. */
#define OID_GEN_CO_XMIT_PDUS_OK                 OID_GEN_XMIT_OK
#define OID_GEN_CO_RCV_PDUS_OK                  OID_GEN_RCV_OK
#define OID_GEN_CO_XMIT_PDUS_ERROR              OID_GEN_XMIT_ERROR
#define OID_GEN_CO_RCV_PDUS_ERROR               OID_GEN_RCV_ERROR
#define OID_GEN_CO_RCV_PDUS_NO_BUFFER           OID_GEN_RCV_NO_BUFFER


#define OID_GEN_CO_RCV_CRC_ERROR                OID_GEN_RCV_CRC_ERROR
#define OID_GEN_CO_TRANSMIT_QUEUE_LENGTH        OID_GEN_TRANSMIT_QUEUE_LENGTH
#define OID_GEN_CO_BYTES_XMIT                   OID_GEN_DIRECTED_BYTES_XMIT
#define OID_GEN_CO_BYTES_RCV                    OID_GEN_DIRECTED_BYTES_RCV
#define OID_GEN_CO_NETCARD_LOAD                 OID_GEN_NETCARD_LOAD
#define OID_GEN_CO_DEVICE_PROFILE               OID_GEN_DEVICE_PROFILE
#define OID_GEN_CO_BYTES_XMIT_OUTSTANDING       0x00020221


/* 802.3 Objects (Ethernet) */
#define OID_802_3_PERMANENT_ADDRESS             0x01010101
#define OID_802_3_CURRENT_ADDRESS               0x01010102
#define OID_802_3_MULTICAST_LIST                0x01010103
#define OID_802_3_MAXIMUM_LIST_SIZE             0x01010104
/* This OID has been deprecated for NDIS 6 drivers. */
#define OID_802_3_MAC_OPTIONS                   0x01010105  /* deprecated */


/* This Flag has been deprecated for NDIS 6 drivers. */
#define NDIS_802_3_MAC_OPTION_PRIORITY          0x00000001  /* deprecated */

#define OID_802_3_RCV_ERROR_ALIGNMENT           0x01020101
#define OID_802_3_XMIT_ONE_COLLISION            0x01020102
#define OID_802_3_XMIT_MORE_COLLISIONS          0x01020103

#define OID_802_3_XMIT_DEFERRED                 0x01020201
#define OID_802_3_XMIT_MAX_COLLISIONS           0x01020202
#define OID_802_3_RCV_OVERRUN                   0x01020203
#define OID_802_3_XMIT_UNDERRUN                 0x01020204
#define OID_802_3_XMIT_HEARTBEAT_FAILURE        0x01020205
#define OID_802_3_XMIT_TIMES_CRS_LOST           0x01020206
#define OID_802_3_XMIT_LATE_COLLISIONS          0x01020207

/* new for NDIS 6 */
#define OID_802_3_ADD_MULTICAST_ADDRESS         0x01010208
#define OID_802_3_DELETE_MULTICAST_ADDRESS      0x01010209


/* 802.5 Objects (Token-Ring) */
#define OID_802_5_PERMANENT_ADDRESS             0x02010101
#define OID_802_5_CURRENT_ADDRESS               0x02010102
#define OID_802_5_CURRENT_FUNCTIONAL            0x02010103
#define OID_802_5_CURRENT_GROUP                 0x02010104
#define OID_802_5_LAST_OPEN_STATUS              0x02010105
#define OID_802_5_CURRENT_RING_STATUS           0x02010106
#define OID_802_5_CURRENT_RING_STATE            0x02010107


#define OID_802_5_LINE_ERRORS                   0x02020101
#define OID_802_5_LOST_FRAMES                   0x02020102

#define OID_802_5_BURST_ERRORS                  0x02020201
#define OID_802_5_AC_ERRORS                     0x02020202
#define OID_802_5_ABORT_DELIMETERS              0x02020203
#define OID_802_5_FRAME_COPIED_ERRORS           0x02020204
#define OID_802_5_FREQUENCY_ERRORS              0x02020205
#define OID_802_5_TOKEN_ERRORS                  0x02020206
#define OID_802_5_INTERNAL_ERRORS               0x02020207


/* FDDI Objects */
#define OID_FDDI_LONG_PERMANENT_ADDR            0x03010101
#define OID_FDDI_LONG_CURRENT_ADDR              0x03010102
#define OID_FDDI_LONG_MULTICAST_LIST            0x03010103
#define OID_FDDI_LONG_MAX_LIST_SIZE             0x03010104
#define OID_FDDI_SHORT_PERMANENT_ADDR           0x03010105
#define OID_FDDI_SHORT_CURRENT_ADDR             0x03010106
#define OID_FDDI_SHORT_MULTICAST_LIST           0x03010107
#define OID_FDDI_SHORT_MAX_LIST_SIZE            0x03010108

#define OID_FDDI_ATTACHMENT_TYPE                0x03020101
#define OID_FDDI_UPSTREAM_NODE_LONG             0x03020102
#define OID_FDDI_DOWNSTREAM_NODE_LONG           0x03020103
#define OID_FDDI_FRAME_ERRORS                   0x03020104
#define OID_FDDI_FRAMES_LOST                    0x03020105
#define OID_FDDI_RING_MGT_STATE                 0x03020106
#define OID_FDDI_LCT_FAILURES                   0x03020107
#define OID_FDDI_LEM_REJECTS                    0x03020108
#define OID_FDDI_LCONNECTION_STATE              0x03020109

#define OID_FDDI_SMT_STATION_ID                 0x03030201
#define OID_FDDI_SMT_OP_VERSION_ID              0x03030202
#define OID_FDDI_SMT_HI_VERSION_ID              0x03030203
#define OID_FDDI_SMT_LO_VERSION_ID              0x03030204
#define OID_FDDI_SMT_MANUFACTURER_DATA          0x03030205
#define OID_FDDI_SMT_USER_DATA                  0x03030206
#define OID_FDDI_SMT_MIB_VERSION_ID             0x03030207
#define OID_FDDI_SMT_MAC_CT                     0x03030208
#define OID_FDDI_SMT_NON_MASTER_CT              0x03030209
#define OID_FDDI_SMT_MASTER_CT                  0x0303020A
#define OID_FDDI_SMT_AVAILABLE_PATHS            0x0303020B
#define OID_FDDI_SMT_CONFIG_CAPABILITIES        0x0303020C
#define OID_FDDI_SMT_CONFIG_POLICY              0x0303020D
#define OID_FDDI_SMT_CONNECTION_POLICY          0x0303020E
#define OID_FDDI_SMT_T_NOTIFY                   0x0303020F
#define OID_FDDI_SMT_STAT_RPT_POLICY            0x03030210
#define OID_FDDI_SMT_TRACE_MAX_EXPIRATION       0x03030211
#define OID_FDDI_SMT_PORT_INDEXES               0x03030212
#define OID_FDDI_SMT_MAC_INDEXES                0x03030213
#define OID_FDDI_SMT_BYPASS_PRESENT             0x03030214
#define OID_FDDI_SMT_ECM_STATE                  0x03030215
#define OID_FDDI_SMT_CF_STATE                   0x03030216
#define OID_FDDI_SMT_HOLD_STATE                 0x03030217
#define OID_FDDI_SMT_REMOTE_DISCONNECT_FLAG     0x03030218
#define OID_FDDI_SMT_STATION_STATUS             0x03030219
#define OID_FDDI_SMT_PEER_WRAP_FLAG             0x0303021A
#define OID_FDDI_SMT_MSG_TIME_STAMP             0x0303021B
#define OID_FDDI_SMT_TRANSITION_TIME_STAMP      0x0303021C
#define OID_FDDI_SMT_SET_COUNT                  0x0303021D
#define OID_FDDI_SMT_LAST_SET_STATION_ID        0x0303021E
#define OID_FDDI_MAC_FRAME_STATUS_FUNCTIONS     0x0303021F
#define OID_FDDI_MAC_BRIDGE_FUNCTIONS           0x03030220
#define OID_FDDI_MAC_T_MAX_CAPABILITY           0x03030221
#define OID_FDDI_MAC_TVX_CAPABILITY             0x03030222
#define OID_FDDI_MAC_AVAILABLE_PATHS            0x03030223
#define OID_FDDI_MAC_CURRENT_PATH               0x03030224
#define OID_FDDI_MAC_UPSTREAM_NBR               0x03030225
#define OID_FDDI_MAC_DOWNSTREAM_NBR             0x03030226
#define OID_FDDI_MAC_OLD_UPSTREAM_NBR           0x03030227
#define OID_FDDI_MAC_OLD_DOWNSTREAM_NBR         0x03030228
#define OID_FDDI_MAC_DUP_ADDRESS_TEST           0x03030229
#define OID_FDDI_MAC_REQUESTED_PATHS            0x0303022A
#define OID_FDDI_MAC_DOWNSTREAM_PORT_TYPE       0x0303022B
#define OID_FDDI_MAC_INDEX                      0x0303022C
#define OID_FDDI_MAC_SMT_ADDRESS                0x0303022D
#define OID_FDDI_MAC_LONG_GRP_ADDRESS           0x0303022E
#define OID_FDDI_MAC_SHORT_GRP_ADDRESS          0x0303022F
#define OID_FDDI_MAC_T_REQ                      0x03030230
#define OID_FDDI_MAC_T_NEG                      0x03030231
#define OID_FDDI_MAC_T_MAX                      0x03030232
#define OID_FDDI_MAC_TVX_VALUE                  0x03030233
#define OID_FDDI_MAC_T_PRI0                     0x03030234
#define OID_FDDI_MAC_T_PRI1                     0x03030235
#define OID_FDDI_MAC_T_PRI2                     0x03030236
#define OID_FDDI_MAC_T_PRI3                     0x03030237
#define OID_FDDI_MAC_T_PRI4                     0x03030238
#define OID_FDDI_MAC_T_PRI5                     0x03030239
#define OID_FDDI_MAC_T_PRI6                     0x0303023A
#define OID_FDDI_MAC_FRAME_CT                   0x0303023B
#define OID_FDDI_MAC_COPIED_CT                  0x0303023C
#define OID_FDDI_MAC_TRANSMIT_CT                0x0303023D
#define OID_FDDI_MAC_TOKEN_CT                   0x0303023E
#define OID_FDDI_MAC_ERROR_CT                   0x0303023F
#define OID_FDDI_MAC_LOST_CT                    0x03030240
#define OID_FDDI_MAC_TVX_EXPIRED_CT             0x03030241
#define OID_FDDI_MAC_NOT_COPIED_CT              0x03030242
#define OID_FDDI_MAC_LATE_CT                    0x03030243
#define OID_FDDI_MAC_RING_OP_CT                 0x03030244
#define OID_FDDI_MAC_FRAME_ERROR_THRESHOLD      0x03030245
#define OID_FDDI_MAC_FRAME_ERROR_RATIO          0x03030246
#define OID_FDDI_MAC_NOT_COPIED_THRESHOLD       0x03030247
#define OID_FDDI_MAC_NOT_COPIED_RATIO           0x03030248
#define OID_FDDI_MAC_RMT_STATE                  0x03030249
#define OID_FDDI_MAC_DA_FLAG                    0x0303024A
#define OID_FDDI_MAC_UNDA_FLAG                  0x0303024B
#define OID_FDDI_MAC_FRAME_ERROR_FLAG           0x0303024C
#define OID_FDDI_MAC_NOT_COPIED_FLAG            0x0303024D
#define OID_FDDI_MAC_MA_UNITDATA_AVAILABLE      0x0303024E
#define OID_FDDI_MAC_HARDWARE_PRESENT           0x0303024F
#define OID_FDDI_MAC_MA_UNITDATA_ENABLE         0x03030250
#define OID_FDDI_PATH_INDEX                     0x03030251
#define OID_FDDI_PATH_RING_LATENCY              0x03030252
#define OID_FDDI_PATH_TRACE_STATUS              0x03030253
#define OID_FDDI_PATH_SBA_PAYLOAD               0x03030254
#define OID_FDDI_PATH_SBA_OVERHEAD              0x03030255
#define OID_FDDI_PATH_CONFIGURATION             0x03030256
#define OID_FDDI_PATH_T_R_MODE                  0x03030257
#define OID_FDDI_PATH_SBA_AVAILABLE             0x03030258
#define OID_FDDI_PATH_TVX_LOWER_BOUND           0x03030259
#define OID_FDDI_PATH_T_MAX_LOWER_BOUND         0x0303025A
#define OID_FDDI_PATH_MAX_T_REQ                 0x0303025B
#define OID_FDDI_PORT_MY_TYPE                   0x0303025C
#define OID_FDDI_PORT_NEIGHBOR_TYPE             0x0303025D
#define OID_FDDI_PORT_CONNECTION_POLICIES       0x0303025E
#define OID_FDDI_PORT_MAC_INDICATED             0x0303025F
#define OID_FDDI_PORT_CURRENT_PATH              0x03030260
#define OID_FDDI_PORT_REQUESTED_PATHS           0x03030261
#define OID_FDDI_PORT_MAC_PLACEMENT             0x03030262
#define OID_FDDI_PORT_AVAILABLE_PATHS           0x03030263
#define OID_FDDI_PORT_MAC_LOOP_TIME             0x03030264
#define OID_FDDI_PORT_PMD_CLASS                 0x03030265
#define OID_FDDI_PORT_CONNECTION_CAPABILITIES   0x03030266
#define OID_FDDI_PORT_INDEX                     0x03030267
#define OID_FDDI_PORT_MAINT_LS                  0x03030268
#define OID_FDDI_PORT_BS_FLAG                   0x03030269
#define OID_FDDI_PORT_PC_LS                     0x0303026A
#define OID_FDDI_PORT_EB_ERROR_CT               0x0303026B
#define OID_FDDI_PORT_LCT_FAIL_CT               0x0303026C
#define OID_FDDI_PORT_LER_ESTIMATE              0x0303026D
#define OID_FDDI_PORT_LEM_REJECT_CT             0x0303026E
#define OID_FDDI_PORT_LEM_CT                    0x0303026F
#define OID_FDDI_PORT_LER_CUTOFF                0x03030270
#define OID_FDDI_PORT_LER_ALARM                 0x03030271
#define OID_FDDI_PORT_CONNNECT_STATE            0x03030272
#define OID_FDDI_PORT_PCM_STATE                 0x03030273
#define OID_FDDI_PORT_PC_WITHHOLD               0x03030274
#define OID_FDDI_PORT_LER_FLAG                  0x03030275
#define OID_FDDI_PORT_HARDWARE_PRESENT          0x03030276
#define OID_FDDI_SMT_STATION_ACTION             0x03030277
#define OID_FDDI_PORT_ACTION                    0x03030278
#define OID_FDDI_IF_DESCR                       0x03030279
#define OID_FDDI_IF_TYPE                        0x0303027A
#define OID_FDDI_IF_MTU                         0x0303027B
#define OID_FDDI_IF_SPEED                       0x0303027C
#define OID_FDDI_IF_PHYS_ADDRESS                0x0303027D
#define OID_FDDI_IF_ADMIN_STATUS                0x0303027E
#define OID_FDDI_IF_OPER_STATUS                 0x0303027F
#define OID_FDDI_IF_LAST_CHANGE                 0x03030280
#define OID_FDDI_IF_IN_OCTETS                   0x03030281
#define OID_FDDI_IF_IN_UCAST_PKTS               0x03030282
#define OID_FDDI_IF_IN_NUCAST_PKTS              0x03030283
#define OID_FDDI_IF_IN_DISCARDS                 0x03030284
#define OID_FDDI_IF_IN_ERRORS                   0x03030285
#define OID_FDDI_IF_IN_UNKNOWN_PROTOS           0x03030286
#define OID_FDDI_IF_OUT_OCTETS                  0x03030287
#define OID_FDDI_IF_OUT_UCAST_PKTS              0x03030288
#define OID_FDDI_IF_OUT_NUCAST_PKTS             0x03030289
#define OID_FDDI_IF_OUT_DISCARDS                0x0303028A
#define OID_FDDI_IF_OUT_ERRORS                  0x0303028B
#define OID_FDDI_IF_OUT_QLEN                    0x0303028C
#define OID_FDDI_IF_SPECIFIC                    0x0303028D

/* WAN objects */
#define OID_WAN_PERMANENT_ADDRESS               0x04010101
#define OID_WAN_CURRENT_ADDRESS                 0x04010102
#define OID_WAN_QUALITY_OF_SERVICE              0x04010103
#define OID_WAN_PROTOCOL_TYPE                   0x04010104
#define OID_WAN_MEDIUM_SUBTYPE                  0x04010105
#define OID_WAN_HEADER_FORMAT                   0x04010106

#define OID_WAN_GET_INFO                        0x04010107
#define OID_WAN_SET_LINK_INFO                   0x04010108
#define OID_WAN_GET_LINK_INFO                   0x04010109

#define OID_WAN_LINE_COUNT                      0x0401010A
#define OID_WAN_PROTOCOL_CAPS                   0x0401010B

#define OID_WAN_GET_BRIDGE_INFO                 0x0401020A
#define OID_WAN_SET_BRIDGE_INFO                 0x0401020B
#define OID_WAN_GET_COMP_INFO                   0x0401020C
#define OID_WAN_SET_COMP_INFO                   0x0401020D
#define OID_WAN_GET_STATS_INFO                  0x0401020E

/* These are connection-oriented WAN OIDs.
 * These replace the above OIDs for CoNDIS WAN Miniports */
#define OID_WAN_CO_GET_INFO                     0x04010180
#define OID_WAN_CO_SET_LINK_INFO                0x04010181
#define OID_WAN_CO_GET_LINK_INFO                0x04010182
#define OID_WAN_CO_GET_COMP_INFO                0x04010280
#define OID_WAN_CO_SET_COMP_INFO                0x04010281
#define OID_WAN_CO_GET_STATS_INFO               0x04010282


/* LocalTalk objects */
#define OID_LTALK_CURRENT_NODE_ID               0x05010102

#define OID_LTALK_IN_BROADCASTS                 0x05020101
#define OID_LTALK_IN_LENGTH_ERRORS              0x05020102

#define OID_LTALK_OUT_NO_HANDLERS               0x05020201
#define OID_LTALK_COLLISIONS                    0x05020202
#define OID_LTALK_DEFERS                        0x05020203
#define OID_LTALK_NO_DATA_ERRORS                0x05020204
#define OID_LTALK_RANDOM_CTS_ERRORS             0x05020205
#define OID_LTALK_FCS_ERRORS                    0x05020206


/* Arcnet objects */
#define OID_ARCNET_PERMANENT_ADDRESS            0x06010101
#define OID_ARCNET_CURRENT_ADDRESS              0x06010102

#define OID_ARCNET_RECONFIGURATIONS             0x06020201

/* TAPI objects */
#define OID_TAPI_ACCEPT                         0x07030101
#define OID_TAPI_ANSWER                         0x07030102
#define OID_TAPI_CLOSE                          0x07030103
#define OID_TAPI_CLOSE_CALL                     0x07030104
#define OID_TAPI_CONDITIONAL_MEDIA_DETECTION    0x07030105
#define OID_TAPI_CONFIG_DIALOG                  0x07030106
#define OID_TAPI_DEV_SPECIFIC                   0x07030107
#define OID_TAPI_DIAL                           0x07030108
#define OID_TAPI_DROP                           0x07030109
#define OID_TAPI_GET_ADDRESS_CAPS               0x0703010A
#define OID_TAPI_GET_ADDRESS_ID                 0x0703010B
#define OID_TAPI_GET_ADDRESS_STATUS             0x0703010C
#define OID_TAPI_GET_CALL_ADDRESS_ID            0x0703010D
#define OID_TAPI_GET_CALL_INFO                  0x0703010E
#define OID_TAPI_GET_CALL_STATUS                0x0703010F
#define OID_TAPI_GET_DEV_CAPS                   0x07030110
#define OID_TAPI_GET_DEV_CONFIG                 0x07030111
#define OID_TAPI_GET_EXTENSION_ID               0x07030112
#define OID_TAPI_GET_ID                         0x07030113
#define OID_TAPI_GET_LINE_DEV_STATUS            0x07030114
#define OID_TAPI_MAKE_CALL                      0x07030115
#define OID_TAPI_NEGOTIATE_EXT_VERSION          0x07030116
#define OID_TAPI_OPEN                           0x07030117
#define OID_TAPI_PROVIDER_INITIALIZE            0x07030118
#define OID_TAPI_PROVIDER_SHUTDOWN              0x07030119
#define OID_TAPI_SECURE_CALL                    0x0703011A
#define OID_TAPI_SELECT_EXT_VERSION             0x0703011B
#define OID_TAPI_SEND_USER_USER_INFO            0x0703011C
#define OID_TAPI_SET_APP_SPECIFIC               0x0703011D
#define OID_TAPI_SET_CALL_PARAMS                0x0703011E
#define OID_TAPI_SET_DEFAULT_MEDIA_DETECTION    0x0703011F
#define OID_TAPI_SET_DEV_CONFIG                 0x07030120
#define OID_TAPI_SET_MEDIA_MODE                 0x07030121
#define OID_TAPI_SET_STATUS_MESSAGES            0x07030122
#define OID_TAPI_GATHER_DIGITS                  0x07030123
#define OID_TAPI_MONITOR_DIGITS                 0x07030124

/* ATM Connection Oriented OIDs */
#define OID_ATM_SUPPORTED_VC_RATES              0x08010101
#define OID_ATM_SUPPORTED_SERVICE_CATEGORY      0x08010102
#define OID_ATM_SUPPORTED_AAL_TYPES             0x08010103
#define OID_ATM_HW_CURRENT_ADDRESS              0x08010104
#define OID_ATM_MAX_ACTIVE_VCS                  0x08010105
#define OID_ATM_MAX_ACTIVE_VCI_BITS             0x08010106
#define OID_ATM_MAX_ACTIVE_VPI_BITS             0x08010107
#define OID_ATM_MAX_AAL0_PACKET_SIZE            0x08010108
#define OID_ATM_MAX_AAL1_PACKET_SIZE            0x08010109
#define OID_ATM_MAX_AAL34_PACKET_SIZE           0x0801010A
#define OID_ATM_MAX_AAL5_PACKET_SIZE            0x0801010B

#define OID_ATM_SIGNALING_VPIVCI                0x08010201
#define OID_ATM_ASSIGNED_VPI                    0x08010202
#define OID_ATM_ACQUIRE_ACCESS_NET_RESOURCES    0x08010203
#define OID_ATM_RELEASE_ACCESS_NET_RESOURCES    0x08010204
#define OID_ATM_ILMI_VPIVCI                     0x08010205
#define OID_ATM_DIGITAL_BROADCAST_VPIVCI        0x08010206
#define OID_ATM_GET_NEAREST_FLOW                0x08010207
#define OID_ATM_ALIGNMENT_REQUIRED              0x08010208
#define OID_ATM_LECS_ADDRESS                    0x08010209
#define OID_ATM_SERVICE_ADDRESS                 0x0801020A

#define OID_ATM_CALL_PROCEEDING                 0x0801020B  /* UNI 4.0 */
#define OID_ATM_CALL_ALERTING                   0x0801020C  /* UNI 4.0 */
#define OID_ATM_PARTY_ALERTING                  0x0801020D  /* UNI 4.0 */
#define OID_ATM_CALL_NOTIFY                     0x0801020E  /* UNI 4.0 */

#define OID_ATM_MY_IP_NM_ADDRESS                0x0801020F


/*  ATM specific statistics OIDs. */
#define OID_ATM_RCV_CELLS_OK                    0x08020101
#define OID_ATM_XMIT_CELLS_OK                   0x08020102
#define OID_ATM_RCV_CELLS_DROPPED               0x08020103

#define OID_ATM_RCV_INVALID_VPI_VCI             0x08020201
#define OID_ATM_CELLS_HEC_ERROR                 0x08020202
#define OID_ATM_RCV_REASSEMBLY_ERROR            0x08020203


/* IEEE 802.11 OIDs */
#define OID_802_11_BSSID                        0x0D010101
#define OID_802_11_SSID                         0x0D010102
#define OID_802_11_NETWORK_TYPES_SUPPORTED      0x0D010203
#define OID_802_11_NETWORK_TYPE_IN_USE          0x0D010204
#define OID_802_11_TX_POWER_LEVEL               0x0D010205
#define OID_802_11_RSSI                         0x0D010206
#define OID_802_11_RSSI_TRIGGER                 0x0D010207
#define OID_802_11_INFRASTRUCTURE_MODE          0x0D010108
#define OID_802_11_FRAGMENTATION_THRESHOLD      0x0D010209
#define OID_802_11_RTS_THRESHOLD                0x0D01020A
#define OID_802_11_NUMBER_OF_ANTENNAS           0x0D01020B
#define OID_802_11_RX_ANTENNA_SELECTED          0x0D01020C
#define OID_802_11_TX_ANTENNA_SELECTED          0x0D01020D
#define OID_802_11_SUPPORTED_RATES              0x0D01020E
#define OID_802_11_DESIRED_RATES                0x0D010210
#define OID_802_11_CONFIGURATION                0x0D010211
#define OID_802_11_STATISTICS                   0x0D020212
#define OID_802_11_ADD_WEP                      0x0D010113
#define OID_802_11_REMOVE_WEP                   0x0D010114
#define OID_802_11_DISASSOCIATE                 0x0D010115
#define OID_802_11_POWER_MODE                   0x0D010216
#define OID_802_11_BSSID_LIST                   0x0D010217
#define OID_802_11_AUTHENTICATION_MODE          0x0D010118
#define OID_802_11_PRIVACY_FILTER               0x0D010119
#define OID_802_11_BSSID_LIST_SCAN              0x0D01011A
#define OID_802_11_WEP_STATUS                   0x0D01011B
/* Renamed to reflect better the extended set of encryption status */
#define OID_802_11_ENCRYPTION_STATUS            OID_802_11_WEP_STATUS
#define OID_802_11_RELOAD_DEFAULTS              0x0D01011C
/* Added to allow key mapping and default keys */
#define OID_802_11_ADD_KEY                      0x0D01011D
#define OID_802_11_REMOVE_KEY                   0x0D01011E
#define OID_802_11_ASSOCIATION_INFORMATION      0x0D01011F
#define OID_802_11_TEST                         0x0D010120
#define OID_802_11_MEDIA_STREAM_MODE            0x0D010121
#define OID_802_11_CAPABILITY                   0x0D010122
#define OID_802_11_PMKID                        0x0D010123
#define OID_802_11_NON_BCAST_SSID_LIST          0x0D010124
#define OID_802_11_RADIO_STATUS                 0x0D010125

#endif /* __RNDIS_OID_H_ */
