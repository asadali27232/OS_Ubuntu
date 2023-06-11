import matplotlib.pyplot as plt

# Initialize variables
packet_sent = 0
packet_delivered = 0
packet_dropped = 0
packet_received = 0
packet_size = 0
packet_loss_ratio = 0
total_packet_size = 0
start_time = 0
end_time = 0

# Lists to store data for plotting
time_list = []
goodput_list = []
congestion_window_list = []
rtt_list = []
packet_loss_ratio_list = []
throughput_list = []
delivery_ratio_list = []

with open('sp21-bcs-007.tr', 'r') as file:
    for line in file:
        # Skip lines starting with '+', '-', or 'd'
        if line.startswith(('+', '-', 'd')):
            continue

        # Split line into fields
        fields = line.strip().split()

        # Event data fields
        event_type = fields[0]
        event_time = float(fields[1])
        from_node = int(fields[2])
        to_node = int(fields[3])
        pkt_type = fields[4]
        pkt_size = int(fields[5])
        flags = fields[6]
        fid = fields[7]
        sic_addr = fields[8]
        dst_addr = fields[9]
        seq_num = int(fields[10])
        pkt_id = int(fields[11])

        # Update start and end time
        if event_time < start_time:
            start_time = event_time
        if event_time > end_time:
            end_time = event_time

        # Add event time to the time_list
        time_list.append(event_time)

        # Calculate Network Goodput
        if pkt_type == 'tcp':
            packet_sent += 1
            packet_size += pkt_size
            goodput_list.append(packet_size / (event_time - start_time))

        # Calculate Congestion Window
        if flags == '-------':
            congestion_window_list.append(pkt_size)

        # Calculate Packet Loss Ratio
        if pkt_type == 'tcp' and flags == '-------':
            packet_delivered += 1
        elif pkt_type == 'tcp' and flags == 'd':
            packet_dropped += 1

        # Calculate Throughput
        total_packet_size += pkt_size
        throughput_list.append(total_packet_size / (event_time - start_time))

        # Calculate Packet Delivery Ratio
        if pkt_type in ['tcp', 'cbr'] and flags == 'r':
            packet_received += 1
        if packet_sent != 0:
            delivery_ratio_list.append(packet_received / packet_sent)
        else:
            delivery_ratio_list.append(0)

        # Calculate Round Trip Time
        if pkt_type == 'ack' and flags == '1':
            rtt = event_time - start_time
            rtt_list.append(rtt)

# Calculate Network Goodput
network_goodput = packet_size / (end_time - start_time)

# Calculate Packet Loss Ratio
packet_loss_ratio = packet_dropped / packet_sent

# Print the results
print("a. Network Goodput:", network_goodput)
print("b. Congestion Window:", congestion_window_list)
print("c. Round Trip Time:", rtt_list)
print("d. Packet Loss Ratio:", packet_loss_ratio)
print("e. Throughput:", throughput_list)
print("f. Packet Delivery Ratio:", delivery_ratio_list)

# Chop the lists to include only 50 values
chopped_time_list = time_list[:50]
chopped_goodput_list = goodput_list[:50]
chopped_congestion_window_list = congestion_window_list[:50]
chopped_rtt_list = rtt_list[:50]
chopped_packet_loss_ratio_list = packet_loss_ratio_list[:50]
chopped_throughput_list = throughput_list[:50]
chopped_delivery_ratio_list = delivery_ratio_list[:50]

# Plot and save separate graphs for each metric

# Network Goodput
plt.plot(chopped_time_list, chopped_goodput_list)
plt.xlabel("Time")
plt.ylabel("Network Goodput")
plt.title("Network Goodput")
plt.savefig("network_goodput.png")
plt.clf()

# Congestion Window
plt.plot(chopped_time_list, chopped_congestion_window_list)
plt.xlabel("Time")
plt.ylabel("Congestion Window")
plt.title("Congestion Window")
plt.savefig("congestion_window.png")
plt.clf()

# Round Trip Time
plt.plot(chopped_time_list, chopped_rtt_list)
plt.xlabel("Time")
plt.ylabel("Round Trip Time")
plt.title("Round Trip Time")
plt.savefig("round_trip_time.png")
plt.clf()

# Packet Loss Ratio
plt.plot(chopped_time_list, chopped_packet_loss_ratio_list)
plt.xlabel("Time")
plt.ylabel("Packet Loss Ratio")
plt.title("Packet Loss Ratio")
plt.savefig("packet_loss_ratio.png")
plt.clf()

# Throughput
plt.plot(chopped_time_list, chopped_throughput_list)
plt.xlabel("Time")
plt.ylabel("Throughput")
plt.title("Throughput")
plt.savefig("throughput.png")
plt.clf()

# Packet Delivery Ratio
plt.plot(chopped_time_list, chopped_delivery_ratio_list)
plt.xlabel("Time")
plt.ylabel("Packet Delivery Ratio")
plt.title("Packet Delivery Ratio")
plt.savefig("packet_delivery_ratio.png")
plt.clf()