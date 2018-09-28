TOOLCHAIN_TARBALL   := gcc-arm-none-eabi-4_9-2015q3-20150921-linux.tar.bz2
NRF5X_TOOLS_TARBALL := nRF5x-Command-Line-Tools_8_4_0_Linux-x86_64.tar
WORKSHOP_PROJ       := nrf52-hardware-startup-hands-on
JLINK_DEBUGGER      := JLinkDebugger_Linux_V214h_x86_64

tools.done: gcc-arm-none-eabi-4_9-2015q3/.done \
            nrfjprog/.done \
            /opt/SEGGER/JLink/libjlinkarm.so
	touch $@

# download toolchain
gcc-arm-none-eabi-4_9-2015q3/.done: $(TOOLCHAIN_TARBALL)
	tar xjf $+
	touch $@

# unpack toolchain
$(TOOLCHAIN_TARBALL):
	wget https://launchpad.net/gcc-arm-embedded/4.9/4.9-2015-q3-update/+download/$@

# download programming tools
$(NRF5X_TOOLS_TARBALL):
	wget -O $@ https://www.nordicsemi.com/eng/nordic/download_resource/51386/29/52613202/94917

# unpack programming tools
nrfjprog/.done: $(NRF5X_TOOLS_TARBALL)
	tar xf $+
	touch $@

# download segger tools
$(JLINK_DEBUGGER).tgz:
	wget https://download.segger.com/J-Link/J-LinkDebugger/$@

# unpack segger tools
$(JLINK_DEBUGGER)/.done: $(JLINK_DEBUGGER).tgz
	tar zxf $+
	touch $@

# install segger library in the place nrfjprog excepts to find it (needs root access)
/opt/SEGGER/JLink/libjlinkarm.so: JLinkDebugger_Linux_V214h_x86_64/.done
	sudo mkdir -p /opt/SEGGER/JLink
	sudo cp JLinkDebugger_Linux_V214h_x86_64/Lib/libjlinkarm.so /opt/SEGGER/JLink/

# clean all files except form the downloaded tarballs
cleanall:
	rm -rf nrfjprog/ mergehex/ gcc-arm-none-eabi-4_9-2015q3/ \
	       $(JLINK_DEBUGGER)/ tools.done

# cleanall and delete the downloaded tarballs too
distclean: cleanall
	rm -f $(TOOLCHAIN_TARBALL) $(NRF5X_TOOLS_TARBALL) $(JLINK_DEBUGGER).tgz
