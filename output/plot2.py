import numpy as np
import matplotlib.pyplot as plt
import glob
import os
import copy
from datetime import datetime
import random
import string

# 获取文件路径列表，假设文件的路径模式是 'data/*.txt'，可以根据实际情况修改
file_paths = glob.glob('/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/output/*.st')

# 定义颜色列表，每个文件分配一种颜色
colors=['blue','red']

def read_spike_data(file_name):
    """读取单个文件，返回时间和神经元编号数组。"""
    times = []
    neuron_ids = []
    
    # 读取文件中的时间和神经元编号
    with open(file_name, 'r') as file:
        for line in file:
            if line.strip():
                time, neuron_id = line.split()
                times.append(float(time))
                neuron_ids.append(int(neuron_id))
    
    return np.array(times), np.array(neuron_ids)

# 创建一个随机字符串作为标签
def generate_random_label():
    timestamp = datetime.now().strftime("%Y%m%d_%H%M")  # 当前时间
    random_str = ''.join(random.choices(string.ascii_letters + string.digits, k=6))  # 6位随机字符串
    return f"{timestamp}_{random_str}"

# 生成随机标签
random_label = generate_random_label()

# 创建图形
plt.figure(figsize=(30,15))

# 初始化纵坐标标签和刻度位置列表
group_labels = []
y_ticks = []
offset=0
bind=2000
# 遍历文件路径，读取数据并绘制散点图
for idx, file_path in enumerate(file_paths):
    # 读取当前文件数据
    times, neuron_ids = read_spike_data(file_path)
    ind=copy.deepcopy(neuron_ids)
    neuron_ids=neuron_ids+offset+bind
    offset += max(ind)+1
    # 获取文件的基础名称（不带路径和扩展名）作为群体名称
    group_name = os.path.splitext(os.path.basename(file_path))[0]
    
    # 绘制该文件的数据，使用相应的颜色
    plt.scatter(times, neuron_ids, s=1, color=colors[idx%2], marker='.', label=group_name)
    
    # 保存群体名称和纵坐标位置（用该文件神经元编号的中间值作为标签位置）
    group_labels.append(group_name)
    y_ticks.append(np.median(neuron_ids))  # 用中值作为标签位置

# 设置纵坐标的刻度和标签，显示每个文件对应的群体名称
plt.yticks(y_ticks, group_labels,fontsize=16)
plt.xlabel('Time',fontsize=16)

# 添加图例
outputPath=f"/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/output/Fig/V1_{random_label}.png"
plt.tight_layout()
plt.savefig(outputPath)
