#include<stdio.h>
#include <bits/stdc++.h> 
using namespace std; 

int in[100],p[50],h=0,i,j,k,PF=0,n,nf;

int check(int a){
    h=0;
    for(j=0; j<nf; j++)
        if(p[j]==a){ h=1; break; }
    return h;
}
 
int check_index(int a){
    int index;
    for(k=0; k<nf; k++){
        if(p[k]==a){
            index=k;
            break;
        }
    }
    return index;
}
 
void LRU(){
    PF=0;
    for(i=0;i<nf;i++) p[i]=9999;
    int least[50];
    for(i=0; i<n; i++){
        printf("\nFor %d :",in[i]);
        if(check(in[i])==0){
            for(j=0; j<nf; j++){
                int pg=p[j];
                int found=0;
                for(k=i-1; k>=0; k--){
                    if(pg==in[k]){
                        least[j]=k;
                        found=1;
                        break;
                    }
                    else
                        found=0;
                }
                if(!found) least[j]=-9999;
            }
            int min=9999;
            int repindex;
            for(j=0; j<nf; j++){
                if(least[j]<min){
                    min=least[j];
                    repindex=j;
                }
            }
            p[repindex]=in[i];
            PF++;
            for (k=0; k<nf; k++){
                if(p[k]!=9999) printf(" %d",p[k]);
            }
        }
        else
            printf("No page fault!");
    }
    printf("\nTotal no of page faults:%d",PF);
}
 
void MRU(){
    int ind=0; 
    ind=(n % nf); 
    int ix = ind, id = in[ind]; 
    while(ix>0) in[ix]=in[--ix];
    in[0]=id; 
    for(int q=0;q<nf;q++) cout<<in[q]<<" "; 
} 

 
void Clock(){
    int usedbit[50];
    int victimptr=0;
    PF=0;
    for(i=0;i<nf;i++) p[i]=9999;
    for(i=0; i<nf; i++) usedbit[i]=0;
    for(i=0; i<n; i++){
        printf("\nFor %d:",in[i]);
        if(check(in[i])){
            printf("No page fault!");
            int hitindex=check_index(in[i]);
            if(usedbit[hitindex]==0) usedbit[hitindex]=1;
        }
        else{
            PF++;
            if(usedbit[victimptr]==1){
                do{
                    usedbit[victimptr]=0;
                    victimptr++;
                    if(victimptr==nf) victimptr=0;
                }
                while(usedbit[victimptr]!=0);
            }
            if(usedbit[victimptr]==0){
                p[victimptr]=in[i];
                usedbit[victimptr]=1;
                victimptr++;
            }
            for (k=0; k<nf; k++){
                if(p[k]!=9999) printf(" %d",p[k]);
            }
        }
        if(victimptr==nf) victimptr=0;
    }
    printf("\nTotal no of page faults:%d",PF);
}

void fifo(){
    PF=0;
    for(i=0;i<nf;i++) p[i]=9999;
    for(i=0; i<n; i++){
        printf("\nFor %d :",in[i]);
        if(check(in[i])==0){
            for(k=0;k<nf-1;k++) p[k]=p[k+1];
            p[k]=in[i];
            PF++;
            for (k=0; k<nf; k++){
                if(p[k]!=9999) printf(" %d",p[k]);
            }
        }
        else printf("No page fault");
    }
    printf("\nTotal no of page faults:%d",PF);
}
 
int main(){
	int a;
	printf("\n***********************************\n");
	printf("length of page reference sequence: "); scanf("%d",&n);
    printf("\npage reference sequence:\n");
    for(i=0; i<n; i++) scanf("%d",&in[i]);
    printf("\nEnter no of frames:"); scanf("%d",&nf);
    printf("\n***********************************\n");
    while(1){
        printf("Page Replacement Algorithms\n1.LRU\n2.MRU\n3.Clock\n4.fifo\n5.Exit\n\nEnter your choice: ");
        scanf("%d",&a);
        switch(a){
        case 1:
            LRU();
            break;
        case 2:
            MRU();
            break;
        case 3:
            Clock();
            break;
        case 4:
        	fifo();
        	break;
        default:
            return 0;
            break;
        }
    printf("\n\n***********************************\n\n");
    }
}
