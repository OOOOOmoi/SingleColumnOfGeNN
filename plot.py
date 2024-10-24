import numpy as np
import matplotlib.pyplot as plt

# 定义读取数据的函数
def read_spike_data(file_name):
    times = []
    neuron_ids = []
    
    # 打开文件并逐行读取
    with open(file_name, 'r') as file:
        for line in file:
            # 跳过空行
            if line.strip():
                time, neuron_id = line.split()
                times.append(float(time))
                neuron_ids.append(int(neuron_id))
    
    return np.array(times), np.array(neuron_ids)

# 读取三个文件中的数据
file1 = '/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/outputH1SpikeTime'
file2 = '/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/outputE23SpikeTime'
file3 = '/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/outputE6SpikeTime'

times1, neuron_ids1 = read_spike_data(file1)
times2, neuron_ids2 = read_spike_data(file2)
times3, neuron_ids3 = read_spike_data(file3)

# 保存第一个文件的散点图
plt.figure(figsize=(30,10))
plt.scatter(times1, neuron_ids1, color='blue', s=0.01, marker='.')
plt.title('Spike Events from File 1')
plt.xlabel('Time (ms)')
plt.ylabel('Neuron ID')
plt.tight_layout()
plt.savefig('H1Spike.png')  # 保存为文件名 'spike_plot_file1.png'
plt.close()

# 保存第二个文件的散点图
plt.figure(figsize=(30,10))
plt.scatter(times2, neuron_ids2, color='red', s=0.01, marker='.')
plt.title('Spike Events from File 2')
plt.xlabel('Time (ms)')
plt.ylabel('Neuron ID')
plt.tight_layout()
plt.savefig('E23Spike.png')  # 保存为文件名 'spike_plot_file2.png'
plt.close()

# 保存第三个文件的散点图
plt.figure(figsize=(30,10))
plt.scatter(times3, neuron_ids3, color='green', s=0.01, marker='.')
plt.title('Spike Events from File 3')
plt.xlabel('Time (ms)')
plt.ylabel('Neuron ID')
plt.tight_layout()
plt.savefig('E6Spike.png')  # 保存为文件名 'spike_plot_file3.png'
plt.close()