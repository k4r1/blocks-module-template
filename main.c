#include "vendor.h"

const vendor_module_info_t blocks_module_info = {
    .label    = u"Example Module",
    .vendorID = u"Blocks Wearables Ltd.",
    .modelID  = {0x12, 0x34, 0x56, 0x78}
};

/**
 * Vendor-defined function for performing hardware initialization
 * e.g. GPIO setup.
 */
void blocks_initializeModule(void)
{
    // Use ModuleError notification to indicate critical error here
    //blocks_notify(NOTIFY_MODULE_ERROR);
}

void blocks_main(void)
{
    // Enter your main run loop implementation here
    while (1) {
        module_vendor_idle();
    }
}

const vendor_array_handler_t blocks_module_functions = { .count = 0,
{
    // Add standard function handlers here and update the count value
    //{ STDFUNC_LED_ON, led_on },
}};
