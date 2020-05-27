#include "sudokusolver.h"

SudokuSolver::SudokuSolver(int origin[][9])
{
    int number=0;
    //Erster Lösungsansatz
    /*-----------------------------------------------------------------------------------------------------------------------------------
             * ----------------------------------------------------------------------------------------------------------------------------------*/
    solveMatrix(origin);


    //Zweiter Lösungsansatz
    /*-----------------------------------------------------------------------------------------------------------------------------------
         * ----------------------------------------------------------------------------------------------------------------------------------*/
    for(int iff=0;iff<9;iff++){
        for(int jff=0;jff<9;jff++){
            possi[iff][jff].clear();
        }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(origin[i][j]!=0){
                possi[i][j].push_front(origin[i][j]);

            }
            else{
                for(int ii=1;ii<10;ii++){
                    number=ii;
                    for(int a=0;a<9;a++){
                        if(origin[i][a]==ii){
                            number=-1;
                        }
                    }
                    if(number>-1){
                        for(int a=0;a<9;a++){

                            if( origin[a][j]==ii){
                                number=-1;
                            }
                        }
                    }

                    if(number>-1){
                        for(int a=0;a<9;a++){
                            switch (i%3) {
                            case 2:
                                switch (j%3) {
                                case 2:if(origin[i-1][j-1]==ii||origin[i-1][j-2]==ii||origin[i-2][j-1]==ii||origin[i-2][j-2]==ii){
                                        number=-1;
                                    }
                                    break;
                                case 0:if(origin[i-1][j+1]==ii||origin[i-1][j+2]==ii||origin[i-2][j+1]==ii||origin[i-2][j+2]==ii){
                                        number=-1;
                                    }
                                    break;
                                case 1:if(origin[i-1][j-1]==ii||origin[i-1][j+1]==ii||origin[i-2][j-1]==ii||origin[i-2][j+1]==ii){
                                        number=-1;
                                    }
                                    break;

                                }
                                break;
                            case 0:
                                switch (j%3) {
                                case 2:if(origin[i+1][j-1]==ii||origin[i+1][j-2]==ii||origin[i+2][j-1]==ii||origin[i+2][j-2]==ii){
                                        number=-1;
                                    }
                                    break;
                                case 0:if(origin[i+1][j+1]==ii||origin[i+1][j+2]==ii||origin[i+2][j+1]==ii||origin[i+2][j+2]==ii){
                                        number=-1;
                                    }
                                    break;
                                case 1:if(origin[i+1][j-1]==ii||origin[i+1][j+1]==ii||origin[i+2][j-1]==ii||origin[i+2][j+1]==ii){
                                        number=-1;
                                    }
                                    break;

                                }
                                break;
                            case 1:
                                switch (j%3) {
                                case 2:if(origin[i-1][j-1]==ii||origin[i-1][j-2]==ii||origin[i+1][j-1]==ii||origin[i+1][j-2]==ii){
                                        number=-1;
                                    }
                                    break;
                                case 0:if(origin[i-1][j+1]==ii||origin[i-1][j+2]==ii||origin[i+1][j+1]==ii||origin[i+1][j+2]==ii){
                                        number=-1;
                                    }
                                    break;
                                case 1:if(origin[i-1][j-1]==ii||origin[i-1][j+1]==ii||origin[i+1][j-1]==ii||origin[i+1][j+1]==ii){
                                        number=-1;
                                    }
                                    break;

                                }
                                break;

                            }
                        }
                    }

                    if(number!=-1){
                        possi[i][j].push_back(number);
                    }

                }


            }
        }
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                copy[i][j]=origin[i][j];

            }
        }
        for(int k=0;k<6;k++){
            for(int i=0;i<9;i++){
                for(int j=0;j<9;j++){
                    if(origin[i][j]==0&&possi[i][j].size()>0){
                        copy[i][j]=possi[i][j].front();
                        int k=possi[i][j].front();
                        possi[i][j].pop_front();
                        possi[i][j].push_back(k);
                        solveMatrix(copy);
                        if(isSolved(copy)){
                            i=9;
                            j=9;
                            for(int ii=0;ii<9;ii++){
                                for(int jj=0;jj<9;jj++){
                                    origin[ii][jj]=copy[ii][jj];

                                }
                            }
                        }
                        else{
                            for(int ii=0;ii<9;ii++){
                                for(int jj=0;jj<9;jj++){
                                    copy[ii][jj]=origin[ii][jj];

                                }
                            }

                        }
                    }

                }
            }
        }


    }



}
void SudokuSolver::printOutSudoku(int a [][9])
{
    for ( int i = 0; i < 9; i++ ){
        for ( int j = 0; j < 9; j++ ) {

            std::cout<<a[i][j]<<"\t";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

void SudokuSolver::setSQ(int input[][9], int number, int original [][9],bool state)
{
    int count1=0;
    int row[2]={0,0};
    int lane[2]={0,0};
    int count2=0;
    int row1[3]={0,0,0};
    int lane1[3]={0,0,0};
    int c=0;
    for(int iii=0;iii<9;iii++){
        for(int jjj=0;jjj<9;jjj++){
            input[iii][jjj]=0;
        }
    }
    for(int ik=0;ik<9;ik++){
        for(int jk=0;jk<9;jk++){
            if(original[ik][jk]!=0){
                input[ik][jk]=1;
            }

            if(original[ik][jk]==number){
                for(int ii=0;ii<9;ii++){
                    input[ik][ii]=1;
                    input[ii][jk]=1;
                }

                switch (ik%3) {
                case 2:
                    switch (jk%3) {
                    case 2:
                        input[ik-1][jk-1]=1;
                        input[ik-1][jk-2]=1;
                        input[ik-2][jk-1]=1;
                        input[ik-2][jk-2]=1;

                        break;
                    case 0:
                        input[ik-1][jk+1]=1;
                        input[ik-1][jk+2]=1;
                        input[ik-2][jk+1]=1;
                        input[ik-2][jk+2]=1;
                        break;
                    case 1:
                        input[ik-1][jk-1]=1;
                        input[ik-1][jk+1]=1;
                        input[ik-2][jk-1]=1;
                        input[ik-2][jk+1]=1;
                        break;

                    }
                    break;
                case 0:
                    switch (jk%3) {
                    case 2:
                        input[ik+1][jk-1]=1;
                        input[ik+1][jk-2]=1;
                        input[ik+2][jk-1]=1;
                        input[ik+2][jk-2]=1;
                        break;
                    case 0:
                        input[ik+1][jk+1]=1;
                        input[ik+1][jk+2]=1;
                        input[ik+2][jk+1]=1;
                        input[ik+2][jk+2]=1;
                        break;
                    case 1:
                        input[ik+1][jk-1]=1;
                        input[ik+1][jk+1]=1;
                        input[ik+2][jk-1]=1;
                        input[ik+2][jk+1]=1;
                        break;

                    }
                    break;
                case 1:
                    switch (jk%3) {
                    case 2:
                        input[ik-1][jk-1]=1;
                        input[ik-1][jk-2]=1;
                        input[ik+1][jk-1]=1;
                        input[ik+1][jk-2]=1;
                        break;
                    case 0:
                        input[ik-1][jk+1]=1;
                        input[ik-1][jk+2]=1;
                        input[ik+1][jk+1]=1;
                        input[ik+1][jk+2]=1;
                        break;
                    case 1:
                        input[ik-1][jk-1]=1;
                        input[ik-1][jk+1]=1;
                        input[ik+1][jk-1]=1;
                        input[ik+1][jk+1]=1;
                        break;

                    }
                    break;

                }

            }
        }
    }
    if(state){
        for(int a=0;a<3;a++){
            for(int b=0;b<3;b++){

                c=input[a*3][b*3]+input[a*3+1][b*3]+input[a*3+2][b*3]+
                        input[a*3][b*3+1]+input[a*3+1][b*3+1]+input[a*3+2][b*3+1]+
                        input[a*3][b*3+2]+input[a*3+1][b*3+2]+input[a*3+2][b*3+2];
                if(c<8&&c>5){
                    if(c==7){
                        count1=0;
                        row[0]=0;
                        row[1]=0;
                        lane[0]=0;
                        lane[1]=0;

                        for(int is=a*3;is<(a*3+3);is++){
                            for(int js=a*3;js<(a*3+3);js++){
                                if(input[is][js]==0){
                                    row[count1]=is;
                                    lane[count1]=js;
                                    count1++;
                                }
                            }
                        }
                        if(row[0]==row[1]){
                            for(int i=0;i<9;i++){
                                input[row[0]][i]=1;
                            }
                        }
                        if(lane[0]==lane[1]){
                            for(int i=0;i<9;i++){
                                input[i][lane[0]]=1;
                            }
                        }

                    }
                    if(c==6){
                        count2=0; row1[0]=0; row1[1]=0;
                        row1[2]=0; lane1[0]=0; lane1[1]=0; lane1[2]=0;

                        for(int id=a*3;id<(a*3+3);id++){
                            for(int jd=a*3;jd<(a*3+3);jd++){
                                if(input[id][jd]==0&&count2<3){
                                    row1[count2]=id;
                                    lane1[count2]=jd;
                                    count2++;
                                }
                            }
                        }
                        if(row1[0]==row1[1]&&row1[0]==row1[2]){
                            for(int idd=0;idd<9;idd++){
                                input[row1[0]][idd]=1;
                            }
                        }
                        if(lane1[0]==lane1[1]&&lane1[0]==lane1[2]){
                            for(int iss=0;iss<9;iss++){
                                input[iss][lane1[0]]=1;
                            }
                        }
                    }
                }

            }
        }
    }


}

bool SudokuSolver::isSolved(int a[][9])
{
    bool isTrue=0;
    int spalte=0;
    int reihe=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            spalte+=a[i][j];
            reihe+=a[j][i];
        }
        if(spalte==45&&reihe==45){
            isTrue=1;
        }
        else{
            return 0;
        }
        spalte=0;
        reihe=0;


    }

    int squares[9];
    int count=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            squares[count]=a[i*3][j*3]+a[i*3][j*3+1]+a[i*3][j*3+2]+
                    a[i*3+1][j*3]+a[i*3+1][j*3+1]+a[i*3+1][j*3+2]+
                    a[i*3+2][j*3]+a[i*3+2][j*3+1]+a[i*3+2][j*3+2];
            count++;
        }
    }
    count=0;
    for(int i=0;i<9;i++){
        if(squares[i]==45){
            isTrue=1;
        }
        else{
            return 0;
        }

    }

    return isTrue;
}

