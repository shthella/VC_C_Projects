savedcmd_/home/admin1/linux/user_space/mychardev.ko := x86_64-linux-gnu-ld -r -m elf_x86_64 -z noexecstack --build-id=sha1  -T scripts/module.lds -o /home/admin1/linux/user_space/mychardev.ko /home/admin1/linux/user_space/mychardev.o /home/admin1/linux/user_space/mychardev.mod.o;  make -f ./arch/x86/Makefile.postlink /home/admin1/linux/user_space/mychardev.ko