import numpy as np
import matplotlib.pyplot as plt
import glob
import os
import copy
from datetime import datetime
import random
import string

# 获取文件路径列表，假设文件的路径模式是 'output/*.st'
file_paths = glob.glob('/home/yangjinhao/GeNN/userproject/SingleColumn/output/*.st')

# 定义颜色列表，每个文件分配一种颜色
colors = ['blue', 'red']

def read_spike_data(file_name):
    """读取单个文件，返回时间和神经元编号数组。"""
    times = []
    neuron_ids = []
    
    # 读取文件中的每一行
    with open(file_name, 'r') as file:
        for time_index, line in enumerate(file):
            if line.strip():  # 跳过空行
                # 当前行表示某一时间点放电的神经元 ID
                current_neuron_ids = list(map(int, line.split()))
                times.extend([time_index] * len(current_neuron_ids))  # 时间点为行号
                neuron_ids.extend(current_neuron_ids)  # 神经元 ID
            
    return np.array(times), np.array(neuron_ids)

# 创建一个随机字符串作为标签
def generate_random_label():
    timestamp = datetime.now().strftime("%Y%m%d_%H%M")  # 当前时间
    random_str = ''.join(random.choices(string.ascii_letters + string.digits, k=6))  # 6位随机字符串
    return f"{timestamp}_{random_str}"

# 生成随机标签
random_label = generate_random_label()

# 创建图形
plt.figure(figsize=(30, 15))

# 初始化纵坐标标签和刻度位置列表
group_labels = []
y_ticks = []
offset = 0
bind = 2000

# 遍历文件路径，读取数据并绘制散点图
for idx, file_path in enumerate(file_paths):
    # 读取当前文件数据
    times, neuron_ids = read_spike_data(file_path)
    ind = copy.deepcopy(neuron_ids)
    neuron_ids = neuron_ids + offset + bind  # 纵坐标偏移，用于分开不同文件的神经元
    offset += max(ind) + 1  # 更新偏移量

    # 获取文件的基础名称（不带路径和扩展名）作为群体名称
    group_name = os.path.splitext(os.path.basename(file_path))[0]

    # 绘制该文件的数据，使用相应的颜色
    plt.scatter(times, neuron_ids, s=1, color=colors[idx % len(colors)], marker='.', label=group_name)

    # 保存群体名称和纵坐标位置（用该文件神经元编号的中间值作为标签位置）
    group_labels.append(group_name)
    y_ticks.append(np.median(neuron_ids))  # 用中值作为标签位置

# 设置纵坐标的刻度和标签，显示每个文件对应的群体名称
plt.yticks(y_ticks, group_labels, fontsize=16)
plt.xlabel('Time', fontsize=16)

# 添加图例
output_path = f"/home/yangjinhao/GeNN/userproject/SingleColumn/output/Fig/V1_{random_label}.png"
plt.tight_layout()
plt.savefig(output_path)

print(f"Figure saved at {output_path}")
