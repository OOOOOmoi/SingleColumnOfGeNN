import os
import json
from collections import OrderedDict
DataPath=os.path.join("/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/custom_Data_Model_6b76eb0c02b1211978e7dd25477ecd56.json")
file1=os.path.join("/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/SynapsesWeight.txt")
file2=os.path.join("/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/ExternalSynapses.txt")
file3=os.path.join("/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/SynapsesNumber.txt")
with open(DataPath,'r') as f:
    ParamOfAll=json.load(f)
SynapsesWeightMean=OrderedDict()
SynapsesWeightSd=OrderedDict()
PopListOfV1=ParamOfAll['structure']['V1']
SynapsesWeightMean=ParamOfAll["synapse_weights_mean"]
SynapsesWeightSd=ParamOfAll["synapse_weights_sd"]
SynapsesNumber=ParamOfAll["synapses"]
# 打开两个文件，分别保存数据
with open(file1, 'w') as f1, open(file2, 'w') as f2, open(file3, 'w') as f3:
    # 用于存储 popTar 和 wEx 的集合，避免重复写入
    popTar_wEx_written = set()

    for popSrc in PopListOfV1:
        for popTar in PopListOfV1:
            # 从数据字典中获取 wAve, wSd, wEx
            wAve = SynapsesWeightMean['V1'][popTar]['V1'][popSrc]
            wSd = SynapsesWeightSd['V1'][popTar]['V1'][popSrc]
            wEx = SynapsesWeightMean['V1'][popTar]["external"]["external"]
            synNum = SynapsesNumber['V1'][popTar]['V1'][popSrc]

            # 写入第一个文件：popSrc popTar wAve wSd
            f1.write(f"{popSrc} {popTar} {wAve} {wSd}\n")
            f3.write(f"{popSrc} {popTar} {synNum}\n")
            # 如果 popTar 尚未写入第二个文件，写入 popTar 和 wEx
            if popTar not in popTar_wEx_written:
                f2.write(f"{popTar} {wEx}\n")
                popTar_wEx_written.add(popTar)  # 记录 popTar，防止重复写入