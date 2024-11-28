i=0;i<*glbSpkCnt{pop};i++){{\n")
        f.write(f"    outPuts[{ind}]<<glbSpk{pop}[i];\n")
        f.write(f"    if(i<*glbSpkCnt{pop}-1){{\n")
        f.write(f"        outPuts[{ind}]<<\" \";\n")
        f.write(f"    }}\n")
        f.write(f"}}\n")
        f.write(f"outPuts[{ind}]<<endl;\n")
        ind+=1