# 定义列表
NeuronType = ["E", "S", "P", "V"]
LayerList = ["1", "23", "4", "5", "6"]
PopList = ["H1"]  # 初始化列表
PopNum = 1
outDir="/home/yangjinhao/SingleColumn/output"
# 遍历 LayerList 中的元素（跳过第一个元素 "1"）
for layer in LayerList[1:]:
    for pop in NeuronType:
        PopList.append(pop + layer)
ind=0
# 生成函数调用代码
with open("/home/yangjinhao/GeNN/genn-master/userproject/SingleColumn/generated_calls.txt", "w") as f:
    i=0
    for pop in PopList:
        f.write(f"pull{pop}CurrentSpikesFromDevice();\n")
        # f.write(f"     IntoFile(glbSpk{pop},glbSpkCnt{pop},outPuts[{i}]);\n")
        f.write(f"for (int i=0;i<*glbSpkCnt{pop};i++){{\n")
        f.write(f"    outPuts[{ind}]<<glbSpk{pop}[i];\n")
        f.write(f"    if(unsigned int i<*glbSpkCnt{pop}-1){{\n")
        f.write(f"        outPuts[{ind}]<<\" \";\n")
        f.write(f"    }}\n")
        f.write(f"}}\n")
        f.write(f"outPuts[{ind}]<<endl;\n")
        ind+=1
    # for pop in PopList:
    #     f.write(f"ofstream({outDir}/{pop}.st);\n")
    # for pop in PopList:
    # f.write(f"    pullCurrentV{pop}FromDevice();\n")
    # f.write(f"    VoltageIntoFile(V{pop},outPuts[{i}],\"{pop}\");\n")
