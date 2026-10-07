#include<stdio.h>


void merge(float profit[], float weight[], float ratio[], int id[], int m, int lb, int ub){
    float tp[100], tw[100], tr[100];
    int ti[100], i = lb, j = m + 1, k = 0;

    while(i <= m || j <= ub){
        int s;
        if(j > ub || (i <= m && ratio[i] > ratio[j])) s = i++;
        else s = j++;
        tp[k] = profit[s]; tw[k] = weight[s]; tr[k] = ratio[s]; ti[k] = id[s]; k++;
    }
    for(k = 0, i = lb; i <= ub; i++, k++){
        profit[i] = tp[k]; weight[i] = tw[k]; ratio[i] = tr[k]; id[i] = ti[k];
    }
}

void mergesort(float profit[], float weight[], float ratio[], int id[], int lb, int ub){
    if(lb < ub){
        int m = (lb + ub) / 2;
        mergesort(profit, weight, ratio, id, lb, m);
        mergesort(profit, weight, ratio, id, m + 1, ub);
        merge(profit, weight, ratio, id, m, lb, ub);
    }
}

void display(float profit[], float weight[], float ratio[], int id[], int n, int showRatio){
    printf("\nPackage\tProfit\tWeight%s\n", showRatio ? "\tRatio" : "");
    for(int i = 0; i < n; i++){
        printf("%d\t%.2f\t%.2f", id[i], profit[i], weight[i]);
        if(showRatio) printf("\t%.2f", ratio[i]);
        printf("\n");
    }
}

void calcRatio(float profit[], float weight[], float ratio[], int n){
    for(int i = 0; i < n; i++) ratio[i] = profit[i] / weight[i];
}

float knapsack(float profit[], float weight[], float frac[], int n, float capacity){
    float total = 0;
    for(int i = 0; i < n; i++){
        if(weight[i] <= capacity){     
            frac[i] = 1;
            capacity -= weight[i];
        } else {                        
            frac[i] = capacity / weight[i];
            capacity = 0;
        }
        total += profit[i] * frac[i];
    }
    return total;
}

void displaySelected(float profit[], float weight[], float frac[], int id[], int n){
    float usedWeight = 0, value = 0;
    printf("\nPackage\tFraction\tWeight used\tValue gained\n");
    for(int i = 0; i < n; i++){
        if(frac[i] > 0){
            printf("%d\t%.2f\t\t%.2f\t\t%.2f\n", id[i], frac[i], weight[i] * frac[i], profit[i] * frac[i]);
            usedWeight += weight[i] * frac[i];
            value += profit[i] * frac[i];
        }
    }
    printf("\nTotal weight used : %.2f\nMaximum value     : %.2f\n", usedWeight, value);
}

int main(){
    int n = 0, choice, id[100];
    float weight[100], profit[100], ratio[100], frac[100] = {0}, capacity = 0;

    do{
        printf("\n===== Smart Delivery Planning - Fractional Knapsack =====\n"
               "1. Enter Package Details\n2. Display Package Details\n3. Calculate Value/Weight Ratio\n"
               "4. Sort Packages by Ratio\n5. Find Maximum Value\n6. Display Selected Packages\n7. Exit\n"
               "Enter your choice : ");
        scanf("%d", &choice);

        switch(choice){
        case 1:
            printf("Enter the number of packages (max 100) : ");
            scanf("%d", &n);
            for(int i = 0; i < n; i++){
                id[i] = i + 1;
                printf("Enter weight of package %d : ", i + 1);
                scanf("%f", &weight[i]);
                printf("Enter profit of package %d : ", i + 1);
                scanf("%f", &profit[i]);
            }
            printf("Enter the maximum weight of the truck : ");
            scanf("%f", &capacity);
            break;
        case 2:
            display(profit, weight, ratio, id, n, 0);
            printf("Vehicle capacity = %.2f\n", capacity);
            break;
        case 3:
            calcRatio(profit, weight, ratio, n);
            display(profit, weight, ratio, id, n, 1);
            break;
        case 4:
            mergesort(profit, weight, ratio, id, 0, n - 1);
            display(profit, weight, ratio, id, n, 1);
            break;
        case 5:
            printf("\nMaximum value that can be carried = %.2f\n", knapsack(profit, weight, frac, n, capacity));
            break;
        case 6:
            displaySelected(profit, weight, frac, id, n);
            break;
        case 7:
            printf("\nTime complexity: O(n) ratios + O(n log n) merge sort + O(n) greedy pass = O(n log n),\n"
                   "since sorting dominates.\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    }while(choice != 7);

    return 0;
}
