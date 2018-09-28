OLDLOC              := /usr/local/gcc-arm-none-eabi-4_9-2015q3
NEWLOC              := $(shell pwd)/tools/gcc-arm-none-eabi-4_9-2015q3
MKPOSIX             := sdk/nRF5_SDK_14.2.0_17b948a/components/toolchain/gcc/Makefile.posix
SDK_ZIPFILE         := nRF5_SDK_14.2.0_17b948a.zip
BLINKY_ARMGCC       := sdk/nRF5_SDK_14.2.0_17b948a/examples/peripheral/blinky/pca10040/blank/armgcc

NRFJPROG := ./tools/nrfjprog/nrfjprog

default: tools/tools.done sdk/.done

flash flash_softdevice:

tools/tools.done:
	$(MAKE) -C tools

# download sdk
$(SDK_ZIPFILE):
	wget http://developer.nordicsemi.com/nRF5_SDK/nRF5_SDK_v14.x.x/$@

# unpack and fixup sdk
sdk/.done: $(SDK_ZIPFILE)
	mkdir sdk
	cd sdk && unzip ../$+
	grep $(OLDLOC) $(MKPOSIX) && sed -i "s|$(OLDLOC)|$(NEWLOC)|g" $(MKPOSIX)
	touch $@

# build blinky
blinky: default
	$(MAKE) -C $(BLINKY_ARMGCC)

# deploy blinky
deploy_blinky: blinky
	$(NRFJPROG)  --family nRF52 -e
	$(NRFJPROG)  --family nRF52 --program $(BLINKY_ARMGCC)/_build/nrf52832_xxaa.hex
	$(NRFJPROG)  --family nRF52 -r

# run a check build
check: blinky_blank_pca10040

# clean all files except form the downloaded tarballs
cleanall:
	$(MAKE) -C tools $@
	rm -rf sdk/

# cleanall and delete the downloaded tarballs too
distclean: cleanall
	$(MAKE) -C tools $@
	rm -f $(SDK_ZIPFILE)

# install udev rules to allow access segger device without being root
udev_rule /etc/udev/rules.d/99-jlink.rules:
	sudo cp 99-jlink.rules /etc/udev/rules.d/
	sudo udevadm control --reload-rules

.PHONY: default check cleanall blinky deploy_blinky
