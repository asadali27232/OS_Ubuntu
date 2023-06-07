# Create a simulator object
set ns [new Simulator]

# Create two nodes
set node1 [$ns node]
set node2 [$ns node]

# Create a TCP sending agent and attach it to node1
set tcp1 [new Agent/TCP]
$ns attach-agent $node1 $tcp1

# Create a TCP sink agent and attach it to node2
set sink [new Agent/TCPSink]
$ns attach-agent $node2 $sink

# Create a link between the nodes
$ns duplex-link $node1 $node2 10Mb 10ms DropTail

# Set up a TCP connection between the sender and the sink
$ns connect $tcp1 $sink

# Create a TCP application traffic source and attach it to the sender agent
set app1 [new Application/Traffic/FTP]
$app1 attach-agent $tcp1

# Set the start and stop time for the application
$app1 set start_time 0.1
$app1 set stop_time 1.0

# Set up a trace file to monitor the TCP connection
set tracefile [open tcptrace.tr w]
$tcp1 tracevar tracefile
$ns at 1.1 "$ns trace-annotate tcptrace.tr"

# Define a procedure to finish the simulation
proc finish {} {
    global ns tracefile
    $ns flush-trace
    close $tracefile
    $ns halt
}

# Schedule the end of the simulation
$ns at 2.0 "finish"

# Run the simulation
$ns run
