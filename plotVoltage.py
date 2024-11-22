import numpy as np
import matplotlib.pyplot as plt

def read_membrane_potentials(file_path):
    """
    从文本文件中读取膜电位数据。

    参数：
    file_path: str
        文件路径，文件中每一行表示一个时间点，每行包含多个神经元的膜电位。

    返回：
    data: np.ndarray
        读取的二维数组，形状为 (time_steps, num_neurons)。
    """
    data = np.loadtxt(file_path)
    return data

def plot_membrane_potentials(data, neuron_indices, output_file=None):
    """
    绘制指定神经元的膜电位曲线。

    参数：
    data: np.ndarray
        二维数组，形状为 (time_steps, num_neurons)，表示膜电位数据。
    neuron_indices: list[int]
        要绘制的神经元索引列表。
    output_file: str, optional
        如果提供，则将图形保存到指定路径。
    """
    time_steps = np.arange(data.shape[0])  # 时间点索引
    plt.figure(figsize=(15, 8))
    
    # 绘制每个指定神经元的膜电位曲线
    for idx in neuron_indices:
        if idx >= data.shape[1]:
            print(f"神经元索引 {idx} 超出范围 (0-{data.shape[1]-1})，跳过。")
            continue
        plt.plot(time_steps, data[:, idx], label=f"Neuron {idx}")
    
    # 添加图例和标签
    plt.xlabel("Time Step", fontsize=14)
    plt.ylabel("Membrane Potential", fontsize=14)
    plt.title("Membrane Potential of Selected Neurons", fontsize=16)
    plt.legend(fontsize=12)
    plt.grid(True)

    # 保存图形或显示图形
    if output_file:
        plt.savefig(output_file)
        print(f"图形已保存到 {output_file}")
    else:
        plt.show()

# 示例用法
file_path = "/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/outputE23VoltageTime.st"  # 替换为实际文件路径
data = read_membrane_potentials(file_path)

# 指定要绘制的神经元索引
neuron_indices = [0, 1, 2, 50, 99]  # 例如绘制第 0、1、2、50 和 99 个神经元

# 绘制膜电位曲线并保存结果
output_file = "/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/outputE23VoltageTime.png"  # 可选，若不保存图像则设为 None
plot_membrane_potentials(data, neuron_indices, output_file)
