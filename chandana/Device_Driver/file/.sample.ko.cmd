savedcmd_/home/admin1/Downloads/devdri/file/sample.ko := ld -r -m elf_x86_64 -z noexecstack --build-id=sha1  -T scripts/module.lds -o /home/admin1/Downloads/devdri/file/sample.ko /home/admin1/Downloads/devdri/file/sample.o /home/admin1/Downloads/devdri/file/sample.mod.o;  make -f ./arch/x86/Makefile.postlink /home/admin1/Downloads/devdri/file/sample.ko