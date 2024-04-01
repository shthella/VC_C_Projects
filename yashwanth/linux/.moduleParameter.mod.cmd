savedcmd_/home/admin1/linux/moduleParameter.mod := printf '%s\n'   moduleParameter.o | awk '!x[$$0]++ { print("/home/admin1/linux/"$$0) }' > /home/admin1/linux/moduleParameter.mod
