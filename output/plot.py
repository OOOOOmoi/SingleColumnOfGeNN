# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import glob
import copy

file_paths = glob.glob('/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/output/*.st')

def read_spike_data(file_name):
    times = []
    neuron_ids = []
    
    with open(file_name, 'r') as file:
        for line in file:
            if line.strip():
                time, neuron_id = line.split()
                times.append(float(time))
                neuron_ids.append(int(neuron_id))
    
    return np.array(times), np.array(neuron_ids)

# 初始化全局时间和神经元编号数组
all_times = []
all_neuron_ids = []

# 设置每个文件的偏移量
offset = 0

for file_path in file_paths:
    # 读取当前文件的数据
    times, neuron_ids = read_spike_data(file_path)
    ind=copy.deepcopy(neuron_ids)

    # 为神经元编号增加偏移量，避免编号重叠
    neuron_ids += offset

    # 更新偏移量（可以设置为当前文件中的神经元数量）
    offset += max(ind) + 1
    
    # 将数据添加到全局列表中
    all_times.extend(times)
    all_neuron_ids.extend(neuron_ids)

# 转换为 NumPy 数组以便于绘图
all_times = np.array(all_times)
all_neuron_ids = np.array(all_neuron_ids)

# 绘制散点图
plt.figure(figsize=(10, 8))
plt.scatter(all_times, all_neuron_ids, s=1, color='blue', marker='.')
plt.xlabel('Time')
plt.ylabel('Neuron ID')
plt.tight_layout()
plt.savefig("/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/output/output.png")
