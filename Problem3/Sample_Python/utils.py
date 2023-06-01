#!/usr/bin/python3
import matplotlib.pyplot as plt
import sys
import numpy as np


def add_items(list1, list2):
  if len(list1) == 0:
    return list2
  elif len(list2) == 0:
    return list1
  else:
    res_list = [] 
    for i in range(0, len(list1)): 
      res_list.append(list1[i] + list2[i])
    return res_list

def link_count(sign, file_name, source_node,  dest_node, flow):
  count = 0
  of = open("traces/"+file_name,"r")
  lines = [i.strip().split() for i in of.readlines()]
  of.close()
  for line in lines:
    event = line[0]
    source = line[2]
    dest = line[3]
    size = line[5]
    flag = line[7]
    if  event == sign and source == str(source_node) and dest == str(dest_node) and int(size) >= 1000 and int(flag) == flow:
      count += 1
  return count