void SudokuSolver::makeZero(int a[][9])
{
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            a[i][j]=0;
        }
    }
}

void SudokuSolver::solveMatrix(int input[][9])
{
    int c=0;

    int c1=0;
    int c2=0;
    int sq[9][9];

    bool numberIsFound=1;
    while(numberIsFound){
        numberIsFound=0;
        for(int numb=1;numb<10;numb++){


            c1=0;
            c2=0;
            makeZero(sq);
            setSQ(sq,numb,input,0);

            for(int lll=0;lll<9;lll++){
                for(int mmm=0;mmm<9;mmm++){
                    c1+=sq[lll][mmm];
                    c2+=sq[mmm][lll];
                }
                if(c1==8){
                    for(int place=0;place<9;place++){
                        if(sq[lll][place]==0&&input[lll][place]==0){
                            input[lll][place]=numb;
                            numberIsFound=1;
                        }
                    }
                }
                if(c2==8){
                    for(int place=0;place<9;place++){
                        if(sq[place][lll]==0&&input[place][lll]==0){
                            input[place][lll]=numb;
                            numberIsFound=1;
                        }
                    }
                }
                c1=0;
                c2=0;
            }


            for(int a=0;a<3;a++){
                for(int b=0;b<3;b++){
                    makeZero(sq);
                    setSQ(sq,numb, input,1);
                    c=sq[a*3][b*3]+sq[a*3+1][b*3]+sq[a*3+2][b*3]+
                            sq[a*3][b*3+1]+sq[a*3+1][b*3+1]+sq[a*3+2][b*3+1]+
                            sq[a*3][b*3+2]+sq[a*3+1][b*3+2]+sq[a*3+2][b*3+2];
                    if(c<8&&c>5){
                        if(c==8){
                            for(int ib=a*3;ib<(a*3+3);ib++){
                                for(int jb=a*3;jb<(a*3+3);jb++){
                                    if(sq[ib][jb]==0&&input[ib][jb]==0){

                                        input[ib][jb]=numb;
                                        numberIsFound=1;

                                    }
                                }
                            }
                        }
                    }
                }
                c=0;



            }
            c1=0;
            c2=0;
            makeZero(sq);
            setSQ(sq,numb,input,0);

            for(int lll=0;lll<9;lll++){
                for(int mmm=0;mmm<9;mmm++){
                    c1+=sq[lll][mmm];
                    c2+=sq[mmm][lll];
                }
                if(c1==8){
                    for(int place=0;place<9;place++){
                        if(sq[lll][place]==0&&input[lll][place]==0){
                            input[lll][place]=numb;
                        }
                    }
                }
                if(c2==8){
                    for(int place=0;place<9;place++){
                        if(sq[place][lll]==0&&input[place][lll]==0){
                            input[place][lll]=numb;
                        }
                    }
                }
                c1=0;
                c2=0;
            }
        }
    }
}


