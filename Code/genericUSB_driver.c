/*
	genericUSB: Generic USB Driver for Mass Storage Devices
		Janki Trivedi 121018  
		Shoghi Bagul 121051
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
 
static struct usb_device *device;

static struct usb_device_id genericUSB_table[] =
{
    { USB_DEVICE(0x058F, 0x6387) },
    {} /* Terminating entry */
};
MODULE_DEVICE_TABLE (usb, genericUSB_table);
 
static struct usb_driver genericUSB_driver =
{
    .name = "genericUSB_driver",
    .probe = genericUSB_probe,
    .disconnect = genericUSB_disconnect,
    .id_table = genericUSB_table,
};
 
static int __init genericUSB_init(void)
{
    return usb_register(&genericUSB_driver);
}
 
static void __exit genericUSB_exit(void)
{
    usb_deregister(&genericUSB_driver);
}
 
module_init(genericUSB_init);
module_exit(genericUSB_exit);

static int genericUSB_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
  printk("\n\nProbe called");
 struct usb_host_interface *host_inter;
    struct usb_endpoint_descriptor *end_desc;
    int i;
 
    host_inter = interface->cur_altsetting;
printk(KERN_INFO "Pen i/f %d now probed: (%04X:%04X)\n",
    
	host_inter->desc.bInterfaceNumber, id->idVendor, id->idProduct);
printk(KERN_INFO "ID->bNumEndpoints: %02X\n",
            
	host_inter->desc.bNumEndpoints);
printk(KERN_INFO "ID->bInterfaceClass: %02X\n",
            host_inter->desc.bInterfaceClass);
 
    for (i = 0; i < host_inter->desc.bNumEndpoints; i++)
    {
	  printk("\n\nProbe for loop");       
	 	end_desc = &host_inter->end_desc[i].desc;
 
        printk(KERN_INFO "ED[%d]->bEndpointAddress: 0x%02X\n",
                i, end_desc->bEndpointAddress);
        printk(KERN_INFO "ED[%d]->bmAttributes: 0x%02X\n",
                i, end_desc->bmAttributes);
        printk(KERN_INFO "ED[%d]->wMaxPacketSize: 0x%04X (%d)\n",
                i, end_desc->wMaxPacketSize, end_desc->wMaxPacketSize);
    }
    device = interface_to_usbdev(interface);
    return 0;
}
 
static void genericUSB_disconnect(struct usb_interface *interface)
{
	printk("\n\n................pen_disconnect called");   
	printk(KERN_INFO "Pen i/f %d now disconnected\n",
            interface->cur_altsetting->desc.bInterfaceNumber);
}
 
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Janki Trivedi | Shoghi Bagul");
MODULE_DESCRIPTION("Generic USB Driver");
