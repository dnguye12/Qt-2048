#include "game.h"
#include <math.h>

#include <QMediaPlayer>
#include <QAudioOutput>

size_t score = 0;

Plateau plateauVide() {
    Plateau plat = vector<vector<int>>(4);
    for(int i =0; i < 4; i++)
    {
        plat[i] = {0, 0, 0, 0};
    }
    return plat;
}

Plateau plateauInitial()
{
    Plateau plat = plateauVide();
    int i1, i2, j1, j2;
    srand(time(0));
    while(1)
    {
        i1 = rand()%4;
        j1 = rand()%4;
        i2 = rand()%4;
        j2 = rand()%4;
        if(i1 != i2 || j1 != j2)
        {
            break;
        }
    }
    plat[i1][j1] = tireDeuxOuQuatre();
    plat[i2][j2] = 2;
    return plat;
}

int tireDeuxOuQuatre() {
    srand(time(0));
    int r = rand() % 10;
    if(r==9) {
        return 4;
    }else {
        return 2;
    }
}

Plateau deplacementGauche(Plateau plat)
{

    int i,j;
    int hi, hj;
    for(i=0; i<4; i++)
    {
        hi=i,hj=0;
        for(j=1; j<4; j++)
        {
            if(plat[i][j]!=0)
            {
                if(plat[i][j-1]==0 || plat[i][j-1]==plat[i][j])
                {
                    if(plat[hi][hj]==plat[i][j])
                    {
                        plat[hi][hj]*=2;
                        plat[i][j]=0;
                        score+=plat[hi][hj];
                        mergeSFX();
                    }
                    else
                    {
                        if(plat[hi][hj]==0)
                        {
                            plat[hi][hj]=plat[i][j];
                            plat[i][j]=0;
                        }
                        else
                        {
                            plat[hi][hj+1]=plat[i][j];
                            plat[i][j]=0;
                        }
                    }
                }
                else hj++;
            }
        }
    }
    return plat;
}


Plateau deplacementDroite(Plateau plat)
{
    int i,j;
    int hi, hj;
    for(i=0; i<4; i++)
    {
        hi=i,hj=3;
        for(j=2; j>=0; j--)
        {
            if(plat[i][j]!=0)
            {
                if(plat[i][j+1]==0 || plat[i][j+1]==plat[i][j])
                {
                    if(plat[hi][hj]==plat[i][j])
                    {
                        plat[hi][hj]*=2;
                        plat[i][j]=0;
                        score+=plat[hi][hj];
                        mergeSFX();
                    }
                    else
                    {
                        if(plat[hi][hj]==0)
                        {
                            plat[hi][hj]=plat[i][j];
                            plat[i][j]=0;
                        }
                        else
                        {
                            plat[hi][hj-1]=plat[i][j];
                            plat[i][j]=0;
                        }
                    }
                }
                else hj--;
            }
        }
    }

    return plat;
}

Plateau deplacementHaut(Plateau plat)
{
    int i,j;
    int hi, hj;
    for(j=0; j<4; j++)
    {
        hi=0,hj=j;
        for(i=1; i<4; i++)
        {
            if(plat[i][j]!=0)
            {
                if(plat[i-1][j]==0 || plat[i-1][j]==plat[i][j])
                {
                    if(plat[hi][hj]==plat[i][j])
                    {
                        plat[hi][hj]*=2;
                        plat[i][j]=0;
                        score+=plat[hi][hj];
                        mergeSFX();
                    }
                    else
                    {
                        if(plat[hi][hj]==0)
                        {
                            plat[hi][hj]=plat[i][j];
                            plat[i][j]=0;
                        }
                        else
                        {
                            plat[hi+1][hj]=plat[i][j];
                            plat[i][j]=0;
                        }
                    }
                }
                else hi++;
            }
        }
    }

    return plat;
}


Plateau deplacementBas(Plateau plat)
{
    int i,j;
    int hi, hj;
    for(j=0; j<4; j++)
    {
        hi=3,hj=j;
        for(i=2; i>=0; i--)
        {
            if(plat[i][j]!=0)
            {
                if(plat[i+1][j]==0 || plat[i+1][j]==plat[i][j])
                {
                    if(plat[hi][hj]==plat[i][j])
                    {
                        plat[hi][hj]*=2;
                        plat[i][j]=0;
                        score+=plat[hi][hj];
                        mergeSFX();
                    }
                    else
                    {
                        if(plat[hi][hj]==0)
                        {
                            plat[hi][hj]=plat[i][j];
                            plat[i][j]=0;
                        }
                        else
                        {
                            plat[hi-1][hj]=plat[i][j];
                            plat[i][j]=0;
                        }
                    }
                }
                else hi--;
            }
        }
    }

    return plat;
}

bool estTermine(Plateau plat) {

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(plat[i][j] == 0) {
                return false;
            }
        }
    }

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(plat[i][j] == plat[i+1][j] or plat[i][j] == plat[i][j+1]) {
                return false;
            }
        }
    }

    for(int i = 0; i < 3; i++) {
        if(plat[i][3] == plat[i + 1][3] || plat[3][i] == plat[3][i + 1]) {
            return false;
        }
    }
    return true;
}

bool estGagnant(Plateau plat) {
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j <4; j++)
        {
            if(plat[i][j] >= 2048)
            {
                return true;
            }
        }

    }
    return false;
}

int repow(int c)
{
    int i;
    for(i = 1; i <= c; i++)
    {
        if(pow(2, i) == c)
        {
            return i;
        }
    }
    return i;
}

Plateau addblock(Plateau plat) {
    int i, j;
    srand(time(0));
    while(1) {
        i = rand()%4;
        j = rand()%4;
        if(plat[i][j] == 0) {
            if(not estGagnant(plat)) {
                plat[i][j] = tireDeuxOuQuatre();
                break;
            }else {
                int max = 2048;

                for(int x = 0; x < 4; x++)
                {
                    for(int y = 0; y < 4; y++)
                    {
                        if(plat[x][y] >= max)
                        {
                            max = plat[x][y];
                        }
                    }
                }

                int a = repow(max);
                int b = tireDeuxOuQuatre();
                if(b == 2) {
                    plat[i][j] = tireDeuxOuQuatre();
                    break;

                }else {
                    plat[i][j] = pow(2, (rand()%(a - 8) + 1));
                    break;
                }
            }
        }

    }
    return plat;
}

bool notMoved(Plateau plat1, Plateau plat2) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(plat1[i][j] != plat2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int getScore() {
    return score;
}

void setScore(int n) {
    score = n;
}

void resetScore() {
    score = 0;
}

void mergeSFX() {
    QMediaPlayer *music = new QMediaPlayer();
    QAudioOutput *aO = new QAudioOutput;
    music->setAudioOutput(aO);
    music->setSource(QUrl("qrc:/sounds/Pop.mp3"));
    aO->setVolume(0.25);
    music->play();
}
