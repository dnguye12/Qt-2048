#include "game.h"



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
