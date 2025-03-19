import numpy as np
import matplotlib.pyplot as plt
import os
import copy
from datetime import datetime
import random
import string

# 初始化 PopList
NeuronType = ["E", "S", "P", "V"]
LayerList = ["1", "23", "4", "5", "6"]
PopList = ["H1"]
for layer in LayerList[1:]:
    for pop in NeuronType:
        PopList.append(pop + layer)
PopList.reverse()

# 文件路径模板
file_path_template = '/home/yangjinhao/GeNN/userproject/SingleColumn/output/{}.st'

# 计算放电率的时间窗口（ms）
bin_size = 50  # 50ms 时间窗口
time_threshold = 100  # 忽略前 100ms 的数据

def read_spike_data(file_name, time_threshold=100):
    """读取单个文件，并返回前 5% 神经元的时间和神经元编号数组，同时略去前 100ms 的数据。"""
    times = []
    neuron_ids = []
    
    with open(file_name, 'r') as file:
        for time_index, line in enumerate(file):
            if line.strip():  # 跳过空行
                current_neuron_ids = list(map(int, line.split()))
                times.extend([time_index] * len(current_neuron_ids))  # 记录时间点
                neuron_ids.extend(current_neuron_ids)  # 记录神经元 ID

    # 转换为 NumPy 数组
    times = np.array(times)
    neuron_ids = np.array(neuron_ids)

    # 确保数据不为空
    if len(neuron_ids) == 0:
        return np.array([]), np.array([])

    # 过滤掉 100ms 以内的时间点
    mask = times >= time_threshold
    times = times[mask]
    neuron_ids = neuron_ids[mask]

    # 计算前 5% 的神经元 ID 阈值
    threshold = np.percentile(neuron_ids, 5)

    # 仅保留前 5% 的神经元 ID
    mask = neuron_ids <= threshold
    return times[mask], neuron_ids[mask]

# 生成随机标签（用于保存文件）
def generate_random_label():
    timestamp = datetime.now().strftime("%Y%m%d_%H%M")
    random_str = ''.join(random.choices(string.ascii_letters + string.digits, k=6))
    return f"{timestamp}_{random_str}"

random_label = generate_random_label()

# 🎨 颜色映射
cmap = plt.cm.get_cmap("tab10", len(PopList))

# 创建两个子图：1. Raster Plot  2. 放电率变化
fig, axes = plt.subplots(2, 1, figsize=(30, 20), sharex=True, gridspec_kw={'height_ratios': [2, 1]})

# 初始化纵坐标标签和刻度位置列表
group_labels = []
y_ticks = []
offset = 0  # Y 轴偏移量
bind = 2000  # 纵向间隔

# 遍历 PopList，生成文件路径并绘制数据
for idx, pop in enumerate(PopList):
    file_path = file_path_template.format(pop)
    
    # 检查文件是否存在
    if not os.path.exists(file_path):
        print(f"File not found: {file_path}")
        continue

    # 读取前 5% 神经元的数据
    times, neuron_ids = read_spike_data(file_path)

    if len(neuron_ids) == 0:
        print(f"No valid neurons found in {file_path}")
        continue

    # 记录原始神经元 ID 以计算偏移量
    original_neuron_ids = copy.deepcopy(neuron_ids)

    # 纵坐标偏移
    neuron_ids = neuron_ids + offset + bind
    offset += max(original_neuron_ids) + 1  # 更新偏移量

    # 设置神经元群名称
    group_name = pop

    # 🎨 选取颜色
    color = cmap(idx % cmap.N)

    # 🎯 绘制 Raster Plot（散点图）
    axes[0].scatter(times, neuron_ids, s=10, color=color, marker='o', label=group_name)

    # 计算放电率（Firing Rate）
    max_time = np.max(times) if len(times) > 0 else 0
    bins = np.arange(time_threshold, max_time + bin_size, bin_size)  # 100ms 之后的时间窗口
    spike_counts, _ = np.histogram(times, bins)  # 统计每个时间窗口内的放电次数

    firing_rate = spike_counts / (bin_size / 1000.0)  # 计算放电率（spikes/s）

    # 🎯 绘制放电率变化（折线图）
    bin_centers = bins[:-1] + bin_size / 2  # 时间窗口中心点
    axes[1].plot(bin_centers, firing_rate, color=color, label=group_name, linewidth=2)

    # 存储群体名称 & 纵坐标位置（使用中值）
    group_labels.append(group_name)
    y_ticks.append(np.median(neuron_ids))

# 🎨 设置 Raster Plot（散点图）属性
axes[0].set_yticks(y_ticks)
axes[0].set_yticklabels(group_labels, fontsize=16)
axes[0].set_ylabel("Neuron Groups", fontsize=16)
axes[0].set_title("Raster Plot of Top 5% Neurons", fontsize=18)

# 🎨 设置 Firing Rate Plot（放电率曲线）属性
axes[1].set_ylabel("Firing Rate (spikes/s)", fontsize=16)
axes[1].set_xlabel("Time (ms)", fontsize=16)
axes[1].set_title("Firing Rate Over Time", fontsize=18)
axes[1].legend(fontsize=14)

# 🔹 **裁剪 X 轴**，确保从 100ms 开始
axes[0].set_xlim(time_threshold, max_time)
axes[1].set_xlim(time_threshold, max_time)

# 保存图像
output_path = f"/home/yangjinhao/GeNN/userproject/SingleColumn/output/Fig/V1_{random_label}.png"
plt.tight_layout()
plt.savefig(output_path)

