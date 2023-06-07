# create three nodes
set node(0) [$ns node]
set node(1) [$ns node]
set node(2) [$ns node]

# create links between the nodes
$ns duplex-link $node(0) $node(1) 1Mb 10ms DropTail
$ns duplex-link $node(1) $node(2) 1Mb 10ms DropTail

# create a router for the topology (using OSPF protocol)
set router [$ns node]
$router set router-agt_ "Agent/OSPF"

foreach n [$ns nodes] {
  if {$n != $router} {
    # add a connection to each node that is not a router
    $ns attach-agent $n [$n get-addr]
    $ns attach-agent $router [$router get-addr]
    $ns connect $n $router
  }
}  
