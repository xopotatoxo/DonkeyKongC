## Setting up bare-metal Raspberry-pi model 4b
### openocd
Open a terminal at the same path
```
openocd -f rpi4.cfg
```

### serial output
Now open another terminal
```
ls /dev | grep ttyUSB
```
and it will display for example `ttyUSB1`. Use the **same number of usb** to setup serial output:
```
screen /dev/ttyUSB1 115200,cs8,ixoff,-istrip
```
press enter to see your pi's specs.

### NOTE
openocd setup will only work if your sd card has all the dependencies required, including `kernel8.img` that should be pre-included. If that is not the case overwrite the contents of the sd card with the backup zip file.

## Executing program
Now open another terminal on the same path. To compile an ELF (Executable Linkable File) called kernel8.elf:
```
make
```
The next step is to use **gdb** to load the ELF file and run it.
Open gdb, set the architecture and connect to `aarch64` (same as the one the pi uses) and connect to the remote target made earlier with openocd.

```
set architecture aarch64
target extended-remote :3333
```
Finally load the ELF file and use `c`/`continue` to run the program.
```
load kernel8.elf
c
```
To, halt press `CNTRL+C` and you may restart program by repeating above step.

NOTE: the output will be visible on the terminal where you set up serial output