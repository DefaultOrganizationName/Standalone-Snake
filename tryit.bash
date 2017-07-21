make all

if [ $? -eq 0 ]
then
	make image
	if [ $? -eq 0 ]
	then
		qemu-system-i386 -cdrom os.iso
	fi
	make clean
fi