print(f"Figure saved at {output_path}")
import numpy as np
import matplotlib.pyplot as plt
import os
import copy
from datetime import datetime
import random
import string

# 初始化 PopList
NeuronType = ["E", "S", "P", "V"]
LayerList = ["1", "23", "4", "5", "6"]
PopList = ["H1"]
for layer in LayerList[1:]:
    for pop in NeuronType:
        PopList.append(pop + layer)
PopList.reverse()

# 文件路径模板
file_path_template = '/home/yangjinhao/GeNN/userproject/SingleColumn/output/{}.st'

# 计算放电率的时间窗口（ms）
bin_size = 50  # 50ms 时间窗口
time_threshold = 100  # 忽略前 100ms 的数据

def read_spike_data(file_name, time_threshold=100):
    """读取单个文件，并返回前 5% 神经元的时间和神经元编号数组，同时略去前 100ms 的数据。"""
    times = []
    neuron_ids = []
    
    with open(file_name, 'r') as file:
        for time_index, line in enumerate(file):
            if line.strip():  # 跳过空行
                current_neuron_ids = list(map(int, line.split()))
                times.extend([time_index] * len(current_neuron_ids))  # 记录时间点
                neuron_ids.extend(current_neuron_ids)  # 记录神经元 ID

    # 转换为 NumPy 数组
    times = np.array(times)
    neuron_ids = np.array(neuron_ids)

    # 确保数据不为空
    if len(neuron_ids) == 0:
        return np.array([]), np.array([])

    # 过滤掉 100ms 以内的时间点
    mask = times >= time_threshold
    times = times[mask]
    neuron_ids = neuron_ids[mask]

    # 计算前 5% 的神经元 ID 阈值
    threshold = np.percentile(neuron_ids, 5)

    # 仅保留前 5% 的神经元 ID
    mask = neuron_ids <= threshold
    return times[mask], neuron_ids[mask]

# 生成随机标签（用于保存文件）
def generate_random_label():
    timestamp = datetime.now().strftime("%Y%m%d_%H%M")
    random_str = ''.join(random.choices(string.ascii_letters + string.digits, k=6))
    return f"{timestamp}_{random_str}"

random_label = generate_random_label()

# 🎨 颜色映射
cmap = plt.cm.get_cmap("tab10", len(PopList))

# 创建两个子图：1. Raster Plot  2. 放电率变化
fig, axes = plt.subplots(2, 1, figsize=(30, 20), sharex=True, gridspec_kw={'height_ratios': [2, 1]})

# 初始化纵坐标标签和刻度位置列表
group_labels = []
y_ticks = []
offset = 0  # Y 轴偏移量
bind = 2000  # 纵向间隔

# 遍历 PopList，生成文件路径并绘制数据
for idx, pop in enumerate(PopList):
    file_path = file_path_template.format(pop)
    
    # 检查文件是否存在
    if not os.path.exists(file_path):
        print(f"File not found: {file_path}")
        continue

    # 读取前 5% 神经元的数据
    times, neuron_ids = read_spike_data(file_path)

    if len(neuron_ids) == 0:
        print(f"No valid neurons found in {file_path}")
        continue

    # 记录原始神经元 ID 以计算偏移量
    original_neuron_ids = copy.deepcopy(neuron_ids)

    # 纵坐标偏移
    neuron_ids = neuron_ids + offset + bind
    offset += max(original_neuron_ids) + 1  # 更新偏移量

    # 设置神经元群名称
    group_name = pop

    # 🎨 选取颜色
    color = cmap(idx % cmap.N)
    colors = ['blue','red']
    # 🎯 绘制 Raster Plot（散点图）
    axes[0].scatter(times, neuron_ids, s=10, color=colors[idx % len(colors)], marker='o', label=group_name)

    # 计算放电率（Firing Rate）
    max_time = np.max(times) if len(times) > 0 else 0
    bins = np.arange(time_threshold, max_time + bin_size, bin_size)  # 100ms 之后的时间窗口
    spike_counts, _ = np.histogram(times, bins)  # 统计每个时间窗口内的放电次数

    firing_rate = spike_counts / (bin_size / 1000.0)  # 计算放电率（spikes/s）

    # 🎯 绘制放电率变化（折线图）
    bin_centers = bins[:-1] + bin_size / 2  # 时间窗口中心点
    axes[1].plot(bin_centers, firing_rate, color=color, label=group_name, linewidth=2)

    # 存储群体名称 & 纵坐标位置（使用中值）
    group_labels.append(group_name)
    y_ticks.append(np.median(neuron_ids))

# 🎨 设置 Raster Plot（散点图）属性
axes[0].set_yticks(y_ticks)
axes[0].set_yticklabels(group_labels, fontsize=16)
axes[0].set_ylabel("Neuron Groups", fontsize=16)
axes[0].set_title("Raster Plot of Top 5% Neurons", fontsize=18)

# 🎨 设置 Firing Rate Plot（放电率曲线）属性
axes[1].set_ylabel("Firing Rate (spikes/s)", fontsize=16)
axes[1].set_xlabel("Time (ms)", fontsize=16)
axes[1].set_title("Firing Rate Over Time", fontsize=18)
axes[1].legend(fontsize=14)

# 🔹 **裁剪 X 轴**，确保从 100ms 开始
axes[0].set_xlim(time_threshold, max_time)
axes[1].set_xlim(time_threshold, max_time)

# 保存图像
output_path = f"/home/yangjinhao/GeNN/userproject/SingleColumn/output/Fig/V1_{random_label}.png"
plt.tight_layout()
plt.savefig(output_path)

print(f"Figure saved at {output_path}")
