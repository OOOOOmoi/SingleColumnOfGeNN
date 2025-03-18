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

# 定义颜色列表，每个文件分配一种颜色（蓝色 & 红色交替）
colors = ['blue', 'red']

def read_spike_data(file_name):
    """读取单个文件，并返回前 5% 神经元的时间和神经元编号数组。"""
    times = []
    neuron_ids = []
    
    with open(file_name, 'r') as file:
        for time_index, line in enumerate(file):
            if line.strip():  # 跳过空行
                current_neuron_ids = list(map(int, line.split()))
                times.extend([time_index] * len(current_neuron_ids))  # 时间点为行号
                neuron_ids.extend(current_neuron_ids)  # 神经元 ID

    # 转换为 NumPy 数组
    times = np.array(times)
    neuron_ids = np.array(neuron_ids)

    # 确保数据不为空
    if len(neuron_ids) == 0:
        return np.array([]), np.array([])

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

# 创建图形
plt.figure(figsize=(30, 15))

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


    # 绘制点图，颜色交替
    plt.scatter(times, neuron_ids, s=10, color=colors[idx % len(colors)], marker='o', label=group_name)

    # 存储群体名称 & 纵坐标位置（使用中值）
    group_labels.append(group_name)
    y_ticks.append(np.median(neuron_ids))

# 设置纵坐标的刻度和标签
plt.yticks(y_ticks, group_labels, fontsize=16)
plt.xlabel('TimeStep', fontsize=16)
plt.title('Raster Plot of Top 5% Neurons in Each Group', fontsize=18)

# 保存图像
output_path = f"/home/yangjinhao/GeNN/userproject/SingleColumn/output/Fig/V1_{random_label}.png"
plt.tight_layout()
plt.savefig(output_path)

print(f"Figure saved at {output_path}")
