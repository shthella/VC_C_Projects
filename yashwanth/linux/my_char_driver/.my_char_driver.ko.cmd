cmd_/home/admin1/Documents/linux/my_char_driver/my_char_driver.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -z noexecstack   --build-id  -T ./scripts/module-common.lds -o /home/admin1/Documents/linux/my_char_driver/my_char_driver.ko /home/admin1/Documents/linux/my_char_driver/my_char_driver.o /home/admin1/Documents/linux/my_char_driver/my_char_driver.mod.o;  true
