#include "composite_device.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_HID_CDC
  * @brief usbd core module
  * @{
  */

/** @defgroup USBD_HID_CDC_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_HID_CDC_Private_Defines
  * @{
  */

/**
  * @}
  */


/** @defgroup USBD_HID_CDC_Private_Macros
  * @{
  */

/**
  * @}
  */




/** @defgroup USBD_HID_CDC_Private_FunctionPrototypes
  * @{
  */


static uint8_t  USBD_HID_CDC_Init (USBD_HandleTypeDef *pdev, 
								   uint8_t cfgidx);

static uint8_t  USBD_HID_CDC_DeInit (USBD_HandleTypeDef *pdev, 
									 uint8_t cfgidx);

static uint8_t  USBD_HID_CDC_Setup (USBD_HandleTypeDef *pdev, 
									USBD_SetupReqTypedef *req);

static uint8_t  *USBD_HID_CDC_GetCfgDesc (uint16_t *length);

static uint8_t  *USBD_HID_CDC_GetDeviceQualifierDesc (uint16_t *length);

static uint8_t  USBD_HID_CDC_DataIn (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t  USBD_HID_CDC_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t  USBD_HID_CDC_EP0_RxReady (USBD_HandleTypeDef *pdev);

/**
  * @}
  */

/** @defgroup USBD_HID_CDC_Private_Variables
  * @{
  */

USBD_ClassTypeDef USBD_HID_CDC_ClassDriver = 
{
	USBD_HID_CDC_Init,
	USBD_HID_CDC_DeInit,
	USBD_HID_CDC_Setup,
	NULL, //USBD_HID_CDC_EP0_TxReady,
	USBD_HID_CDC_EP0_RxReady,
	USBD_HID_CDC_DataIn,
	USBD_HID_CDC_DataOut,
	NULL, //USBD_HID_CDC_SOF,
	NULL, //USBD_HID_CDC_IsoINIncomplete,
	NULL, //USBD_HID_CDC_IsoOutIncomplete,
	USBD_HID_CDC_GetCfgDesc,
	USBD_HID_CDC_GetCfgDesc,
	USBD_HID_CDC_GetCfgDesc,
	USBD_HID_CDC_GetDeviceQualifierDesc,
};

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4
#endif
/* USB HID+CDC device Configuration Descriptor */
__ALIGN_BEGIN uint8_t USBD_HID_CDC_CfgDesc[] __ALIGN_END =
{
	USB_CONFIG_DESC_SIZE,    /* bLength: Configuation Descriptor size */
	USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
	0x00, /* wTotalLength: Bytes returned */
	0x00,
	USB_NUM_INTERFACES,         /*bNumInterfaces: 2 interface*/
	0x01,         /*bConfigurationValue: Configuration value*/
	0x00,         /*iConfiguration: Index of string descriptor describing the configuration*/
	0xC0,         /*bmAttributes: bus powered and Supports Remote Wakeup */
	0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/
	/* 09 bytes */

	 /************** Descriptor of Joystick Mouse interface ****************/
	0x09,                                               /* bLength: Interface Descriptor size */
	USB_DESC_TYPE_INTERFACE,                            /* bDescriptorType: Interface descriptor type */
	0x00,                                               /* bInterfaceNumber: Number of Interface */
	0x00,                                               /* bAlternateSetting: Alternate setting */
	0x01,                                               /* bNumEndpoints */
	0x03,                                               /* bInterfaceClass: HID */
	0x01,                                               /* bInterfaceSubClass : 1=BOOT, 0=no boot */
	0x02,                                               /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
	0x00,                                               /* iInterface: Index of string descriptor */
	/* 09 bytes */

	/******************** Descriptor of Joystick Mouse HID ********************/
	0x09,                                               /* bLength: HID Descriptor size */
	HID_DESCRIPTOR_TYPE,                                /* bDescriptorType: HID */
	0x11,                                               /* bcdHID: HID Class Spec release number */
	0x01,
	0x00,                                               /* bCountryCode: Hardware target country */
	0x01,                                               /* bNumDescriptors: Number of HID class descriptors to follow */
	0x22,                                               /* bDescriptorType */
	LOBYTE(IRS_HID_MOUSE_REPORT_DESC_SIZE),                         /* wItemLength: Total length of Report descriptor */
	HIBYTE(IRS_HID_MOUSE_REPORT_DESC_SIZE),
	/* 09 bytes */

	/******************** Descriptor of Mouse endpoint ********************/
	0x07,                                               /* bLength: Endpoint Descriptor size */
	USB_DESC_TYPE_ENDPOINT,                             /* bDescriptorType:*/
	HID_EPIN_ADDR,                                      /* bEndpointAddress: Endpoint Address (IN) */
	0x03,                                               /* bmAttributes: Interrupt endpoint */
	HID_EPIN_SIZE,                                      /* wMaxPacketSize: 4 Byte max */
	0x00,
	HID_FS_BINTERVAL,                                   /* bInterval: Polling Interval */
	/* 07 bytes */

	/******** IAD should be positioned just before the CDC interfaces ******
			 IAD to associate the two CDC interfaces */
	0x08, /* bLength */
	0x0B, /* bDescriptorType */
	CDC_INTERFACE_IDX, /* bFirstInterface */
	0x02, /* bInterfaceCount */
	CDC_FUNCTION_CLASS, /* bFunctionClass */
	CDC_FUNCTION_SUBCLASS, /* bFunctionSubClass */
	CDC_FUNCTION_PROTOCOL, /* bFunctionProtocol */
	0x00, /* iFunction (Index of string descriptor describing this function) */
	/* 08 bytes */

	/********************  CDC interfaces ********************/

	/*Interface Descriptor */
	0x09,   /* bLength: Interface Descriptor size */
	USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: Interface */
	/* Interface descriptor type */
	CDC_INTERFACE_IDX,   /* bInterfaceNumber: Number of Interface */
	0x00,   /* bAlternateSetting: Alternate setting */
	0x01,   /* bNumEndpoints: One endpoints used */
	CDC_INTERFACE_CLASS,   /* bInterfaceClass: Communication Interface Class */
	CDC_INTERFACE_SUBCLASS,   /* bInterfaceSubClass: Abstract Control Model */
	CDC_INTERFACE_PROTOCOL,   /* bInterfaceProtocol: Common AT commands */
	0x01,   /* iInterface: */
	/* 09 bytes */

	/*Header Functional Descriptor*/
	0x05,   /* bLength: Endpoint Descriptor size */
	0x24,   /* bDescriptorType: CS_INTERFACE */
	0x00,   /* bDescriptorSubtype: Header Func Desc */
	0x10,   /* bcdCDC: spec release number */
	0x01,
	/* 05 bytes */

	/*Call Management Functional Descriptor*/
	0x05,   /* bFunctionLength */
	0x24,   /* bDescriptorType: CS_INTERFACE */
	0x01,   /* bDescriptorSubtype: Call Management Func Desc */
	0x00,   /* bmCapabilities: D0+D1 */
	CDC_INTERFACE_IDX + 1,   /* bDataInterface: 2 */
	/* 05 bytes */

	/*ACM Functional Descriptor*/
	0x04,   /* bFunctionLength */
	0x24,   /* bDescriptorType: CS_INTERFACE */
	0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
	0x02,   /* bmCapabilities */
	/* 04 bytes */

	/*Union Functional Descriptor*/
	0x05,   /* bFunctionLength */
	0x24,   /* bDescriptorType: CS_INTERFACE */
	0x06,   /* bDescriptorSubtype: Union func desc */
	CDC_INTERFACE_IDX,   /* bMasterInterface: Communication class interface */
	CDC_INTERFACE_IDX + 1,   /* bSlaveInterface0: Data Class Interface */
	/* 05 bytes */

	/*Endpoint 2 Descriptor*/
	0x07,                          /* bLength: Endpoint Descriptor size */
	USB_DESC_TYPE_ENDPOINT,        /* bDescriptorType: Endpoint */
	CDC_CMD_EP,                    /* bEndpointAddress */
	0x03,                          /* bmAttributes: Interrupt */
	LOBYTE(CDC_CMD_PACKET_SIZE),   /* wMaxPacketSize: */
	HIBYTE(CDC_CMD_PACKET_SIZE),
	0x10,                          /* bInterval: */
	/* 07 bytes */

	/*Data class interface descriptor*/
	0x09,   /* bLength: Endpoint Descriptor size */
	USB_DESC_TYPE_INTERFACE,       /* bDescriptorType: */
	CDC_INTERFACE_IDX + 1,         /* bInterfaceNumber: Number of Interface */
	0x00,                          /* bAlternateSetting: Alternate setting */
	0x02,                          /* bNumEndpoints: Two endpoints used */
	0x0A,                          /* bInterfaceClass: CDC */
	0x00,                          /* bInterfaceSubClass: */
	0x00,                          /* bInterfaceProtocol: */
	0x00,                          /* iInterface: */
	/* 09 bytes */

	/*Endpoint OUT Descriptor*/
	0x07,   /* bLength: Endpoint Descriptor size */
	USB_DESC_TYPE_ENDPOINT,        /* bDescriptorType: Endpoint */
	0x05,                    /* bEndpointAddress */
	0x02,                          /* bmAttributes: Bulk */
	LOBYTE(CDC_DATA_PACKET_SIZE),  /* wMaxPacketSize: */
	HIBYTE(CDC_DATA_PACKET_SIZE),
	0x00,                          /* bInterval: ignore for Bulk transfer */
	/* 07 bytes */

	/*Endpoint IN Descriptor*/
	0x07,   /* bLength: Endpoint Descriptor size */
	USB_DESC_TYPE_ENDPOINT,        /* bDescriptorType: Endpoint */
	IRS_CDC_IN_EP,                     /* bEndpointAddress */
	0x02,                          /* bmAttributes: Bulk */
	LOBYTE(CDC_DATA_PACKET_SIZE),  /* wMaxPacketSize: */
	HIBYTE(CDC_DATA_PACKET_SIZE),
	0x00,                          /* bInterval */
	/* 07 bytes */
};

extern const uint16_t USB_HID_CDC_CONFIG_DESC_SIZ = 
  sizeof(USBD_HID_CDC_CfgDesc);
//#define USB_HID_CDC_CONFIG_DESC_SIZ sizeof(USBD_HID_CDC_CfgDesc)

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4
#endif
/* USB Standard Device Descriptor */
uint8_t USBD_HID_CDC_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] =
{
	USB_LEN_DEV_QUALIFIER_DESC,
	USB_DESC_TYPE_DEVICE_QUALIFIER,
	0x00,
	0x02,
	0x00,
	0x00,
	0x00,
	USB_MAX_PACKET_SIZE,
	0x01,
	0x00,
};

/**
  * @}
  */

/** @defgroup USBD_HID_CDC_Private_Functions
  * @{
  */

/**
  * @brief  USBD_HID_CDC_Init
  *         Initialize the HID+CDC interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_CDC_Init (USBD_HandleTypeDef *pdev, 
								   uint8_t cfgidx)
{
	/* HID initialization */
	uint8_t ret = USBD_HID_Init(pdev, cfgidx);
	if(ret != 0)
		return ret;

	/* CDC initialization */
	ret = USBD_CDC_Init(pdev, cfgidx);
	if(ret != 0)
		return ret;

	return USBD_OK;
}

