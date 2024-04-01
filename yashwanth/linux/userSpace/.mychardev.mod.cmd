savedcmd_/home/admin1/linux/userSpace/mychardev.mod := printf '%s\n'   mychardev.o | awk '!x[$$0]++ { print("/home/admin1/linux/userSpace/"$$0) }' > /home/admin1/linux/userSpace/mychardev.mod
