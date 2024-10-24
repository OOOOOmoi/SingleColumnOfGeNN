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

# 定义计算放电率的函数
def compute_spike_rate(times, window_length_ms):
    """
    times: array-like, 所有的时间点
    window_length_ms: int, 时间窗的长度（以 ms 为单位）
    
    返回时间窗中心点以及对应的放电率
    """
    max_time = np.max(times)  # 找到最大时间
    time_bins = np.arange(0, max_time + window_length_ms, window_length_ms)  # 创建时间窗
    spike_counts, _ = np.histogram(times, bins=time_bins)  # 统计每个时间窗内的放电数量
    
    # 将时间窗中的计数转化为放电率（Hz）
    spike_rate = spike_counts / (window_length_ms / 1000.0)  # 将 ms 转化为秒
    
    # 计算每个时间窗的中心点，用于绘制曲线
    time_bin_centers = (time_bins[:-1] + time_bins[1:]) / 2
    
    return time_bin_centers, spike_rate

def plot_spike_and_rate(times, neuron_ids, time_bin_centers, spike_rate, file_name):
    """
    绘制放电散点图和放电率曲线，并保存为文件
    """
    fig, axs = plt.subplots(2, 1, figsize=(8, 6), sharex=True)
    
    # 绘制放电散点图
    axs[0].scatter(times, neuron_ids, color='blue', s=0.01, marker='o')
    axs[0].set_title('Spike Times')
    axs[0].set_ylabel('Neuron ID')
    
    # 绘制放电率曲线
    axs[1].plot(time_bin_centers, spike_rate, color='red')
    axs[1].set_title('Spike Rate')
    axs[1].set_xlabel('Time (ms)')
    axs[1].set_ylabel('Spike Rate (Hz)')
    
    plt.tight_layout()
    plt.savefig(file_name)
    plt.close()

# 读取三个文件中的数据
file1 = '/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/outputH1SpikeTime'
file2 = '/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/outputE23SpikeTime'
file3 = '/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/outputE6SpikeTime'

times1, neuron_ids1 = read_spike_data(file1)
times2, neuron_ids2 = read_spike_data(file2)
times3, neuron_ids3 = read_spike_data(file3)

# 设置放电率时间窗
window_length_ms = 100  # 100ms 的时间窗

# 计算放电率
time_bin_centers1, spike_rate1 = compute_spike_rate(times1, window_length_ms)
time_bin_centers2, spike_rate2 = compute_spike_rate(times2, window_length_ms)
time_bin_centers3, spike_rate3 = compute_spike_rate(times3, window_length_ms)

plot_spike_and_rate(times1, neuron_ids1, time_bin_centers1, spike_rate1, '/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/H1Spike.png')
plot_spike_and_rate(times2, neuron_ids2, time_bin_centers2, spike_rate2, '/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/E23Spike.png')
plot_spike_and_rate(times3, neuron_ids3, time_bin_centers3, spike_rate3, '/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/E6Spike.png')