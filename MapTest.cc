#include <map>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    map<string,int> neuron_number={
            {"1", 15545},
            {"23", 60753},
            {"4", 87985},
            {"5", 25295},
            {"6", 23903},
            {"total", 213481},
            {"H1", 15545},
            {"E23", 51738},
            {"S23", 1892},
            {"P23", 2610},
            {"H23", 4514},
            {"E4", 74933},
            {"S4", 4041},
            {"P4", 7037},
            {"H4", 1973},
            {"E5", 21624},
            {"S5", 1586},
            {"P5", 1751},
            {"H5", 334},
            {"E6", 20278},
            {"S6", 1667},
            {"P6", 1656},
            {"H6", 302}
    };
    vector<string> NeuronType={"E","S","P","H"};
    vector<string> LayerList={"1","23","4","5","6"};
    string PopList[17];
    PopList[0]="H1";
    int PopNum=1;
    for (auto layer = LayerList.begin()+1; layer != LayerList.end(); layer++){
        for (auto pop = NeuronType.begin(); pop != NeuronType.end(); pop++){
                PopList[PopNum]=*pop+*layer;
                PopNum++;
        }
    }
    for (int i=0;i<17;i++){
        cout<<PopList[i]<<" "<<neuron_number[PopList[i]]<<endl;
    }
    return 0;
}