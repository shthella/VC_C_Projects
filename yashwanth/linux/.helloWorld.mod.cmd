savedcmd_/home/admin1/linux/helloWorld.mod := printf '%s\n'   helloWorld.o | awk '!x[$$0]++ { print("/home/admin1/linux/"$$0) }' > /home/admin1/linux/helloWorld.mod
