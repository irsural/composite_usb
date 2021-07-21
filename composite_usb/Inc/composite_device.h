/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_MSC_CDC_CORE_H
#define __USB_MSC_CDC_CORE_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_ioreq.h"
#include "usbd_desc.h"
#include "usbd_ctlreq.h"

#include "usbd_hid.h"
#include "usbd_cdc.h"

#include "usbd_cdc_interface.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
* @{
*/

/** @defgroup USBD_MSC_CDC_Exported_Defines
* @{
*/
//#define TEMPLATE_EPIN_ADDR                 0x81
//#define TEMPLATE_EPIN_SIZE                 0x10

#define USB_CONFIG_DESC_SIZE 0x12

#define HID_INTERFACE_IDX 0x00
#define HID_INTERFACE_CLASS 0x03
#define HID_INTERFACE_SUBCLASS 0x01
#define HID_INTERFACE_PROTOCOL 0x02
#define HID_IDX_INTERFACE_STR 0x00

#define HID_EP_IDX 0x01

#define CDC_INTERFACE_IDX 0x01
#define CDC_FUNCTION_CLASS 0x02
#define CDC_FUNCTION_SUBCLASS 0x02
#define CDC_FUNCTION_PROTOCOL 0x01

#define CDC_INTERFACE_CLASS CDC_FUNCTION_CLASS
#define CDC_INTERFACE_SUBCLASS CDC_FUNCTION_SUBCLASS
#define CDC_INTERFACE_PROTOCOL CDC_FUNCTION_PROTOCOL

#define CDC_CMD_EP_IDX 0x02
#define CDC_EP_IDX 0x03

#define IN_EP_DIR 0x80 // Adds a direction bit

#define HID_OUT_EP HID_EP_IDX                 /* EP1 for BULK OUT */
#define HID_IN_EP HID_EP_IDX | IN_EP_DIR      /* EP1 for BULK IN */
#define CDC_CMD_EP CDC_CMD_EP_IDX | IN_EP_DIR /* EP2 for CDC commands */
#define CDC_OUT_EP CDC_EP_IDX                 /* EP3 for data OUT */
#define CDC_IN_EP CDC_EP_IDX | IN_EP_DIR      /* EP3 for data IN */

#define CDC_DATA_PACKET_SIZE CDC_DATA_FS_MAX_PACKET_SIZE
#define USB_MAX_PACKET_SIZE USB_FS_MAX_PACKET_SIZE

/**
* @}
*/

/** @defgroup USBD_CORE_Exported_TypesDefinitions
* @{
*/

/**
* @}
*/

/** @defgroup USBD_CORE_Exported_Macros
* @{
*/

/**
* @}
*/

/** @defgroup USBD_CORE_Exported_Variables
* @{
*/

extern USBD_ClassTypeDef USBD_HID_CDC_ClassDriver;
/**
* @}
*/

/** @defgroup USB_CORE_Exported_Functions
* @{
*/
/**
* @}
*/

#ifdef __cplusplus
}
#endif

#endif /* __USB_HID_CDC_CORE_H */
       /**
  * @}
  */

/**
  * @}
  */