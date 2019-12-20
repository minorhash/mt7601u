My nonane black-red 148f:7601 mt7601u mini stick is working now!
Tested on Ubuntu 14.04 (kernel 4.4) and Ubuntu 17.10 (kernel 4.13).
Thanks to aleksander and Nidroide!
Just want to clarify instruction:

    Download corresponding kernel source from kernel.org. For example: if you have 4.4.0-104-generic download version 4.4.
    From archive unpack just folder drivers/net/wireless/mediatek/mt7601u
    Edit phy.c. Find function mt7601u_init_cal and comment out call mt7601u_mcu_calibrate(dev, MCU_CAL_RXIQ, 0); like so:

//  ret = mt7601u_mcu_calibrate(dev, MCU_CAL_RXIQ, 0);
//  if (ret)
//      return ret;
//  ret = mt7601u_mcu_calibrate(dev, MCU_CAL_DPD, dev->dpd_temp);
//  if (ret)
//      return ret;

Find function mt7601u_phy_recalibrate_after_assoc and comment out call mt7601u_mcu_calibrate(dev, MCU_CAL_DPD, dev->curr_temp); like so:

void mt7601u_phy_recalibrate_after_assoc(struct mt7601u_dev *dev)
{
//  mt7601u_mcu_calibrate(dev, MCU_CAL_DPD, dev->curr_temp);

    mt7601u_rxdc_cal(dev);
}

    Build module: make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
    Remove device
    sudo rmmod mt7601u
    sudo insmod ./mt7601u.ko
    Insert device
    Check there are no errors in dmesg and interface appeared in ip link, check connection stability.
    To make change persistent till next kernel upgrade: backup original module and replace with compiled. To find out where is original module run modinfo mt7601u (view string filename: /lib/modules/_KERNEL_VERSION_/kernel/drivers/net/wireless/mediatek/mt7601u/mt7601u.ko).
