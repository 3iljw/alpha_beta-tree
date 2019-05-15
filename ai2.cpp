#include <iostream>
#include <sstream>
#include <stdio.h>

#define MAX_NUM 2147483647
#define MIN_NUM -2147483648
int a=0;
int pow(int c, int b){
   int k = c;
   if (b==0){
      k=1;
   }
   else if (b==1){
      k=c;
   }
   else {
      for (int i =2 ;i<=b;i++){
         k=k*c;
      }
   }
   return k;
}

void init_tree(int dregree, int level, int tree[]){
   tree[0]=MIN_NUM;
   int continue_num = 0;
   for (int i=1; i<=level ; i++){
      if (i==1){
         for (int j=1; j<=dregree ; j++){
            tree[j]=MAX_NUM;
         }
         continue_num = dregree;
      }
      else {
         for (int j=continue_num+1; j<=continue_num+pow(dregree,i) ; j++){
            if(i%2==0){
               tree[j]=MIN_NUM;
            }
            else {
               tree[j]=MAX_NUM;
            }
         }
         continue_num = continue_num+pow(dregree,i) ;
      }
   }
}
/*
int dfs(int point, int dregree, int node, int tree[], int visit[]){
   for (int i=point*dregree+1; i<=point*dregree+dregree; i++){
      if (visit[i]==0 && i<node){
    		visit[i]=1;
	   	//printf("I am visiting %d in tree: %d \n",tree[i],i);
		   dfs(i,dregree,node,tree,visit);
         return point;
		}
   }
}

void minimax(int point, int dregree, int node, int tree[], int visit[]){
   if (point==0){
      for (int i=1; i<=dregree; i++){
         if (visit[i]==0 && i<node){
    		   visit[i]=1;
		      minimax(i,dregree,node,tree,visit);
         }
         if (visit[i]==1 && i<node){
            if (tree[i]>tree[point]){
                  tree[point]=tree[i];
            }
         }
      }
   }
   else {
      if (tree[point]==MAX_NUM){
         for (int i=point*dregree+1; i<=point*dregree+dregree; i++){
            if (visit[i]==0 && i<node){
               visit[i]=1;
               minimax(point,dregree,node,tree,visit);
            }
            if (visit[i]==1 && i<node){
               if (tree[i]<tree[point]){
                  tree[point]=tree[i];
               }
            }
         }
      }
      else if (tree[point]==MIN_NUM){
         for (int i=point*dregree+1; i<=point*dregree+dregree; i++){
            if (visit[i]==0 && i<node){
               visit[i]=1;
               minimax(point,dregree,node,tree,visit);
            }
            if (visit[i]==1 && i<node){
               if (tree[i]>tree[point]){
                  tree[point]=tree[i];
               }
            }
         }
      }
   }
}
*/
void alphabeta(int point, int dregree, int node, int tree[], int visit[]){
   //printf(" \"%d\" ",point);
   a++;
   if (point==0){
      for (int i=1; i<=dregree; i++){
         if (visit[i]==0 && i<node){
    		   visit[i]=1;
		      alphabeta(i,dregree,node,tree,visit);
         }
         if (visit[i]==1 && i<node){
            if (tree[i]>tree[point]){
                  tree[point]=tree[i];
            }
         }
      }
   }
   else {
      if (tree[point]==MAX_NUM){
         for (int i=point*dregree+1; i<=point*dregree+dregree; i++){
            if (visit[i]==0 && i<node){
               visit[i]=1;
               alphabeta(i,dregree,node,tree,visit);
            }
            if (visit[i]==1 && i<node){
               if (tree[i]<tree[point]){
                  tree[point]=tree[i];
               }
               if (tree[point]<=tree[(point-1)/dregree] && tree[(point-1)/dregree]!=MAX_NUM){           
                  break;
               }
            }
         }
      }
      else if (tree[point]==MIN_NUM){
         for (int i=point*dregree+1; i<=point*dregree+dregree; i++){
            if (visit[i]==0 && i<node){
               visit[i]=1;
               alphabeta(i,dregree,node,tree,visit);
            }
            if (visit[i]==1 && i<node){
               if (tree[i]>tree[point]){
                  tree[point]=tree[i];
               }
               if (tree[point]>=tree[(point-1)/dregree] && tree[(point-1)/dregree]!=MIN_NUM){
                  break;
               }
            }
         }
      }
   }
}

int main() {
   int dregree = 5 ;     // dregree the tree have
   int level = 2 ;        // level the tree have
   int leaf = pow(dregree,level);
   int data[leaf] = {15,4,1,17,9,-20,-19,12,23,-22,10,19,-17,0,-16,11,-8,2,-3,16,-21,-15,-6,-10,-24};
   int node = 0;
   for (int i=0;i<=level;i++){
      node = pow(dregree,i) + node;
   }
   int tree[node];
   init_tree(dregree,level,tree);
   printf("leaf = %d node = %d", leaf, node);

   for (int i=1, j=0;i<node;i++){
      if(i>=node-leaf){
      	tree[i]=data[j];
      	j++;
	  }
   }
	int visit[node+1];
	for (int i=0;i<=node;i++){
		visit[+i]=0;
	}
	visit[node]=1;

   alphabeta(0,dregree,node,tree,visit);
   printf("\nThe answer is : %d",tree[0]);
   printf("\nI wasn't visited : %d",node-a);
   return 0;
}
