savedcmd_/home/admin1/linux/basicCharacterDriver/basicCharacterDriver.mod := printf '%s\n'   basicCharacterDriver.o | awk '!x[$$0]++ { print("/home/admin1/linux/basicCharacterDriver/"$$0) }' > /home/admin1/linux/basicCharacterDriver/basicCharacterDriver.mod