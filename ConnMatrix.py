import numpy as np
import matplotlib.pyplot as plt

# 读取第一个文件（存储 synapsesnum）
def read_synapses_file(file_path):
    """读取第一个文件，返回 (src, tar) 对应的 synapsesnum"""
    synapses = {}
    with open(file_path, 'r') as file:
        for line in file:
            if line.strip():
                srcname, tarname, synapsesnum = line.split()
                synapses[(srcname, tarname)] = float(synapsesnum)
    return synapses

# 读取第二个文件（存储 synWeight 和 synSd）
def read_weights_file(file_path):
    """读取第二个文件，返回 (src, tar) 对应的 synWeight"""
    weights = {}
    with open(file_path, 'r') as file:
        for line in file:
            if line.strip():
                srcname, tarname, synWeight, synSd = line.split()
                weights[(srcname, tarname)] = float(synWeight)
    return weights

# 构建最终的连接矩阵
def build_weighted_matrix(synapses, weights, src_nodes, tar_nodes):
    """根据 synapses 和 weights 构建最终连接矩阵"""
    # 创建源节点和目标节点的索引映射
    src_index = {node: idx for idx, node in enumerate(src_nodes)}
    tar_index = {node: idx for idx, node in enumerate(tar_nodes)}

    # 初始化矩阵
    matrix = np.zeros((len(src_nodes), len(tar_nodes)))

    # 填充矩阵
    for (src, tar), synapsesnum in synapses.items():
        if (src, tar) in weights:  # 如果权重文件中存在该连接
            weighted_value = synapsesnum * weights[(src, tar)] / 20000
            matrix[src_index[src], tar_index[tar]] = weighted_value

    return matrix

# 绘制连接矩阵
def plot_connection_matrix(matrix, src_nodes, tar_nodes, output_path="connection_matrix.png"):
    """绘制连接矩阵并保存为图片"""
    plt.figure(figsize=(10, 8))
    cmap = 'seismic'  # 或者 'coolwarm'
    vmin = -max(abs(matrix.min()), abs(matrix.max()))  # 保证正负对称
    vmax = max(abs(matrix.min()), abs(matrix.max()))
    plt.imshow(matrix, cmap=cmap, interpolation='nearest',vmin=vmin,vmax=vmax)
    plt.colorbar(label='Weighted Synapses')  # 添加颜色条
    plt.xticks(ticks=np.arange(len(tar_nodes)), labels=tar_nodes, rotation=90)
    plt.yticks(ticks=np.arange(len(src_nodes)), labels=src_nodes)
    plt.xlabel('Target Neurons')
    plt.ylabel('Source Neurons')
    plt.title('Weighted Connection Matrix')
    plt.tight_layout()

    # 保存图片
    plt.savefig(output_path)
    print(f"Connection matrix saved as {output_path}")
    plt.show()

# 主程序
if __name__ == "__main__":
    # 文件路径
    synapses_file_path = "/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/SynapsesInd.txt"  # 第一个文件路径
    weights_file_path = "/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/SynapsesWeight.txt"    # 第二个文件路径

    # 读取数据
    synapses = read_synapses_file(synapses_file_path)
    weights = read_weights_file(weights_file_path)

    # 获取所有源节点和目标节点
    src_nodes = sorted(set(src for src, _ in synapses.keys()))
    tar_nodes = sorted(set(tar for _, tar in synapses.keys()))

    # 构建最终的连接矩阵
    matrix = build_weighted_matrix(synapses, weights, src_nodes, tar_nodes)

    # 绘制并保存连接矩阵
    plot_connection_matrix(matrix, src_nodes, tar_nodes, output_path="/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/weighted_connection_matrix.png")
