BEGIN {
    recvdSize = 0
    transSize = 0
    startTime = 400
    stopTime = 0
    throughput = 0
}

{
    event = $1
    time = $2
    send_id = $3
    rec_id = $4
    event_type = $5
    pkt_size = $6
    flow_id = $8

    # Store start time
    if (send_id == "0") {
        if (time < startTime) {
            startTime = time
        }

        if (event == "+") {
            # Store transmitted packet's size
            transSize += pkt_size
        }
    }

    # Update total received packets' size and store packets arrival time
    if (event == "r" && rec_id == "3" && event_type == "tcp") {
        if (time > stopTime) {
            stopTime = time
        }
        # Store received packet's size
        if (flow_id == "0") {
            recvdSize += pkt_size
        }
    }
}

END {
    throughput = (recvdSize * 8) / (stopTime - startTime)
    printf("%.2f\t%.2f\t%.2f\n", startTime, stopTime, recvdSize)
    printf("Throughput: %.2f\n", throughput)
}
