BlackwolfOS
===========

My attempt at writing an operating system(expect it to fail)

Buiding
=======

Open the terminal and cd to where you put this repository.
Than execute # sh build, that will build the files in src and add the output to
the floppy.img file.

Running
=======

To run this OS you either use qemu or physical hardware. With qemu it is easy, 
just run ./run_qemu.sh and you'll be fine.
For physical hardware you have to do a little more. You will need a floppy, and
do 'dd if=floppy.img of=/dev/fd0 bs=512' assuming that your floppy is at /dev/fd0.
