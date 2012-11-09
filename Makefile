include src/Makefile.am

all:
	cd src && make && cd ..

	mkdir isofiles
	mkdir isofiles/boot/
	mkdir isofiles/boot/grub/
	cp grub/stage2_eltorito isofiles/boot/grub
	cp src/kernel/kernel isofiles/
	cp src/menu.lst isofiles/boot/grub
	cp logo/grub.xpm.gz isofiles/
	
	cp src/app/test2/test2 src/initr/test2
	cp src/app/test/test src/initr/test
	
	src/tools/initramfs_gen/initramfs_gen src/tools/initramfs_gen/initram.img src/initr/*

	cp src/tools/initramfs_gen/initram.img isofiles/

	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o image.iso isofiles

	rm -r isofiles


clean:
	cd src && make clean  && cd ..
	rm -r isofiles
	rm image.iso


install:
	sudo cp src/kernel/kernel /boot/spiderpig
	sudo cp src/tools/initramfs_gen/initram.img /boot/spidramfs


test:
	qemu -cdrom image.iso -usb -m 128 -serial stdio -net nic,model=ne2k_pci -net user

test_bochs:
	bochs -f bochs.rc

test_qemu:
	qemu -cdrom image.iso -usb -m 128 -serial stdio -net nic,model=ne2k_pci,mac_addr=01:02:03:04:05:06:07:08 -net user 

src:
	cd src && make && cd ..
