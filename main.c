#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void tri_rapide( long* tab, long  gauche, long   droite)
{
   long    l,x, i=gauche, j=droite, pivot=tab[(i+j)/2];

   do
   {
      while(tab[i]<pivot) i++;
      while(tab[j]>pivot) j--;
      if(i<=j)   { x=tab[i];  tab[i]=tab[j];  tab[j]=x;  i++;  j--;}
   }
   while(i<=j);

   if(gauche<j) tri_rapide(tab,gauche,j);
   if(i<droite) tri_rapide(tab,i,droite);

}
void remonter (long* tab, long n, long i)
{  long a;
        if (i==0) return;
        if (tab[i]>tab[i/2])
        {
                a=tab[i];
                tab[i]=tab[i/2];
                tab[i/2]=a;
                remonter (tab, n, i/2);
        }
}
void redescendre ( long* tab, const long n, long i)
{
        long max,a;
        if (2*i+1>=n) return;
        if (tab[2*i+1]>tab[2*i])
        max=2*i+1;
        else
        max=2*i;
        if (tab[max]>tab[i])
        {
                a=tab[max];
                tab[max]=tab[i];
                tab[i]=a;
                redescendre (tab, n, max);
        }
}

void tri_tas( long * tab, const long n )
{
        long i,a;
        for(i = 1 ; i < n ; i++)
        remonter(tab, n, i);

        for(i=n-1 ; i>0 ; i-- )
        {
                a=tab[0];
                tab[0]=tab[i];  //permutation
                tab[i]=a;
                redescendre(tab, i,0);
        }
}
void fusion(long  *t,long  deb1,long  milieu,long  fin2)
{
long  *table1;
long  deb2=milieu+1;
long  compt1=deb1;
long  compt2=deb2;
long   i;
table1=(long* )malloc((milieu-deb1+1)*sizeof(long));

//copie des éléments du début de tableau
for(i=deb1;i<=milieu;i++)
    table1[i-deb1]=t[i];

for(i=deb1;i<=fin2;i++)
{
        if (compt1==deb2) // éléments du tableau 1 sont tous utilisés
            break;  // éléments tous classés
        else if (compt2==(fin2+1)) // éléments du tableau 2 sont  tous utilisés
         { // copie en fin de tableau des éléments du 1er sous tableau restant
          t[i]=table1[compt1-deb1];
          compt1++;
          }
        else if (table1[compt1-deb1]<t[compt2])
            {  // ajoute d'un élément du 1 sous  tableau
                t[i]=table1[compt1-deb1];
                compt1++; // on avance dans le 1 sous tableau
            }
        else
            {  // copie 1élément à la suite du tableau
               t[i]=t[compt2];
               compt2++; // avancer le 2 sous tableau
            }
}
    free(table1);
}
void tri_fusion(long  *t,long  deb,long  fin)
{
if(deb!=fin)
    {
        long  milieu=(fin+deb)/2;
        tri_fusion(t,deb,milieu);
        tri_fusion(t,milieu+1,fin);  // 2 apelle qui devise le tableau sur 2
        fusion(t,deb,milieu,fin);  //fusion du 2 tableau trie
}
}
void tri_selection(long int* tab, long int n )
{
long int i,j,min=0,tmp=0;

  for (i =0; i < n-1; i++)
     { //printf("probleme %ld \n",i);
        min=i;
        for(j = i+1; j < n ; j++)
        if ( tab[min] > tab[j])
            min = j;             //recherche min
            if (min!=i) {
             tmp = tab[i];
             tab[i] = tab[min];  //permutation poser le min a ça place
             tab[min] = tmp;
            }

     }
}
void tri_insertion(long int n ,long int* tab)
{
    long int i,j,elm;
    for (i = 1; i < n; i++)
        {
        elm= tab[i];

        for (j = i; j > 0;j-- && tab[j - 1] > elm)    //comparaison et decalage
          {
            tab[j] = tab[j-1];
          }
        tab[j] = elm;
        }
}
int main()
{
    clock_t t1,t2,t3,t4;
    int choix=0 , oui=1;;

    double temp,temp2;
    long int k,n=0;
    long int *tab;
    long int *tab2;
    printf("*****TP fait par BENHADJ DJILALI Hadjer et AIT AMEUR OUERDIA Lydia ******* \n");
    printf("\n");
    printf("********les algorithmes de tri******** \n");
    etiq :
    do{
    printf("     tapez 1 pour choisir le tri selection\n");
    printf("     tapez 2 pour choisir le tri insertion\n");
    printf("     tapez 3 pour choisir le tri fusion\n");
    printf("     tapez 4 pour choisir le tri rapide\n");
    printf("     tapez 5 pour choisir le tri tas\n");
    printf("     taper votre reponse : \n");
     scanf("   %d",&choix);
    }while(choix>5 || choix <=0 );

    printf("\n   donner la taille du tableau : \n");
    scanf("%ld",&n);
    tab=(long int*) malloc(n*sizeof(long int));
    tab2=(long int*) malloc(n*sizeof(long int));

     for(k=0;k<n;k++)
        {
           tab[k]=k;
        }

     for(k=0;k<n;k++)
        {
           tab2[k]=n-k;
        }
switch (choix)
    {
    case 1:
        {
            printf("  *** tri selection *** \n");
            t1=clock();
            tri_selection(tab,n);
            t2=clock();
           temp= (double)(t2-t1)/CLOCKS_PER_SEC;
            t3=clock();
            tri_selection(tab,n);
            t4=clock();
           temp2=(double)(t3-t4)/CLOCKS_PER_SEC;
        }
        break;
      case 2:
        {
           printf("  *** tri insertion *** \n");
            t1=clock();
            tri_insertion(n,tab);
            t2=clock();
            temp= (double)(t2-t1)/CLOCKS_PER_SEC;
            t3=clock();
            tri_selection(tab,n);
            tri_insertion(n,tab);
            t4=clock();
           temp2=(double)(t2-t1)/CLOCKS_PER_SEC;


        }
        break;
      case 3:
        {
            printf("  ** tri fusion *** \n");
            t1=clock();
            tri_fusion(tab,0,n-1);
            t2=clock();
            temp= (double)(t2-t1)/CLOCKS_PER_SEC;
            t3=clock();
            tri_fusion(tab2,0,n-1);
            t4=clock();
            temp2= (double)(t2-t1)/CLOCKS_PER_SEC;

        }
        break;
      case 4:
        { printf("%ld ",n);
             printf("  ** tri rapid *** \n");
            t1=clock();
            tri_rapide(tab,0,n-1);
            t2=clock();
            temp= (double)(t2-t1)/CLOCKS_PER_SEC;
            t3=clock();
            tri_rapide(tab2,0,n-1);
            t4=clock();
            temp2= (double)(t2-t1)/CLOCKS_PER_SEC;

        }
        break;
     case 5:
        {
            printf("  *** tri tas *** \n");
            t1=clock();
            tri_tas(tab,n);
            t2=clock();
            temp= (double)(t2-t1)/CLOCKS_PER_SEC;
            t3=clock();
            tri_tas(tab2,n);
            t4=clock();
            temp2= (double)(t2-t1)/CLOCKS_PER_SEC;

        }
    break;
    }

    printf("  le temp d'execution dans le meilleur cas est : %f \n",temp);
    printf("  le temp d'execution dans le pire cas est : %f \n",temp2);

    printf("tapez 1 pour continuer : \n ");
    scanf("%d",&oui);
    if (oui==1) {goto etiq;}

    getchar();
    return 0;
}
