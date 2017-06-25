make all

if [ $? -eq 0 ]
then
	sudo make image

	if [ $? -eq 0 ]
	then 
		qemu-system-i386 -vga cirrus -hda hdd.img
	fi
fi
