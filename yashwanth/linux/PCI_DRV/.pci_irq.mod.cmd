savedcmd_/home/admin1/Documents/linux/pci_drv/pci_irq.mod := printf '%s\n'   pci_irq.o | awk '!x[$$0]++ { print("/home/admin1/Documents/linux/pci_drv/"$$0) }' > /home/admin1/Documents/linux/pci_drv/pci_irq.mod