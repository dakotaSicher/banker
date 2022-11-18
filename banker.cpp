#include <fstream>
#include <iostream>

using std::ifstream;

void print_state(int*, int**, int**, int, int, bool*);
int  process_remaining(bool*,int);

int main(){ 
    ifstream fin("process.txt");

    int r_count;
    fin >> r_count;

//    std::cout << r_count << std::endl;

    int* avail = new int[r_count];
    for(int i=0; i < r_count; ++i)
        fin >> avail[i];

    int p_count;
    fin >> p_count;

    int** p_aloc = new int*[p_count];
    int** p_max  = new int*[p_count];
    int** p_need = new int*[p_count];
    bool* finish = new bool[p_count];

    for(int i = 0; i < p_count; ++i){
        p_aloc[i] = new int[r_count];
        p_max[i]  = new int[r_count];
        p_need[i] = new int[r_count];
        finish[i] = false;

        for(int j = 0; j < r_count; ++j){
            fin >> p_aloc[i][j];
            avail[j] = avail[j] - p_aloc[i][j];
        }
        for(int j = 0; j < r_count; ++j){
            fin >> p_max[i][j];
            p_need[i][j] = p_max[i][j] - p_aloc[i][j];
        }
    }

    std::cout<<"Initial State:\n";
    print_state(avail,p_aloc,p_need,r_count,p_count,finish);



    int i=0;
    int p_rem = p_count;
    int last_ex = -1;
    int* ex_ord = new int[p_count];
    while(p_rem > 0 && i != last_ex ){
        bool canEx = true;
        if(!finish[i]){
            for(int k = 0; k < r_count; ++k){
                if(p_need[i][k] > avail[k]) canEx = false;
            }
            if(canEx){
                last_ex = i;
                finish[i] = true;
                for(int k = 0; k < r_count; ++k){
                    avail[k] = avail[k] + p_aloc[i][k];
                }
                ex_ord[p_count-p_rem] = i;
                --p_rem;
                std::cout<<"Process " << i << " executes.\n";
                print_state(avail,p_aloc,p_need,r_count,p_count,finish);
            }
        }
        i = (i+1) % p_count;
    }

    if(p_rem == 0){
        std::cout<<"System is in a safe state, execution order is: ";
        for(int i = 0; i < p_count; ++i)
            std::cout<<ex_ord[i]<<" ";
        std::cout<<std::endl;
    }
    else std::cout<<"System is not in a safe state."<<std::endl;



    for(int i = 0; i < p_count; ++i){
        delete[] p_aloc[i];
        delete[] p_max[i];
        delete[] p_need[i];
    }
    delete[] avail;
    delete[] p_aloc;
    delete[] p_max;
    delete[] p_need;
    delete[] finish;

    fin.close();
}


void print_state(int* avail, int** aloc, int** need, int r, int p, bool* f){
    std::cout << "Resources available: ";
    for(int i = 0; i < r; ++i)
        std::cout << avail[i] << " ";
    std::cout << "\nAllocated:\tNeed:\n";
    for(int i = 0; i < p; ++i){
        for(int j = 0; j < r; ++j){
            std::cout << aloc[i][j] << " ";
        }
        std::cout <<"\t\t";
        for(int j = 0; j < r; ++j){
            std::cout << need[i][j] << " ";
        }
        if(f[i]) std::cout<<"\tComplete";
        else     std::cout<<"\tWaiting";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}


