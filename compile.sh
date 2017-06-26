as -o loader.o loader.s
gcc -Iinclude -Wall -fno-builtin -nostdinc -nostdlib -o kernel.o -c kernel.c
gcc -Iinclude -Wall -fno-builtin -nostdinc -nostdlib -o printf.o -c common/printf.c
gcc -Iinclude -Wall -fno-builtin -nostdinc -nostdlib -o screen.o -c common/screen.c
gcc -Iinclude -Wall -fno-builtin -nostdinc -nostdlib -o standalone_snake_game.o -c common/standalone_snake_game.c
gcc -Iinclude -Wall -fno-builtin -nostdinc -nostdlib -o keyboard_communicator.o -c common/keyboard_communicator.c
ld -T linker.ld -o kernel.bin kernel.o screen.o printf.o loader.o standalone_snake_game.o

cp /usr/lib/grub/x86_64-pc/stage1 ./grub/
cp /usr/lib/grub/x86_64-pc/stage2 ./grub/
cp /usr/lib/grub/x86_64-pc/fat_stage1_5 ./grub/