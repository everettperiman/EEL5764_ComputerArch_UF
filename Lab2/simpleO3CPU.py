import m5
from m5.objects import *

"""
SETUP NOTES
Our configuration script is going to model a very simple system. 
We’ll have just one simple CPU core. 
This CPU core will be connected to a system-wide memory bus. 
And we’ll have a single DDR3 memory channel, also connected to the memory bus.
"""

"""
Useful Terminal Commands for this lab

1. This is used to recompile the modified hello.c file
    gcc -O0 -std=c99 -static -o a.out hello.c
2. This is how to run the simple.py program
    ../../../build/X86/gem5.opt simple.py
"""

# Create the parent for all of the children objects of the system
# This is creating the system as a whole and defines several characteristics
system = System()

# Setup the clock domain using the default value
# Setup the clock freq as 1GHz
# Setup the voltage domain as the default value
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = '1GHz'
system.clk_domain.voltage_domain = VoltageDomain()

# Setup the system using the timing memory mode, this is the most commonly used memory mode except
# for when fast-forwarding or restoring a simulation
# Define the memory range to be 512MB
system.mem_mode = 'timing'
system.mem_ranges = [AddrRange('512MB')]

# TimingSimpleCPU is the simplest cpu in gem5, this model executes each instruction in a single clock cycle
#system.cpu = TimingSimpleCPU()
system.cpu = O3CPU()

# Create a system wide memory bus
system.membus = SystemXBar()

# If there are no caches then the I-cache and the D-cache are connected directly to the membus
# This example has no caches
system.cpu.icache_port = system.membus.cpu_side_ports
system.cpu.dcache_port = system.membus.cpu_side_ports

# Create an IO controller on the CPU and connect it to the memory bus
# Need to connect a special port to the membus, this port allows the sys to read/write to memory
# Connecting PIO and interrupt ports to the membus is an X86 requirement
system.cpu.createInterruptController()
system.cpu.interrupts[0].pio = system.membus.mem_side_ports
system.cpu.interrupts[0].int_requestor = system.membus.cpu_side_ports
system.cpu.interrupts[0].int_responder = system.membus.mem_side_ports

system.system_port = system.membus.cpu_side_ports

# Need to create a memory controller and connect it to the membus
# We are using a simple DDR3 controller
system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR3_1600_8x8()
system.mem_ctrl.dram.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.mem_side_ports

# Setting up and running an example program on the "System"
# First we have to create the command we want to run
binary = 'a.out'

# for gem5 V21 and beyond
system.workload = SEWorkload.init_compatible(binary)

process = Process()
process.cmd = [binary]
system.cpu.workload = process
system.cpu.createThreads()

# Instatiate the simulation and begin execution
root = Root(full_system = False, system = system)
m5.instantiate()

# Start the simulation
print("Beginning simulation!")
exit_event = m5.simulate()

# Inspect the state of the system after simulation
print('Exiting @ tick {} because {}'
      .format(m5.curTick(), exit_event.getCause()))
