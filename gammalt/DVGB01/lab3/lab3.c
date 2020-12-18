#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct struc{
    int adress;
    int count;
    int next;
}struc;


int main(int argc, char**argv)
{
  struc temp;
  int hit=0;
  int miss=0;
  int rep=0;
  int k1;
  struc a[256];
  int size = 0;
  int i, j, k = 0,m,c,test = 0;
  char *arg = NULL;
  int frames = 0;
  char *doc = NULL;

  arg = argv[1];
  frames = atoi(argv[2]);
  doc = argv[3];
  printf(" Frames: %d\n",frames);

	FILE *infil;

	infil = fopen(doc,"r");
	if(!infil) printf("%p",infil);

	while(fscanf(infil, "%d", &a[size].adress) != EOF)
  {
    a[size].next=0;
    a[size].count=0;
    size++;

  }





	//for (int i=0;i<size;i++) printf(" Adress: %d Next: %d\n",a[i].adress,a[i].next);

	struc *vmem = (struc*)malloc(frames*sizeof(struc));

	if(strcmp(arg,"FIFO") == 0)
  {
		for(i=0; i<size; i++)
    {
			test = 1;
			for (j = 0; j<frames; j++)
      {
				if(a[i].adress == vmem[j].adress)
        {
					printf(" Adress: %d Page hit\n", a[i].adress);
          hit++;
					test = 0;
					break;
				}
			}
  		if(test == 1)
      {
    		vmem[k].adress = a[i].adress;
    		if(k >= frames-1) k = 0;
    		else k++;
    		printf(" Adress: %d Page miss\n", a[i].adress);
        miss++;

  		}
		}
   rep=miss-frames;
   if (rep<0) rep=0;
	}

	else if(strcmp(arg,"Optimal") == 0)
  {
    for(i=0; i<size; i++)
    {
      test = 1;
			for (j = 0; j<frames; j++)
      {
				if(a[i].adress == vmem[j].adress)
        {
					printf(" Adress: %d Page hit\n", a[i].adress);
          hit++;
					test = 0;
					break;
				}
}
      if(test == 1)
      {

        if(k <=frames-1)
        {
           vmem[k]= a[i];
           k++;
           printf(" Adress: %d Page miss\n", a[i].adress);
           miss++;
        }
        else
        {
          int q,w;
        //  printf("i=%d\n",i);
          for (q=0;q<size;q++)
          {

            for (w=q+1;w<frames;w++)
            {
              vmem[q].next++;
              printf("next: %d\n",vmem[q].next);
              if (vmem[q].adress==a[w].adress )
              {
                break;
              }
            }
          }
        //  for (int g=0;g<frames;g++) printf("Adress: %d \nnext: %d\n",vmem[g].adress,vmem[g].next);

       k1=0;

        while (k1==0)
        {
          k1=1;
          for (m=0;m<frames-1;m++)
          {
            if(vmem[m].next<vmem[m+1].next)
            {
              temp=vmem[m+1];
              vmem[m+1]=vmem[m];
              vmem[m]=temp;
              k1=0;
            }
          }
        //  for (int g=0;g<frames;g++) printf("Adress: %d \nnext: %d\n",vmem[g].adress,vmem[g].next);
        }
        vmem[0]=a[i];

        printf(" Adress: %d Page miss\n", a[i].adress);
        miss++;
        rep++;

      }
    }
	}
//  for (int i=0;i<frames;i++) printf(" Adress: %d Next: %d\n",vmem[i].adress,vmem[i].next);
}

	else if(strcmp(arg,"LRU") == 0)
  {
    for(i=0; i<size; i++)
    {
      test = 1;
      for (j = 0; j<frames; j++)
      {
        if(a[i].adress == vmem[j].adress)
        {
          printf(" Adress: %d Page hit\n", a[i].adress);
          hit++;
          vmem[j].count=0;
          for ( c=0;c<frames;c++)  if (c!=j) vmem[c].count++;

          test = 0;
          break;
        }
      }
      if(test == 1)
      {

        if(k <=frames-1)
        {
           vmem[k]= a[i];
           k++;
           printf(" Adress: %d Page miss\n", a[i].adress);
           miss++;
           for ( c=0;c<frames;c++)  if (c!=k) vmem[c].count++;
           vmem[k].count=0;

        }
        else
        {
         k1=0;

        while (k1==0)
        {
          k1=1;
          for (m=0;m<frames-1;m++)
          {
            if(vmem[m].count<vmem[m+1].count)
            {
              temp=vmem[m+1];
              vmem[m+1]=vmem[m];
              vmem[m]=temp;
              k1=0;
            }
          }

        }
        vmem[0]=a[i];
        vmem[0].count=0;
        for ( c=1;c<frames;c++) vmem[c].count++;
        printf(" Adress: %d Page miss\n", a[i].adress);
        miss++;
        rep++;

      }
    }
    }
	}
	else printf("Ogiltig algoritm");

  printf("Algoritm: %s \nMemmory accesses: %d\nPage hits: %d\nPage misses: %d\nPage replacements %d\n",arg,size,hit,miss,rep);

	free(vmem);
	return 0;
}