/**
  * @brief  USBD_HID_CDC_Init
  *         DeInitialize the HID+CDC layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_CDC_DeInit (USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
	/* HID De-initialization */
	USBD_HID_DeInit(pdev, cfgidx);

	/* CDC De-initialization */
	USBD_CDC_DeInit(pdev, cfgidx);

	return USBD_OK;
}

/**
  * @brief  USBD_HID_CDC_Setup
  *         Handle the HID+CDC specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t  USBD_HID_CDC_Setup (USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
	// Route requests to HID interface or its endpoints to HID class implementaion
	if(((req->bmRequest & USB_REQ_RECIPIENT_MASK) == USB_REQ_RECIPIENT_INTERFACE && req->wIndex == HID_INTERFACE_IDX) ||
		((req->bmRequest & USB_REQ_RECIPIENT_MASK) == USB_REQ_RECIPIENT_ENDPOINT && ((req->wIndex & 0x7F) == HID_EP_IDX)))
	{
		return USBD_HID_Setup(pdev, req);
	}

	return USBD_CDC_Setup(pdev, req);
}

/**
  * @brief  USBD_HID_CDC_DataIn
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_HID_CDC_DataIn (USBD_HandleTypeDef *pdev,
									 uint8_t epnum)
{
	if(epnum == HID_EP_IDX)
		return USBD_HID_DataIn(pdev, epnum);

	return USBD_CDC_DataIn(pdev, epnum);
}

/**
  * @brief  USBD_HID_CDC_DataOut
  *         handle data OUT Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_HID_CDC_DataOut (USBD_HandleTypeDef *pdev,
									  uint8_t epnum)
{
    if(epnum == HID_EP_IDX) { return USBD_OK; }
//		return USBD_HID_DataOut(pdev, epnum);

	return USBD_CDC_DataOut(pdev, epnum);
}


/**
  * @brief  USBD_HID_CDC_GetCfgDesc
  *         return configuration descriptor
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_HID_CDC_GetCfgDesc (uint16_t *length)
{
	*length = sizeof (USBD_HID_CDC_CfgDesc);
	return USBD_HID_CDC_CfgDesc;
}

/**
* @brief  DeviceQualifierDescriptor 
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t *USBD_HID_CDC_DeviceQualifierDescriptor (uint16_t *length)
{
	*length = sizeof (USBD_HID_CDC_DeviceQualifierDesc);
	return USBD_HID_CDC_DeviceQualifierDesc;
}


/**
  * @brief  USBD_HID_CDC_EP0_RxReady
  *         handle EP0 Rx Ready event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t  USBD_HID_CDC_EP0_RxReady (USBD_HandleTypeDef *pdev)
{
	return USBD_CDC_EP0_RxReady(pdev);
}

/**
* @brief  DeviceQualifierDescriptor 
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_HID_CDC_GetDeviceQualifierDesc (uint16_t *length)
{
	*length = sizeof (USBD_HID_CDC_DeviceQualifierDesc);
	return USBD_HID_CDC_DeviceQualifierDesc;
}

/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */
