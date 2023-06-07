# Create a simulator object
set ns [new Simulator]

# Open the nam trace file
set namfile [open out.nam w]
$ns namtrace-all $namfile

# Define different colors for data flows (for NAM)
$ns color 1 Blue
$ns color 2 Red

# Open the NAM animation file
set tracefile [open out.tr w]
$ns trace-all $tracefile

# Create four nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

# Create links between the nodes
$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 1.7Mb 20ms DropTail

# Set aggent TCP to n0 and attach it to node n3
set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n3 $sink
$ns connect $tcp $sink
$tcp set fid_ 1

# Set agent FTP to n1 and attach it to node n3
set ftp [new Application/FTP]
$ftp attach-agent $tcp


# Define a 'finish' procedure
proc finish {} {
    global ns tracefile namfile
    $ns flush-trace
    close $tracefile
    close $namfile
    exec nam out.nam &
    exit 0
}