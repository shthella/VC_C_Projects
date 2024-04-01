savedcmd_/home/admin1/linux/freeDeviceNumbers.mod := printf '%s\n'   freeDeviceNumbers.o | awk '!x[$$0]++ { print("/home/admin1/linux/"$$0) }' > /home/admin1/linux/freeDeviceNumbers.mod
