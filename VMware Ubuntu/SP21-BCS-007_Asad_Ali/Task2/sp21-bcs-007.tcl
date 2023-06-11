# This script is created by NSG2 beta1
# <http://wushoupong.googlepages.com/nsg>

#===================================
#     Simulation parameters setup
#===================================
set val(stop)   10.0                         ;# time of simulation end

#===================================
#        Initialization        
#===================================
#Create a ns simulator
set ns [new Simulator]

#Open the NS trace file
set tracefile [open sp21-bcs-007.tr w]
$ns trace-all $tracefile

#Open the NAM trace file
set namfile [open sp21-bcs-007.nam w]
$ns namtrace-all $namfile

#===================================
#        Nodes Definition        
#===================================
#Create 7 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]

#===================================
#        Links Definition        
#===================================
#Createlinks between nodes
$ns duplex-link $n0 $n3 500.0Mb 11ms DropTail
$ns queue-limit $n0 $n3 49
$ns duplex-link $n1 $n3 500.0Mb 11ms DropTail
$ns queue-limit $n1 $n3 49
$ns duplex-link $n2 $n3 500.0Mb 11ms DropTail
$ns queue-limit $n2 $n3 49
$ns duplex-link $n3 $n4 500.0Mb 11ms DropTail
$ns queue-limit $n3 $n4 49
$ns duplex-link $n4 $n5 500.0Mb 11ms DropTail
$ns queue-limit $n4 $n5 49
$ns duplex-link $n4 $n6 500.0Mb 11ms DropTail
$ns queue-limit $n4 $n6 49

#Give node position (for NAM)
$ns duplex-link-op $n0 $n3 orient right-down
$ns duplex-link-op $n1 $n3 orient right
$ns duplex-link-op $n2 $n3 orient right-up
$ns duplex-link-op $n3 $n4 orient right
$ns duplex-link-op $n4 $n5 orient right-up
$ns duplex-link-op $n4 $n6 orient right-down

#===================================
#        Agents Definition        
#===================================
#Setup a TCP connection
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set sink3 [new Agent/TCPSink]
$ns attach-agent $n5 $sink3
$ns connect $tcp0 $sink3
$tcp0 set packetSize_ 2000

#Setup a TCP connection
set tcp1 [new Agent/TCP]
$ns attach-agent $n1 $tcp1
set sink2 [new Agent/TCPSink]
$ns attach-agent $n5 $sink2
$ns connect $tcp1 $sink2
$tcp1 set packetSize_ 2000

#Setup a UDP connection
set udp4 [new Agent/UDP]
$ns attach-agent $n2 $udp4
set null5 [new Agent/Null]
$ns attach-agent $n6 $null5
$ns connect $udp4 $null5
$udp4 set packetSize_ 2200


#===================================
#        Applications Definition        
#===================================
#Setup a FTP Application over TCP connection
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ns at 0.1 "$ftp0 start"
$ns at 5.0 "$ftp0 stop"

#Setup a FTP Application over TCP connection
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ns at 0.1 "$ftp1 start"
$ns at 5.0 "$ftp1 stop"

#Setup a CBR Application over UDP connection
set cbr3 [new Application/Traffic/CBR]
$cbr3 attach-agent $udp4
$cbr3 set packetSize_ 1100
$cbr3 set rate_ 2.0Mb
$cbr3 set random_ null
$ns at 0.1 "$cbr3 start"
$ns at 5.0 "$cbr3 stop"


#===================================
#        Termination        
#===================================
#Define a 'finish' procedure
proc finish {} {
    global ns tracefile namfile
    $ns flush-trace
    close $tracefile
    close $namfile
    exec nam sp21-bcs-007.nam &
    exit 0
}
$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "finish"
$ns at $val(stop) "puts \"done\" ; $ns halt"
$ns run
