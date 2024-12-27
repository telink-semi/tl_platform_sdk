@page Driver_structure

The Driver SDK directory structure is as follows:

![Driver SDK directory](pic/driversdkdirectory.png "Driver SDK directory")

# boot

Under this folder are the boot files.

![boot folder](pic/bootfolder.png "boot folder")

# common

Under this folder are some common files that are not related to the driver. Two of the folders are described in particular:

bt_debug: is the interface function for Bluetooth related modules to set debug GPIO.

compatibility_pack: is to be compatible with the previous driver interface of each SDK, the relevant files added will not be used in the driver.

![common folder](pic/commonfolder.png "common folder")

# drivers

This folder is for the driver of relevant module.

# link

This folder is used to store link files and is selected according to different usage needs.

![link folder](pic/linkfolder.png "link folder")

# vendor

This folder is for the demo of all modules.
