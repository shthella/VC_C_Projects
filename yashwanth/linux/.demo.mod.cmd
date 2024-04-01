savedcmd_/home/admin1/linux/demo.mod := printf '%s\n'   demo.o | awk '!x[$$0]++ { print("/home/admin1/linux/"$$0) }' > /home/admin1/linux/demo.mod
